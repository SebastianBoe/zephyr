#!/usr/bin/env python3

# A curses-based menuconfig implementation. The interface should feel familiar
# to people used to mconf ('make menuconfig').
#
# Supports the same keys as mconf, and also supports a set of keybindings
# inspired by Vi:
# 
#   J/K     : Down/Up
#   L       : Enter menu/Toggle item
#   H       : Leave menu
#   Ctrl-D/U: Page Down/Page Down
#   G/End   : Jump to end of list
#   g/Home  : Jump to beginning of list
#
# This means that the mconf feature that allows you to press a character to
# jump to a menu entry in the current menu that includes that character isn't
# supported. A search feature that allows you to immediately jump to a symbol
# defined anywhere will be added later instead.
#
# Space and Enter are "smart" and try to do what you'd expect for the given
# menu entry.
#
# Other features:
#
#   - Seamless terminal resizing.
#
#   - No dependencies on *nix, as the 'curses' module is in the Python standard
#     library.
#
#   - Improved information screen compared to mconf:
#
#       * Expressions are split up by their top-level &&/|| operands to improve
#         readability.
#
#       * Undefined symbols in expressions are pointed out.
#
#       * Menus and comments have information displays.
#
#       * The Kconfig definition of the item is included on the information
#         screen.


#
# Configuration variables
#

# Number of steps for Page Up/Down to jump
PG_JUMP = 6

# How far the cursor needs to be from the edge of the window before it starts
# to scroll
SCROLL_OFFSET = 5

# Minimum width of dialogs that ask for text input
INPUT_DIALOG_MIN_WIDTH = 30

# Number of arrows pointing up/down to draw when a window is scrolled
N_SCROLL_ARROWS = 14

def init_styles():
    global PATH_STYLE
    global TOP_SEP_STYLE
    global MENU_LIST_STYLE
    global MENU_LIST_SEL_STYLE
    global BOT_SEP_STYLE
    global HELP_STYLE

    global DIALOG_FRAME_STYLE
    global DIALOG_BODY_STYLE
    global INPUT_FIELD_STYLE

    global INFO_TOP_LINE_STYLE
    global INFO_TEXT_STYLE
    global INFO_BOT_SEP_STYLE
    global INFO_HELP_STYLE

    # Initialize styles for different parts of the application. The arguments
    # are ordered as follows:
    #
    #   1. Text color
    #   2. Background color
    #   3. Attributes
    #   4. Extra attributes if colors aren't available. The colors will be
    #      ignored in this case, and the attributes from (3.) and (4.) will be
    #      ORed together.

    # Top row, with menu path
    PATH_STYLE          = style(curses.COLOR_BLACK, curses.COLOR_WHITE,  curses.A_BOLD                     )

    # Separator below menu path, with title and arrows pointing up
    TOP_SEP_STYLE       = style(curses.COLOR_BLACK, curses.COLOR_YELLOW, curses.A_BOLD,   curses.A_STANDOUT)

    # List of menu entries with symbols, etc.
    MENU_LIST_STYLE     = style(curses.COLOR_BLACK, curses.COLOR_WHITE,  curses.A_NORMAL                   )

    # Selected menu entry
    MENU_LIST_SEL_STYLE = style(curses.COLOR_WHITE, curses.COLOR_BLUE,   curses.A_NORMAL, curses.A_STANDOUT)

    # Row below menu list, with arrows pointing down
    BOT_SEP_STYLE       = style(curses.COLOR_BLACK, curses.COLOR_YELLOW, curses.A_BOLD,   curses.A_STANDOUT)

    # Help window with keys at the bottom
    HELP_STYLE          = style(curses.COLOR_BLACK, curses.COLOR_WHITE,  curses.A_BOLD                     )


    # Frame around dialog boxes
    DIALOG_FRAME_STYLE  = style(curses.COLOR_BLACK, curses.COLOR_YELLOW, curses.A_BOLD,   curses.A_STANDOUT)

    # Body of dialog boxes
    DIALOG_BODY_STYLE   = style(curses.COLOR_WHITE, curses.COLOR_BLACK,  curses.A_NORMAL                   )

    # Text input field in dialog boxes
    INPUT_FIELD_STYLE   = style(curses.COLOR_WHITE, curses.COLOR_BLUE,   curses.A_NORMAL, curses.A_STANDOUT)


    # Top line of information display, with title and arrows pointing up
    INFO_TOP_LINE_STYLE = style(curses.COLOR_BLACK, curses.COLOR_YELLOW, curses.A_BOLD,   curses.A_STANDOUT)

    # Main information display window
    INFO_TEXT_STYLE     = style(curses.COLOR_BLACK, curses.COLOR_WHITE,  curses.A_NORMAL                   )

    # Separator below information display, with arrows pointing down
    INFO_BOT_SEP_STYLE  = style(curses.COLOR_BLACK, curses.COLOR_YELLOW, curses.A_BOLD,   curses.A_STANDOUT)

    # Help window with keys at the bottom of the information display
    INFO_HELP_STYLE     = style(curses.COLOR_BLACK, curses.COLOR_WHITE,  curses.A_BOLD                     )


