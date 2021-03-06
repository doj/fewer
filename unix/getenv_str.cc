/* -*- mode: C++; c-basic-offset: 4; tab-width: 8; -*-
 * vi: set shiftwidth=4 tabstop=8:
 * :indentSize=4:tabSize=8:
 */
#include "getenv_str.h"
#include <cstdlib>
bool getenv_str(const std::string& name, std::string& value)
{
    const char *v = getenv(name.c_str());
    if (! v) { return false; }
    value = v;
    return true;
}
