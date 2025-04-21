//
// Created by brunshweeck on 4/21/25.
//

#ifndef CORE_LANG_DOUBLE_H
#define CORE_LANG_DOUBLE_H

#include "Comparable.h"
#include "Number.h"

namespace core
{
    class Double $final: public lang::Comparable<Double>, public lang::Number
    {
    };
} // core

#endif // CORE_LANG_DOUBLE_H