#
# Main application
#

from kconfiglib import Kconfig, \
                       Symbol, Choice, MENU, COMMENT, \
                       BOOL, TRISTATE, STRING, INT, HEX, UNKNOWN, \
                       AND, OR, NOT, \
                       expr_value, split_expr, \
                       TRI_TO_STR, TYPE_TO_STR

# We need this double import for the expr_str() override below
import kconfiglib

import errno
import curses
import locale
import os
import sys
import textwrap


color_attrib_i = 1
color_attribs = {}

def style(fg_color, bg_color, attribs, no_color_extra_attribs=0):
    global color_attribs
    global color_attrib_i

    if not curses.has_colors():
        return attribs | no_color_extra_attribs

    if (fg_color, bg_color) in color_attribs:
        # !!!
        color_attrib = color_attribs[(fg_color, bg_color)]
    else:
        curses.init_pair(color_attrib_i, fg_color, bg_color)
        color_attrib = color_attribs[(fg_color, bg_color)] = \
            curses.color_pair(color_attrib_i)
        color_attrib_i += 1

    return color_attrib | attribs

def expr_str_val(expr):
    if isinstance(expr, Symbol) and not expr.is_constant and \
       not is_num(expr.name):

        if not expr.nodes:
            return "{}(undefined/n)".format(expr.name)

        return '{}(="{}")'.format(expr.name, expr.str_value)

    if isinstance(expr, tuple) and expr[0] == NOT and \
       isinstance(expr[1], Symbol):

        return "! " + expr_str(expr[1])

    return expr_str_orig(expr)

expr_str_orig = kconfiglib.expr_str
kconfiglib.expr_str = expr_str_val
expr_str = expr_str_val

def menuconfig(kconf):
    globals()["kconf"] = kconf

    # We rely on having a selected node
    if not visible_nodes(kconf.top_node):
        print("No visible symbols in the top menu -- nothing to configure")
        return

    # Make sure curses uses the encoding specified in the environment
    locale.setlocale(locale.LC_ALL, "")

    # Get rid of the delay between pressing ESC and jumping to the parent menu
    os.environ.setdefault("ESCDELAY", "0")

    # _menuconfig() returns the string to print on exit. It needs to be printed
    # after curses has been de-initialized.
    return curses.wrapper(_menuconfig)

def _menuconfig(stdscr):
    # Logic for the "main" display, with the list of symbols, etc.

    globals()["stdscr"] = stdscr

    init()

    while True:
        draw_main()
        curses.doupdate()


        c = menu_win.get_wch()

        if c == curses.KEY_RESIZE:
            resize_main()

        if c in (curses.KEY_DOWN, "j", "J"):
            move_down()

        elif c in (curses.KEY_UP, "k", "K"):
            move_up()

        elif c in (curses.KEY_NPAGE, "\x04"):  # Page Down/Ctrl-D
            # Keep it simple. This way we get sane behavior for small windows,
            # etc., for free.
            for _ in range(PG_JUMP):
                move_down()

        elif c in (curses.KEY_PPAGE, "\x15"):  # Page Up/Ctrl-U
            for _ in range(PG_JUMP):
                move_up()

        elif c in (curses.KEY_END, "G"):
            move_to_bottom()

        elif c in (curses.KEY_HOME, "g"):
            move_to_top()

        elif c in (curses.KEY_RIGHT, " ", "\n", "l", "L"):
            sel_node = visible[node_i]

            if sel_node.is_menuconfig and not \
               (c == " " and prefer_toggle(sel_node.item)):

                enter_menu(sel_node)
            else:
                change_node(sel_node)
                if is_y_mode_choice_sym(sel_node.item):
                    leave_menu()

        elif c in (curses.KEY_LEFT, curses.KEY_BACKSPACE, ERASE_CHAR,
                   "\x1B",  # \x1B = ESC
                   "h", "H"):
            if cur_menu is not kconf.top_node:
                leave_menu()

        elif c in ("s", "S"):
            filename = ".config"
            while True:
                filename = input_dialog(
                    "Filename to save configuration to",
                    filename)

                if filename is None:
                    break

                if try_write(kconf.write_config, filename, "configuration"):
                    break

        elif c in ("m", "M"):
            filename = "defconfig"
            while True:
                filename = input_dialog(
                    "Filename to save minimal configuration to",
                    filename)

                if filename is None:
                    break

                if try_write(kconf.write_min_config, filename,
                             "minimal configuration"):
                    break

        elif c == "?":
            info_display(visible[node_i])

        elif c == "/":
            search_dialog()

        elif c in ("q", "Q"):
            while True:
                c = key_dialog(
                    "Quit",
                    "Save configuration to .config?\n"
                    "\n"
                    "    (Y)es  (N)o  (C)ancel",
                    "ync")

                if c is None or c == "c":
                    break

                if c == "y":
                    if try_write(kconf.write_config, ".config",
                                "configuration"):
                        return "Configuration saved to .config"

                elif c == "n":
                    return "Configuration was not saved"

