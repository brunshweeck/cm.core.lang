//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_CLONENOTSUPPORTEDEXCEPTION_H
#define CORE_LANG_CLONENOTSUPPORTEDEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    class CloneNotSupportedException $final : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT CloneNotSupportedException(const String& message);
        ~CloneNotSupportedException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_CLONENOTSUPPORTEDEXCEPTION_H
