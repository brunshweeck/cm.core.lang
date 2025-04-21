//
// Created by brunshweeck on 4/21/25.
//

#ifndef CORE_LANG_FLOAT_H
#define CORE_LANG_FLOAT_H

#include "Comparable.h"
#include "Number.h"

namespace core
{
    class Float $final: public lang::Comparable<Float>, public lang::Number
    {
    };
} // core

#endif // CORE_LANG_FLOAT_H
