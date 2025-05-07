//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ARITHMETICEXCEPTION_H
#define CORE_LANG_ARITHMETICEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    class ArithmeticException $final : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT ArithmeticException(const String& message);
        ~ArithmeticException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ARITHMETICEXCEPTION_H