def init():
    global ERASE_CHAR

    global path_win
    global top_sep_win
    global menu_win
    global bot_sep_win
    global help_win

    global parent_rows
    global cur_menu
    global visible
    global node_i
    global scroll

    # !!!
    ERASE_CHAR = curses.erasechar().decode()

    init_styles()

    # Hide the cursor
    safe_curs_set(0)

    # Initialize windows

    # Window showing the path at the top
    path_win = curses.newwin(1, 1)
    path_win.bkgdset(" ", PATH_STYLE)

    # Separator line above the symbol list
    top_sep_win = curses.newwin(1, 1)
    top_sep_win.bkgdset(" ", TOP_SEP_STYLE)

    # Symbol list
    menu_win = curses.newwin(1, 1)
    menu_win.bkgdset(" ", MENU_LIST_STYLE)
    menu_win.keypad(True)

    # Separator line below the symbol list
    bot_sep_win = curses.newwin(1, 1)
    bot_sep_win.bkgdset(" ", BOT_SEP_STYLE)

    # Help window at the bottom
    help_win = curses.newwin(1, 1)
    help_win.bkgdset(" ", HELP_STYLE)

    # The rows we'd like the nodes in the parent menus to appear on. This
    # prevents the scroll from jumping around when going in and out of menus.
    parent_rows = []


    # !!!
    cur_menu = kconf.top_node
    visible = visible_nodes(cur_menu)
    node_i = 0
    scroll = 0

    resize_main()

def resize_main():
    global scroll

    screen_height, screen_width = stdscr.getmaxyx()

    path_win.resize(1, screen_width)
    top_sep_win.resize(1, screen_width)
    bot_sep_win.resize(1, screen_width)

    help_win_height = 3
    sym_win_height = screen_height - help_win_height - 3

    if sym_win_height >= 1:
        menu_win.resize(sym_win_height, screen_width)
        help_win.resize(help_win_height, screen_width)

        top_sep_win.mvwin(1, 0)
        menu_win.mvwin(2, 0)
        bot_sep_win.mvwin(2 + sym_win_height, 0)
        help_win.mvwin(2 + sym_win_height + 1, 0)
    else:
        # Degenerate case. Give up on nice rendering and just prevent errors.

        sym_win_height = 1

        menu_win.resize(1, screen_width)
        help_win.resize(1, screen_width)

        for win in top_sep_win, menu_win, bot_sep_win, help_win:
            win.mvwin(0, 0)

    # Adjust the scroll so that the selected node is still within the
    # window, if needed
    if node_i - scroll >= sym_win_height:
        scroll = node_i - sym_win_height + 1

def sym_win_height():
    return menu_win.getmaxyx()[0]

def max_scroll():
    return max(0, len(visible) - sym_win_height())

def prefer_toggle(item):
    # !!!update
    # Try to do the sensible thing depending on the type of menu node.
    #
    # The only difference between Space and Enter/L is that Space will
    # toggle the following instead of entering their menu:
    #
    #   1. Symbols defined with 'menuconfig'
    #
    #   2. Choices that can be in more than one mode (e.g. optional
    #      choices)
    return isinstance(item, Symbol) or \
           (isinstance(item, Choice) and len(item.assignable) > 1)

def enter_menu(menu):
    global cur_menu
    global visible
    global node_i
    global scroll

    visible_sub = visible_nodes(menu)
    if visible_sub:
        # !!!
        parent_rows.append(node_i - scroll)

        # Jump into menu
        cur_menu = menu
        visible = visible_sub
        node_i = 0
        scroll = 0

def leave_menu():
    global cur_menu
    global visible
    global node_i
    global scroll

    # Jump back to parent menu and try to make the node appear on
    # the same row as before
    old_row = parent_rows.pop()

    parent = parent_menu(cur_menu)
    visible = visible_nodes(parent)
    node_i = visible.index(cur_menu)
    scroll = max(visible.index(cur_menu) - old_row, 0)
    cur_menu = parent

def move_down():
    global node_i
    global scroll

    if node_i < len(visible) - 1:
        # Jump to the next node
        node_i += 1

        # If the new node is within the scroll area, increase the scroll by
        # one. This gives nice and non-jumpy behavior even when
        # SCROLL_OFFSET >= sym_win_height().
        if node_i >= scroll + sym_win_height() - SCROLL_OFFSET:
            scroll = min(scroll + 1, max_scroll())

def move_up():
    global node_i
    global scroll

    if node_i > 0:
        # Jump to the previous node
        node_i -= 1

        # See move_down()
        if node_i <= scroll + SCROLL_OFFSET:
            scroll = max(scroll - 1, 0)

def move_to_bottom():
    global node_i
    global scroll

    node_i = len(visible) - 1
    scroll = max_scroll()

def move_to_top():
    global node_i
    global scroll

    node_i = scroll = 0

