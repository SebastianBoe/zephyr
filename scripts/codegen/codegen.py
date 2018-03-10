# Copyright (c) 2018 Bobby Noelte.
#
# SPDX-License-Identifier: Apache-2.0

import imp
import inspect
import sys
import hashlib

from .cogapp.backward import string_types
from .cogapp.cogapp import Cog, CogGenerator, CogError, CogUsageError, NumberedFileReader
from .cogapp.whiteutils import *

from .options import Options, OptionsMixin
from .generic import GenericMixin
from .guard import GuardMixin
from .config import ConfigMixin
from .cmake import CMakeMixin
from .zephyr import ZephyrMixin
from .devicetree import DeviceTreeMixin
from .include import IncludeMixin
from .log import LogMixin

class CodeGenerator(OptionsMixin, GenericMixin, ConfigMixin,
                    CMakeMixin, ZephyrMixin, DeviceTreeMixin, GuardMixin,
                    IncludeMixin, LogMixin,
                    CogGenerator): # keep CogGenerator last

    def __init__(self, processor, globals={}):
        CogGenerator.__init__(self)
        self.processor = processor
        self.options = processor.options
        # All generators of a file usually work on the same global namespace
        self.generator_globals = globals

    # Make sure the "codegen" (alias cog) module has our state.
    def _set_module_state(self, module):
        # State of CodeGenerator
        module.options = self.options
        module.msg = self.msg
        module.out = self.out
        module.outl = self.outl
        module.error = self.error
        # Look for the Mixin classes
        for base_cls in inspect.getmro(CodeGenerator):
            if "Mixin" in base_cls.__name__:
                for member_name, member_value in inspect.getmembers(base_cls):
                    if member_name.startswith('_'):
                        continue
                    if inspect.isroutine(member_value):
                        setattr(module, member_name,
                            getattr(self, member_name))



    def evaluate(self, fname='code generator'):
        # figure out the right whitespace prefix for the output
        prefOut = whitePrefix(self.markers)

        intext = self.getCode()
        if not intext:
            return ''

        # In Python 2.2, the last line has to end in a newline.
        intext = "import codegen\n" + intext + "\n"
        code = compile(intext, str(fname), 'exec')

        # Make sure the "codegen" (alias cog) module has our state.
        self._set_module_state(self.processor.cogmodule)

        self.outstring = ''
        eval(code, self.generator_globals)

        # We need to make sure that the last line in the output
        # ends with a newline, or it will be joined to the
        # end-output line, ruining cog's idempotency.
        if self.outstring and self.outstring[-1] != '\n':
            self.outstring += '\n'

        return reindentBlock(self.outstring, prefOut)

