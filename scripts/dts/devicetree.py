#!/usr/bin/env python3
#
# Copyright (c) 2017 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

import os
import sys
import pprint
import collections

import ast
import operator as op

class FileWrapper:
  def __init__(self, file_obj):
    self.file_obj = file_obj
    self.buffer = ''

  def readline(self):
    ret = self.buffer

    if not ret.endswith('\n'):
      ret += self.file_obj.readline()

    self.buffer = ''
    return ret

  def unread(self, buffer):
    self.buffer += buffer


def read_until(line, fd, end):
  out = [line]
  while True:
    idx = line.find(end)
    if idx < 0:
      line = clean_line(fd.readline(), fd)
      out.append(line)
    else:
      out.append(line[idx + len(end):])
      return out

def remove_comment(line, fd):
  out = []
  while True:
    idx = line.find('/*')
    if idx < 0:
      idx = line.find('//')
      if idx < 0:
        out.append(line)
      else:
        out.append(line[:idx])
      return ' '.join(out)

    out.append(line[:idx])
    line = read_until(line[idx:], fd, '*/')[-1]

def remove_preprocessor_directives(line):
  if line.startswith('# '):
    return ''
  return line

def clean_line(line, fd):
  line = remove_preprocessor_directives(line)
  line = remove_comment(line, fd)
  line = line.strip()
  return line

def parse_node_name(fd, line):
  line, rest = line.split('{', 1)

  if rest:
    fd.unread(rest + '\n')

  if '@' in line:
    line, addr = line.split('@')
  else:
    addr = None

  if ':' in line:
    label, name = line.split(':')
  else:
    name = line
    label = None

  if addr is None:
    return label, name.strip(), None, None

  return label, name.strip(), addr, int(addr,16)

def parse_values_internal(value, start, end, separator):
  # Remove the prefix 'start', and the suffix 'end' from 'value' and
  # write the resulting string to the variable 'out'
  #
  # out = value[len(start):-len(end)]
  out = []

  inside = False
  accum = []
  for ch in value:
    if not inside:
      if ch == start:
        inside = True
        accum = []
    else:
      if ch == end:
        inside = False
        out.append(''.join(accum))
        accum = []
      else:
        accum.append(ch)

  if separator == ' ':
    out = [v.split() for v in out]

  if len(out) == 1:
    return parse_value(out[0])

  return [parse_value(v) for v in out]

def substitue_evaluation_of_expression(value):
  start = value.index("(")
  end = value.rfind(")")
  if end == -1:
    raise SyntaxError("'(' found, but no matching ')' on the same line {}".format(value))

  end += 1

  # Attribution:
  # https://stackoverflow.com/a/9558001/1134134
  # supported operators
  operators = {
    ast.Add: op.add,
    ast.Sub: op.sub,
    ast.Mult: op.mul,
    ast.Div: op.truediv,
    ast.Pow: op.pow,
    ast.BitXor: op.xor,
    ast.BitOr: op.or_,
    ast.LShift: op.lshift,
    ast.USub: op.neg,
  }

  def eval_expr(expr):
    """
    >>> eval_expr('2^6')
    4
    >>> eval_expr('2**6')
    64
    >>> eval_expr('1 + 2*3**(4^5) / (6 + -7)')
    -5.0
    """
    return eval_(ast.parse(expr, mode='eval').body)

  def eval_(node):
      if isinstance(node, ast.Num): # <number>
          return node.n
      elif isinstance(node, ast.BinOp): # <left> <operator> <right>
          return operators[type(node.op)](eval_(node.left), eval_(node.right))
      elif isinstance(node, ast.UnaryOp): # <operator> <operand> e.g., -1
          return operators[type(node.op)](eval_(node.operand))
      else:
          raise TypeError(node)

  expr = value[start:end]
  evaluated = eval_expr(expr)

  # Substitue the expression with the evaluated expression
  return value[0:start] + str(evaluated) + value[end:]

def parse_values(value, start, end, separator):

  # If we find a '(' in the value, we immediately evaluate the
  # expression and substitue the expression with the evaluated value
  if "(" in value:
    value = substitue_evaluation_of_expression(value)

  out = parse_values_internal(value, start, end, separator)
  if isinstance(out, list) and all(isinstance(v, str) and len(v) == 1 and not v.isalpha() for v in out):
    return bytearray(out)
  return out

def parse_value(value):
  if value == '':
    return value

  if isinstance(value, list):
    out = [parse_value(v) for v in value]
    return out[0] if len(out) == 1 else out

  if value[0] == '<':
    return parse_values(value, '<', '>', ' ')
  if value[0] == '"':
    return parse_values(value, '"', '"', ',')
  if value[0] == '[':
    return parse_values(value, '[', ']', ' ')

  if value[0] == '&':
    return {'ref': value[1:]}

  if value[0].isdigit():
    if value.startswith("0x"):
      return int(value, 16)
    if value[0] == '0':
      return int(value, 8)
    return int(value, 10)

  return value