def draw_main():
    # Draws the "main" display, with the list of symbols, the header, and the
    # footer


    #
    # Update the window showing the path
    #

    path_win.erase()

    # Draw the menu path ("(top menu) -> menu -> submenu -> ...")

    menu_prompts = []

    menu = cur_menu
    while menu is not kconf.top_node:
        menu_prompts.insert(0, menu.prompt[0])
        menu = menu.parent

    safe_addstr(path_win, 0, 0, "(top menu)")
    for prompt in menu_prompts:
        safe_addch(path_win, " ")
        safe_addch(path_win, curses.ACS_RARROW)
        safe_addstr(path_win, " " + prompt)

    path_win.noutrefresh()


    #
    # Update the top separator window
    #

    top_sep_win.erase()

    # Draw arrows pointing up if the symbol window is scrolled down. Draw them
    # before drawing the title, so the title ends up on top for small windows.
    if scroll > 0:
        safe_hline(top_sep_win, 0, 4, curses.ACS_UARROW, N_SCROLL_ARROWS)

    # Add the 'mainmenu' text as the title
    safe_addstr(top_sep_win,
                0, (stdscr.getmaxyx()[1] - len(kconf.mainmenu_text))//2,
                kconf.mainmenu_text)

    top_sep_win.noutrefresh()


    #
    # Update the symbol window
    #

    menu_win.erase()

    for i in range(scroll, min(scroll + sym_win_height(), len(visible))):
        attr = MENU_LIST_SEL_STYLE if i == node_i else curses.A_NORMAL
        safe_addstr(menu_win, i - scroll, 0, node_str(visible[i]), attr)

    menu_win.noutrefresh()


    #
    # Update the bottom separator window
    #

    bot_sep_win.erase()

    # Draw arrows pointing down if the symbol window is scrolled up
    if scroll < max_scroll():
        safe_hline(bot_sep_win, 0, 4, curses.ACS_DARROW, N_SCROLL_ARROWS)

    bot_sep_win.noutrefresh()


    #
    # Update the help window
    #

    help_win.erase()

    safe_addstr(help_win, 0, 0, "[Space/Enter] Toggle/enter   [ESC] Leave menu   [S] Save   [?] Symbol info")
    safe_addstr(help_win, 1, 0, "[Q] Quit")

    help_win.noutrefresh()

def parent_menu(node):
    # !!!

    menu = node.parent
    while not menu.is_menuconfig:
        menu = menu.parent
    return menu

def visible_nodes(menu):
    # Returns a list of the menu nodes in the menu 'menu' that should be
    # visible in the interface

    def rec(node):
        res = []

        while node:
            # Show the node if its prompt is visible. For menus, also check
            # 'visible if'.
            if node.prompt and expr_value(node.prompt[1]) and not \
               (node.item == MENU and not expr_value(node.visibility)):
                res.append(node)

                # If a node has children but doesn't have the is_menuconfig
                # flag set, the children come from a submenu created implicitly
                # from dependencies. Show those in this menu too.
                if node.list and not node.is_menuconfig:
                    res.extend(rec(node.list))

            node = node.next

        return res

    return rec(menu.list)

def change_node(node):
    global cur_menu
    global visible
    global node_i
    global scroll

    if isinstance(node.item, (Symbol, Choice)):
        sym = node.item

        if sym.type in (INT, HEX, STRING):
            info_text = range_info_str(sym) if sym.type in (INT, HEX) else None

            s = sym.str_value

            while True:
                s = input_dialog("Value for '{}' ({})".format(
                        node.prompt[0], TYPE_TO_STR[sym.type]),
                    s, info_text)

                if s is None:
                    break

                if sym.type in (INT, HEX):
                    s = s.strip()

                if sym.type == HEX and not s.startswith(("0x", "0X")):
                    s = "0x" + s

                if sym.type in (INT, HEX) and not verify_int_hex(s, sym):
                    continue

                sym.set_value(s)
                break

        elif len(sym.assignable) == 1:
            # Handles choice symbols for choices in y mode, which are a special
            # case: .assignable can be (2,) while .tri_value is 0.
            sym.set_value(sym.assignable[0])

        else:
            val_index = sym.assignable.index(sym.tri_value)
            new_val = sym.assignable[(val_index + 1) % len(sym.assignable)]
            sym.set_value(new_val)

        # Changing the value of the item might have changed what items in the
        # current menu are visible. Recalculate the state.

        sel_node = visible[node_i]

        # Row on the screen the cursor was on
        old_row = node_i - scroll

        # New visible nodes
        visible = visible_nodes(cur_menu)

        # New index of node
        node_i = visible.index(sel_node)

        # Try to make the cursor stay on the same row. This might be impossible
        # if two many nodes have disappeared above the node.
        scroll = max(visible.index(sel_node) - old_row, 0)

