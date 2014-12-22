/* -*- mode: C++; c-basic-offset: 4; tab-width: 8; -*-
 * vi: set shiftwidth=4 tabstop=8:
 * :indentSize=4:tabSize=8:
 */
#include <iostream>
/**
 * print command line help text to stdout.
 * \todo keep this in sync with README.md
 */
void help()
{
    std::cout << "usage: fewer [--regex '/REGEX/flags']* [--df '/REGEX/REPLACE/flags']* [--tabwidth 'NUM'] 'FILE'" << std::endl
	      << "--regex      preset regular expressions to filter the file" << std::endl
	      << "--tabwidth   set the width of a tab character in spaces" << std::endl
	      << "--df         preset a display filter regular expression and replace text" << std::endl
	      << "Study the man page fewer(1) for more details." << std::endl
	;
}