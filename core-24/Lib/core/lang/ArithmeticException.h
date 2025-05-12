//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ARITHMETICEXCEPTION_H
#define CORE_LANG_ARITHMETICEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    /// Thrown when an exceptional arithmetic condition has occurred.
    /// For example, an integer "divide by zero" throws an instance of this class.
    class ArithmeticException $final : public lang::RuntimeException
    {
    public:
        /// Constructs an @c ArithmeticException with the specified detail message.
        /// @param message the detail message
        CORE_EXPLICIT ArithmeticException(const String &message);

        ~ArithmeticException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ARITHMETICEXCEPTION_H