def input_dialog(title, initial_text, info_text=None):
    win = curses.newwin(1, 1)
    win.bkgdset(" ", DIALOG_BODY_STYLE)
    win.keypad(True)

    resize_input_dialog(win, title, info_text)

    safe_curs_set(2)

    s = initial_text
    i = len(initial_text)
    hscroll = 0

    while True:
        edit_width = win.getmaxyx()[1] - 4
        if i < hscroll:
            hscroll = i
        elif i >= hscroll + edit_width:
            hscroll = i - edit_width + 1

        draw_main()
        draw_input_dialog(win, title, info_text, s, i, hscroll)
        curses.doupdate()


        c = win.get_wch()

        if c == "\n":
            safe_curs_set(0)
            return s

        if c == "\x1B":  # \x1B = ESC
            safe_curs_set(0)
            return None


        if c == curses.KEY_RESIZE:
            resize_main()
            resize_input_dialog(win, title, info_text)

        elif c == curses.KEY_LEFT:
            if i > 0:
                i -= 1

        elif c == curses.KEY_RIGHT:
            if i < len(s):
                i += 1

        elif c in (curses.KEY_HOME, "\x01"):  # \x01 = CTRL-A
            i = 0

        elif c in (curses.KEY_END, "\x05"):  # \x05 = CTRL-E
            i = len(s)

        elif c in (curses.KEY_BACKSPACE, ERASE_CHAR):
            if i > 0:
                s = s[:i-1] + s[i:]
                i -= 1

        elif c == curses.KEY_DC:
            s = s[:i] + s[i+1:]

        elif c == "\x0B":  # \x0B = CTRL-K
            s = s[:i]

        elif c == "\x15":  # \x15 = CTRL-U
            s = s[i:]
            i = 0

        elif isinstance(c, str):
            # Insert character

            s = s[:i] + c + s[i:]
            i += 1