def parse_property(property, fd):
  if '=' in property:
    key, value = property.split('=', 1)
    value = ' '.join(read_until(value, fd, ';')).strip()
    if not value.endswith(';'):
      raise SyntaxError("parse_property: missing semicolon: %s" % value)
    return key.strip(), parse_value(value[:-1])

  property = property.strip()
  if not property.endswith(';'):
    raise SyntaxError("parse_property: missing semicolon: %s" % property)

  return property[:-1].strip(), {'empty': True}

def build_node_name(name, addr):
  if addr is None:
    return name
  elif isinstance(addr, int):
    return '%s@%x' % (name, addr)

  return '%s@%s' % (name, addr.strip())

def parse_node(line, fd):
  label, name, addr, numeric_addr = parse_node_name(fd, line)

  node = {
    'label': label,
    'addr': numeric_addr,
    'children': {},
    'props': {},
    'name': build_node_name(name, addr)
  }

  while True:
    line = fd.readline()
    if not line:
      raise SyntaxError("parse_node: Missing } while parsing node")

    line = clean_line(line, fd)

    if not line:
      continue

    if line == '};':
      break

    if '{' in line:
      new_node = parse_node(line, fd)
      node['children'][new_node['name']] = new_node
    else:
      key, value = parse_property(line, fd)
      node['props'][key] = value

  return node

def open_with_include_path(file_path, mode, include_path):
  for path in include_path:
    try:
      fd = open(os.path.join(path, file_path), mode)
    except IOError:
      continue

    return FileWrapper(fd)

  raise IOError("Could not find %s in %s" % (file_path, include_path))

def update_node(node, new_node):
  for k, v in new_node.items():
    if isinstance(v, collections.Mapping):
      node[k] = update_node(node.get(k, {}), v)
    else:
      node[k] = v
  return node

def parse_file(fd, ignore_dts_version=False, include_path=[]):
  fd = FileWrapper(fd)

  include_path.append(os.getcwd())

  nodes = {}
  has_v1_tag = False

  while True:
    line = fd.readline()
    if not line:
      break

    line = clean_line(line, fd)
    if not line:
      continue

    if line.startswith('/include/ '):
      tag, filename = line.split()
      with open_with_include_path(filename.strip()[1:-1], "r", include_path) as new_fd:
        nodes.update(parse_file(new_fd, True))
    elif line == '/dts-v1/;':
      has_v1_tag = True
    elif line.startswith('/memreserve/ ') and line.endswith(';'):
      tag, start, end = line.split()
      start = int(start, 16)
      end = int(end[:-1], 16)
      label = "reserved_memory_0x%x_0x%x" % (start, end)
      nodes[label] = {
        'reg': [start, end],
        'label': label,
        'addr': start,
        'name': build_node_name(name, start)
      }
    elif line.endswith('{'):
      if not has_v1_tag and not ignore_dts_version:
        raise SyntaxError("parse_file: Missing /dts-v1/ tag")

      new_node = parse_node(line, fd)
      nodes[new_node['name']] = update_node(nodes.get(new_node['name'], {}), new_node)
    else:
      raise SyntaxError("parse_file: Couldn't understand the line: %s" % line)
  return nodes

def dump_refs(name, value, indent=0):
  spaces = '  ' * indent

  out = []
  if isinstance(value, dict) and 'ref' in value:
    out.append('%s\"%s\" -> \"%s\";' % (spaces, name, value['ref']))
  elif isinstance(value, list):
    for elem in value:
      out.extend(dump_refs(name, elem, indent))

  return out

def dump_all_refs(name, props, indent=0):
  out = []
  for key, value in props.items():
    out.extend(dump_refs(name, value, indent))
  return out

def next_subgraph(count=[0]):
  count[0] += 1
  return 'subgraph cluster_%d' % count[0]

def get_dot_node_name(node):
  name = node['name']
  return name[1:] if name[0] == '&' else name

def dump_to_dot(nodes, indent=0, start_string='digraph devicetree', name=None):
  spaces = '  ' * indent

  print("%s%s {" % (spaces, start_string))

  if name is not None:
    print("%slabel = \"%s\";" % (spaces, name))
    print("%s\"%s\";" % (spaces, name))

  ref_list = []
  for key, value in nodes.items():
    if value.get('children'):
      refs = dump_to_dot(value['children'], indent + 1, next_subgraph(), get_dot_node_name(value))
      ref_list.extend(refs)
    else:
      print("%s\"%s\";" % (spaces, get_dot_node_name(value)))

  for key, value in nodes.items():
    refs = dump_all_refs(get_dot_node_name(value), value.get('props', {}), indent)
    ref_list.extend(refs)

  if start_string.startswith("digraph"):
    print("%s%s" % (spaces, '\n'.join(ref_list)))

  print("%s}" % spaces)

  return ref_list

def main(args):
  if len(args) == 1:
    print('Usage: %s filename.dts' % args[0])
    return 1

  if '--dot' in args:
    formatter = dump_to_dot
    args.remove('--dot')
  else:
    formatter = lambda nodes: pprint.pprint(nodes, indent=2)

  with open(args[1], "r") as fd:
    formatter(parse_file(fd))

  return 0

if __name__ == '__main__':
  sys.exit(main(sys.argv))
