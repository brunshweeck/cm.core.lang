//
// Created by brunshweeck on 11/05/25.
//

#ifndef CORE_LANG_XSTRING_H
#define CORE_LANG_XSTRING_H
#include "String.h"

namespace core
{
    class XString $final : public lang::CharSequence
    {
    public:
        ~XString() override = default;
    };
} // core

#endif // CORE_LANG_XSTRING_H
