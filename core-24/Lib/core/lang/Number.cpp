//
// Created by brunshweeck on 4/16/25.
//

#include "Number.h"

namespace core
{
    namespace lang
    {
        gbyte Number::byteValue() const { return (gbyte)intValue(); }

        gshort Number::shortValue() const { return (gshort)intValue(); }
    } // lang
} // core
