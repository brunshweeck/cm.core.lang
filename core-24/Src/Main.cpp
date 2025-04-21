#include <cstdio>
#include <cstdlib>

#include "../Lib/core/lang/Class.h"

using namespace core::lang::spi;
using namespace core::lang;
using namespace core;

int main() {
    char c[23];
    CORE_FAST ClassOf(c)::NoArray d = {};
    CORE_FAST ClassOf(d)::NoArray e = {};
    CORE_FAST ClassOf(1)::Identity size = Class<gchar[23]>::SIZE;
    CORE_FAST ClassOf(1)::Identity count = Class<gchar[23]>::COUNT;
    return 0;
}