##
# @brief The code generation processor
#
class CodeGen(Cog):

    def __init__(self):
        Cog.__init__(self)
        self.options = Options()

    ##
    # @brief Is this a trailing line after an end spec marker.
    #
    # @todo Make trailing end spec line detection dependent on
    #       type of text or file type.
    #
    # @param s line
    #
    def _is_end_spec_trailer(self, s):
        return '*/' in s

    def installCogModule(self):
        """ Magic mumbo-jumbo so that imported Python modules
            can say "import codegen" and get our state.

            Make us the module, and not our parent cog.
        """
        self.cogmodule = imp.new_module('codegen')
        self.cogmodule.path = []
        sys.modules['codegen'] = self.cogmodule

    def processFile(self, fIn, fOut, fname=None, globals=None):
        """ Process an input file object to an output file object.
            fIn and fOut can be file objects, or file names.
        """

        fInToClose = fOutToClose = None
        # Convert filenames to files.
        if isinstance(fIn, string_types):
            # Open the input file.
            sFileIn = fIn
            fIn = fInToClose = self.openInputFile(fIn)
        elif hasattr(fIn, 'name'):
            sFileIn = fIn.name
        else:
            sFileIn = fname or ''
        if isinstance(fOut, string_types):
            # Open the output file.
            sFileOut = fOut
            fOut = fOutToClose = self.openOutputFile(fOut)
        elif hasattr(fOut, 'name'):
            sFileOut = fOut.name
        else:
            sFileOut = fname or ''
        try:
            fIn = NumberedFileReader(fIn)

            bSawCog = False

            self.cogmodule.inFile = sFileIn
            self.cogmodule.outFile = sFileOut

            # The globals dict we'll use for this file.
            if globals is None:
                globals = {}

            # If there are any global defines, put them in the globals.
            globals.update(self.options.defines)

            # global flag for code generation
            globals['generate_code'] = True

            # loop over generator chunks
            l = fIn.readline()
            while l and globals['generate_code']:
                # Find the next spec begin
                while l and not self.isBeginSpecLine(l):
                    if self.isEndSpecLine(l):
                        raise CogError("Unexpected '%s'" % self.options.sEndSpec,
                            file=sFileIn, line=fIn.linenumber())
                    if self.isEndOutputLine(l):
                        raise CogError("Unexpected '%s'" % self.options.sEndOutput,
                            file=sFileIn, line=fIn.linenumber())
                    fOut.write(l)
                    l = fIn.readline()
                if not l:
                    break
                if not self.options.bDeleteCode:
                    fOut.write(l)

                # l is the begin spec
                gen = CodeGenerator(self, globals)
                gen.setOutput(stdout=self.stdout)
                gen.parseMarker(l)
                firstLineNum = fIn.linenumber()
                self.cogmodule.firstLineNum = firstLineNum

                gen.log('process {} #{}'.format(sFileIn, firstLineNum))
                # If the spec begin is also a spec end, then process the single
                # line of code inside.
                if self.isEndSpecLine(l):
                    beg = l.find(self.options.sBeginSpec)
                    end = l.find(self.options.sEndSpec)
                    if beg > end:
                        raise CogError("Codegen code markers inverted",
                            file=sFileIn, line=firstLineNum)
                    else:
                        sCode = l[beg+len(self.options.sBeginSpec):end].strip()
                        gen.parseLine(sCode)
                    # next line
                    l = fIn.readline()
                else:
                    # Deal with an ordinary code block.
                    l = fIn.readline()

                    # Get all the lines in the spec
                    while l and not self.isEndSpecLine(l):
                        if self.isBeginSpecLine(l):
                            raise CogError("Unexpected '%s'" % self.options.sBeginSpec,
                                file=sFileIn, line=fIn.linenumber())
                        if self.isEndOutputLine(l):
                            raise CogError("Unexpected '%s'" % self.options.sEndOutput,
                                file=sFileIn, line=fIn.linenumber())
                        if not self.options.bDeleteCode:
                            fOut.write(l)
                        gen.parseLine(l)
                        l = fIn.readline()
                    if not l:
                        raise CogError(
                            "Codegen block begun but never ended.",
                            file=sFileIn, line=firstLineNum)
                    # write out end spec line
                    if not self.options.bDeleteCode:
                        fOut.write(l)
                    gen.parseMarker(l)
                    # next line - may be trailing end spec line
                    l = fIn.readline()
                    if self._is_end_spec_trailer(l) and not self.isEndOutputLine(l):
                        fOut.write(l)
                        l = fIn.readline()

                # Eat all the lines in the output section.  While reading past
                # them, compute the md5 hash of the old output.
                previous = ""
                hasher = hashlib.md5()
                while l and not self.isEndOutputLine(l):
                    if self.isBeginSpecLine(l):
                        raise CogError("Unexpected '%s'" % self.options.sBeginSpec,
                            file=sFileIn, line=fIn.linenumber())
                    if self.isEndSpecLine(l):
                        raise CogError("Unexpected '%s'" % self.options.sEndSpec,
                            file=sFileIn, line=fIn.linenumber())
                    previous += l
                    hasher.update(to_bytes(l))
                    l = fIn.readline()
                curHash = hasher.hexdigest()

                if not l and not self.options.bEofCanBeEnd:
                    # We reached end of file before we found the end output line.
                    raise CogError("Missing '%s' before end of file." % self.options.sEndOutput,
                        file=sFileIn, line=fIn.linenumber())

                # Make the previous output available to the current code
                self.cogmodule.previous = previous

                # Write the output of the spec to be the new output if we're
                # supposed to generate code.
                hasher = hashlib.md5()
                if not self.options.bNoGenerate:
                    sFile = "%s+%d" % (sFileIn, firstLineNum)
                    sGen = gen.evaluate(fname=sFile)
                    sGen = self.suffixLines(sGen)
                    hasher.update(to_bytes(sGen))
                    fOut.write(sGen)
                    if not globals['generate_code']:
                        # generator code snippet stopped code generation
                        break
                newHash = hasher.hexdigest()

                bSawCog = True

                # Write the ending output line
                hashMatch = self.reEndOutput.search(l)
                if self.options.bHashOutput:
                    if hashMatch:
                        oldHash = hashMatch.groupdict()['hash']
                        if oldHash != curHash:
                            raise CogError("Output has been edited! Delete old checksum to unprotect.",
                                file=sFileIn, line=fIn.linenumber())
                        # Create a new end line with the correct hash.
                        endpieces = l.split(hashMatch.group(0), 1)
                    else:
                        # There was no old hash, but we want a new hash.
                        endpieces = l.split(self.options.sEndOutput, 1)
                    l = (self.sEndFormat % newHash).join(endpieces)
                else:
                    # We don't want hashes output, so if there was one, get rid
                    # of it.
                    if hashMatch:
                        l = l.replace(hashMatch.groupdict()['hashsect'], '', 1)

                if not self.options.bDeleteCode:
                    fOut.write(l)
                l = fIn.readline()

            if not bSawCog and self.options.bWarnEmpty:
                self.showWarning("no codegen code found in %s" % sFileIn)
        finally:
            if fInToClose:
                fInToClose.close()
            if fOutToClose:
                fOutToClose.close()

    def callableMain(self, argv):
        """ All of command-line codegen, but in a callable form.
            This is used by main.
            argv is the equivalent of sys.argv.
        """
        argv = argv[1:]

        self.options.parse_args(argv)
        self.options.validate()
        self._fixEndOutputPatterns()

        if self.options.bShowVersion:
            self.prout("Codegen version %s" % __version__)
            return

        if self.options.input_file is not None:
            self.processOneFile(self.options.input_file)
        else:
            raise CogUsageError("No files to process")
