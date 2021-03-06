/* -*- mode: C++; c-basic-offset: 4; tab-width: 8; -*-
 * vi: set shiftwidth=4 tabstop=8:
 * :indentSize=4:tabSize=8:
 */

#include "../getenv_str.h"
#include <cassert>

bool getenv_str(const std::string& name, std::string& value)
{
    if (name.empty()) { return false; }
    char *val = nullptr;
    size_t len = 0;
    errno_t e = _dupenv_s(&val, &len, name.c_str());
    if (e != 0) { return false; }
    if (!val) { return false; }
    if (len == 0) {
	value.erase();
    }
    else {
	assert(val);
	value = val;
    }
    return true;
}
