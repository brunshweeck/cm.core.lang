//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_VOID_H
#define CORE_LANG_VOID_H
#include "Object.h"

namespace core
{
    class Void : public Object
    {
        Void() = default;

    public:
        ~Void() override = default;

        CORE_SET_AS_NON_COPYABLE_CLASS(Void);
    };
} // core

#endif // CORE_LANG_VOID_H