def resize_input_dialog(win, title, info_text):
    screen_height, screen_width = stdscr.getmaxyx()

    win_height = min(5 if info_text is None else 7, screen_height)

    win_width = max(INPUT_DIALOG_MIN_WIDTH, len(title) + 4)
    if info_text is not None:
        win_width = max(win_width, len(info_text) + 4)
    win_width = min(win_width, screen_width)

    win.resize(win_height, win_width)
    win.mvwin((screen_height - win_height)//2,
              (screen_width - win_width)//2)

def draw_input_dialog(win, title, info_text, s, i, hscroll):
    win.erase()
    draw_frame(win, title)

    edit_width = win.getmaxyx()[1] - 4

    visible_s = s[hscroll:hscroll + edit_width]
    safe_addstr(win, 2, 2, visible_s + " "*(edit_width - len(visible_s)),
                INPUT_FIELD_STYLE)

    if info_text is not None:
        safe_addstr(win, 4, 2, info_text)

    safe_move(win, 2, 2 + i - hscroll)

    win.noutrefresh()

def draw_frame(win, title):
    win_height, win_width = win.getmaxyx()

    win.attron(DIALOG_FRAME_STYLE)

    # Draw top/bottom edge
    safe_hline(win, 0,              0, " ", win_width)
    safe_hline(win, win_height - 1, 0, " ", win_width)

    # Draw left/right edge
    safe_vline(win, 0,             0, " ", win_height)
    safe_vline(win, 0, win_width - 1, " ", win_height)

    # Draw title
    safe_addstr(win, 0, (win_width - len(title))//2, title)

    win.attroff(DIALOG_FRAME_STYLE)

def info_display(node):
    top_line_win = curses.newwin(1, 1)
    top_line_win.bkgdset(" ", INFO_TOP_LINE_STYLE)

    text_win = curses.newwin(1, 1)
    text_win.bkgdset(" ", INFO_TEXT_STYLE)
    text_win.keypad(True)

    bot_sep_win = curses.newwin(1, 1)
    bot_sep_win.bkgdset(" ", INFO_BOT_SEP_STYLE)

    help_win = curses.newwin(1, 1)
    help_win.bkgdset(" ", INFO_HELP_STYLE)

    resize_info_display(top_line_win, text_win, bot_sep_win, help_win)


    lines = info_str(node).split("\n")

    scroll = 0

    while True:
        draw_info_display(node, lines, scroll, top_line_win, text_win,
                          bot_sep_win, help_win)
        curses.doupdate()


        c = text_win.get_wch()

        if c == curses.KEY_RESIZE:
            resize_info_display(top_line_win, text_win, bot_sep_win, help_win)

        elif c in (curses.KEY_DOWN, "j", "J"):
            if scroll < max_info_scroll(text_win, lines):
                scroll += 1

        elif c in (curses.KEY_NPAGE, "\x04"):  # Page Down/Ctrl-D
            scroll = min(scroll + PG_JUMP, max_info_scroll(text_win, lines))

        elif c in (curses.KEY_PPAGE, "\x15"):  # Page Up/Ctrl-U
            scroll = max(scroll - PG_JUMP, 0)

        elif c in (curses.KEY_END, "G"):
            scroll = max_info_scroll(text_win, lines)

        elif c in (curses.KEY_HOME, "g"):
            scroll = 0

        elif c in (curses.KEY_UP, "k", "K"):
            if scroll > 0:
                scroll -= 1

        elif c in ("q", "Q", "\x1B"):  # \x1B = ESC
            # !!!
            resize_main()
            return

def resize_info_display(top_line_win, text_win, bot_sep_win, help_win):
    screen_height, screen_width = stdscr.getmaxyx()

    top_line_win.resize(1, screen_width)
    bot_sep_win.resize(1, screen_width)
    help_win.resize(1, screen_width)

    text_win_height = screen_height - 3

    if screen_height > 3:
        text_win.resize(screen_height - 2, screen_width)

        text_win.mvwin(1, 0)
        bot_sep_win.mvwin(screen_height - 2, 0)
        help_win.mvwin(screen_height - 1, 0)
    else:
        # Degenerate case. Give up on nice rendering and just prevent errors.

        text_win.resize(1, screen_width)

        text_win.mvwin(0, 0)
        bot_sep_win.mvwin(0, 0)
        help_win.mvwin(0, 0)

def draw_info_display(node, lines, scroll, top_line_win, text_win,
                      bot_sep_win, help_win):

    text_win_height, text_win_width = text_win.getmaxyx()


    #
    # Update line at the top
    #

    top_line_win.erase()

    # Draw arrows pointing up if the information window is scrolled down. Draw
    # them before drawing the title, so the title ends up on top for small
    # windows.
    if scroll > 0:
        safe_hline(top_line_win, 0, 4, curses.ACS_UARROW, N_SCROLL_ARROWS)

    if isinstance(node.item, Symbol):
        title = "{}{}".format(kconf.config_prefix, node.item.name)

    elif isinstance(node.item, Choice):
        if node.item.name is not None:
            title = node.item.name
        else:
            title = "Choice"

    elif node.item == MENU:
        title = 'menu "{}"'.format(node.prompt[0])

    elif node.item == COMMENT:
        title = 'comment "{}"'.format(node.prompt[0])

    safe_addstr(top_line_win, 0, (text_win_width - len(title))//2, title)

    top_line_win.noutrefresh()


    #
    # Update text display
    #

    text_win.erase()

    for i, line in enumerate(lines[scroll:scroll + text_win_height]):
        safe_addstr(text_win, i, 0, line)

    text_win.noutrefresh()


    #
    # Update bottom separator line
    #

    bot_sep_win.erase()

    # Draw arrows pointing down if the symbol window is scrolled up
    if scroll < max_info_scroll(text_win, lines):
        safe_hline(bot_sep_win, 0, 4, curses.ACS_DARROW, N_SCROLL_ARROWS)

    bot_sep_win.noutrefresh()


    #
    # Update help window at bottom
    #

    help_win.erase()

    safe_addstr(help_win, 0, 0, "[ESC/q] Return to menu")

    help_win.noutrefresh()


def max_info_scroll(text_win, lines):
    return max(0, len(lines) - text_win.getmaxyx()[0])

def info_str(node):
    if isinstance(node.item, Symbol):
        sym = node.item

        return (
            prompt_info_str(sym) +
            "Type: {}\n".format(TYPE_TO_STR[sym.type]) +
            'Value: "{}"\n\n'.format(sym.str_value) +
            help_info_str(sym) +
            direct_dep_info_str(sym) +
            defaults_info_str(sym) +
            select_imply_info_str(sym) +
            loc_info_str(sym) +
            kconfig_def_info_str(sym)
        )

    if isinstance(node.item, Choice):
        choice = node.item

        return (
            prompt_info_str(choice) +
            "Type: {}\n".format(TYPE_TO_STR[choice.type]) +
            'Mode: "{}"\n\n'.format(choice.str_value) +
            help_info_str(choice) +
            choice_syms_info_str(choice) +
            direct_dep_info_str(choice) +
            defaults_info_str(choice) +
            loc_info_str(choice) +
            kconfig_def_info_str(choice)
        )

    return "Defined at {}:{}\nMenu: {}\n\n{}" \
           .format(node.filename, node.linenr, menu_path_info_str(node),
                   kconfig_def_info_str(node))

def prompt_info_str(sc):
    s = ""

    for node in sc.nodes:
        if node.prompt:
            s += "Prompt: {}\n".format(node.prompt[0])

    return s

def choice_syms_info_str(choice):
    s = "Choice symbols:\n"

    for sym in choice.syms:
        s += " - " + sym.name
        if sym is choice.selection:
            s += " (selected)"
        s += "\n"

    return s + "\n"

def help_info_str(sc):
    s = ""

    for node in sc.nodes:
        if node.help is not None:
            s += "Help:\n\n{}\n\n" \
                 .format(textwrap.indent(node.help, "   "))

    return s

def direct_dep_info_str(sc):
    if sc.direct_dep is kconf.y:
        return ""

    return 'Direct dependencies (value: "{}"):\n{}\n' \
           .format(TRI_TO_STR[expr_value(sc.direct_dep)],
                   split_expr_str(sc.direct_dep, 0))

def defaults_info_str(sc):
    if not sc.defaults:
        return ""

    s = "Defaults:\n"

    for value, cond in sc.defaults:
        s += " - "
        if isinstance(sc, Symbol):
            s += expr_str(value)
        else:
            # !!!
            s += value.name
        s += "\n"

        if cond is not kconf.y:
            s += '     Condition (value: "{}"):\n{}' \
                 .format(TRI_TO_STR[expr_value(cond)],
                         split_expr_str(cond, 7))

    return s + "\n"

def split_expr_str(expr, indent):
    # Split 'expr' into either its top-level && or || operands. This is usually
    # enough to get something readable. A fancier recursive thingy would be
    # possible too.

    if len(split_expr(expr, AND)) > 1:
        split_op = AND
        op_str = "&&"
    else:
        split_op = OR
        op_str = "||"

    s = ""
    for i, term in enumerate(split_expr(expr, split_op)):
        s += '{}{} {} (value: "{}")\n' \
             .format(" "*indent,
                     "  " if i == 0 else op_str,
                     expr_str(term),
                     TRI_TO_STR[expr_value(term)])
    return s

def select_imply_info_str(sym):
    s = ""

    def add_sis(expr, val, title):
        nonlocal s

        # sis = selects/implies
        sis = [si for si in split_expr(expr, OR) if expr_value(si) == val]

        if sis:
            s += title
            for si in sis:
                s += " - {}\n".format(split_expr(si, AND)[0].name)
            s += "\n"

    if sym.rev_dep is not kconf.n:
        add_sis(sym.rev_dep, 2, "Symbols currently y-selecting this symbol:\n")
        add_sis(sym.rev_dep, 1, "Symbols currently m-selecting this symbol:\n")
        add_sis(sym.rev_dep, 0, "Symbols currently n-selecting this symbol (no effect):\n")

    if sym.weak_rev_dep is not kconf.n:
        add_sis(sym.weak_rev_dep, 2, "Symbols currently y-implying this symbol:\n")
        add_sis(sym.weak_rev_dep, 1, "Symbols currently m-implying this symbol:\n")
        add_sis(sym.weak_rev_dep, 0, "Symbols currently n-implying this symbol (no effect):\n")

    return s

def loc_info_str(sc):
    s = "Definition location{}:\n".format("s" if len(sc.nodes) > 1 else "")

    for node in sc.nodes:
        s += " - {}:{}\n     Menu: {}\n" \
                .format(node.filename, node.linenr, menu_path_info_str(node))

    return s + "\n"

def kconfig_def_info_str(item):
    return "Kconfig definition (with propagated dependencies):\n\n" + \
           textwrap.indent(str(item).expandtabs(), "  ")

def menu_path_info_str(node):
    path = ""

    menu = cur_menu
    while menu is not kconf.top_node:
        # TODO: Can the prompt be missing in show-all mode?
        path = " -> " + menu.prompt[0] + path
        menu = menu.parent

    return "(top menu)" + path

def key_dialog(title, text, keys):
    win = curses.newwin(1, 1)
    win.bkgdset(" ", DIALOG_BODY_STYLE)
    win.keypad(True)

    resize_key_dialog(win, text)

    while True:
        draw_main()
        draw_key_dialog(win, title, text)
        curses.doupdate()


        c = win.get_wch()

        if c == "\x1B":  # \x1B = ESC
            return None


        if c == curses.KEY_RESIZE:
            resize_main()
            resize_key_dialog(win, text)

        elif isinstance(c, str):
            c = c.lower()
            if c in keys:
                return c

def resize_key_dialog(win, text):
    screen_height, screen_width = stdscr.getmaxyx()

    lines = text.split("\n")

    win_height = min(len(lines) + 4, screen_height)
    win_width = min(max(len(line) for line in lines) + 4, screen_width)

    win.resize(win_height, win_width)
    win.mvwin((screen_height - win_height)//2,
              (screen_width - win_width)//2)

def draw_key_dialog(win, title, text):
    win.erase()
    draw_frame(win, title)

    for i, line in enumerate(text.split("\n")):
        safe_addstr(win, 2 + i, 2, line)

    win.noutrefresh()

def error(text):
    key_dialog("Error", text, " \n")

def try_write(write_fn, filename, description):
    try:
        write_fn(filename)
        return True
    except OSError as e:
        error("Error saving {} to '{}'\n\n{} (errno: {})"
              .format(description, e.filename, e.strerror,
                      errno.errorcode[e.errno]))
        return False

def node_str(node):
    # Returns the complete menu entry text for a menu node.
    #
    # Example return value: "[*] Support for X"

    # !!!
    indent = 0
    parent = node.parent
    while not parent.is_menuconfig:
        indent += 2
        parent = parent.parent

    s = "{:{}} ".format(value_str(node), 3 + indent)

    if node.prompt:
        if node.item == COMMENT:
            s += "*** {} ***".format(node.prompt[0])
        else:
            # !!! handle missing prompt later, when "show all" mode is
            # supported?
            s += node.prompt[0]

        if isinstance(node.item, Symbol) and node.item.user_value is None \
           and not (node.item.choice and node.item.choice.tri_value == 2):
            s += " (NEW)"

        if isinstance(node.item, Choice) and node.item.tri_value == 2:
            sym = node.item.selection
            # !!! multi def symbols defined outside choice
            if sym:
                for node_ in sym.nodes:
                    if node_.prompt:
                        s += " ({})".format(node_.prompt[0])

    if node.is_menuconfig:
        s += "  --->" if visible_nodes(node) else "  ---> (empty)"

    return s

def value_str(node):
    # Returns the value part ("[*]", "<M>", "(foo)" etc.) of a menu node

    item = node.item

    if item in (MENU, COMMENT):
        return ""

    # !!!
    if item.type == UNKNOWN:
        return ""

    if item.type in (STRING, INT, HEX):
        return "({})".format(item.str_value)

    # BOOL or TRISTATE

    # The choice mode is an upper bound on the visibility of choice symbols, so
    # we can check the choice symbols' own visibility to see if the choice is
    # in y mode
    if is_y_mode_choice_sym(item):
        return "(X)" if item.choice.selection is item else "( )"

    tri_val_str = (" ", "M", "*")[item.tri_value]

    if len(item.assignable) == 1:
        # Pinned to a single value
        return "" if isinstance(item, Choice) else "-{}-".format(tri_val_str)

    if item.type == BOOL:
        return "[{}]".format(tri_val_str)

    if item.type == TRISTATE:
        if item.assignable == (1, 2):
            return "{{{}}}".format(tri_val_str)  # { }/{M}/{*}
        return "<{}>".format(tri_val_str)

def is_y_mode_choice_sym(item):
    # The choice mode is an upper bound on the visibility of choice symbols, so
    # we can check the choice symbols' own visibility to see if the choice is
    # in y mode
    return isinstance(item, Symbol) and item.choice and item.visibility == 2

def verify_int_hex(s, sym):
    base = 10 if sym.type == INT else 16

    try:
        int(s, base)
    except ValueError:
        error("'{}' is a malformed {} value"
              .format(s, TYPE_TO_STR[sym.type]))
        return False

    for low_sym, high_sym, cond in sym.ranges:
        if expr_value(cond):
            low = int(low_sym.str_value, base)
            val = int(s, base)
            high = int(high_sym.str_value, base)

            if not low <= val <= high:
                error("{} is outside the range {}-{}"
                      .format(s, low_sym.str_value, high_sym.str_value))

                return False

            break

    return True

def range_info_str(sym):
    for low, high, cond in sym.ranges:
        if expr_value(cond):
            return "Range: {}-{}".format(low.str_value, high.str_value)

    return "No range constraints."

def is_num(name):
    # Heuristic to see if a symbol name looks like a number, for nicer output
    # when printing expressions. Things like 16 are actually symbol references,
    # only they get their name as their value.

    try:
        int(name, 10)
        return True

    except ValueError:
        if not name.startswith(("0x", "0X")):
            return False

        try:
            int(name, 16)
            return True

        except ValueError:
            return False

# !!! explain

def safe_curs_set(visibility):
    try:
        curses.curs_set(visibility)
    except curses.error:
        pass

def safe_addstr(win, *args):
    try:
        win.addstr(*args)
    except curses.error:
        pass

def safe_addch(win, *args):
    try:
        win.addch(*args)
    except curses.error:
        pass

def safe_hline(win, *args):
    try:
        win.hline(*args)
    except curses.error:
        pass

def safe_vline(win, *args):
    try:
        win.vline(*args)
    except curses.error:
        pass

def safe_move(win, *args):
    try:
        win.move(*args)
    except curses.error:
        pass

if __name__ == "__main__":
    if len(sys.argv) > 2:
        print("usage: {} [Kconfig]".format(sys.argv[0]), file=sys.stderr)
        sys.exit(1)

    # TODO: Enable warnings
    # Other warning stuff?
    kconf = Kconfig("Kconfig" if len(sys.argv) < 2 else sys.argv[1], warn=False)

    if os.path.isfile(".config"):
        print("Using existing .config as base")
        kconf.load_config(".config")
    elif kconf.defconfig_filename is not None:
        print("Using defaults found in {} as base"
              .format(kconf.defconfig_filename))
        kconf.load_config(kconf.defconfig_filename)

    print(menuconfig(kconf))


# TODO: remembering positions in menus we've been in before, even if they're not parent menus
# TODO: string encoding stuff
# TODO: addchstr() unsupported
# TODO: check for pointless globals
# TODO: check that menus that depend on symbols work
# TODO: mousing in input dialog
# TODO: are symbols without a type showing up?
# TODO: don't reference search dialog when it's not implemented
# TODO: have a type of dialog that accepts any of a number of keys
# TODO: addnstr() might be useful
# TODO: accept H in help dialog to jump back

# idea: some kind of dictionary with old positions for menus?

# https://www.gnu.org/software/make/manual/html_node/Reference.html#Reference
