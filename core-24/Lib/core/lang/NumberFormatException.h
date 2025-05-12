//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_NUMBERFORMATEXCEPTION_H
#define CORE_LANG_NUMBERFORMATEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    /// Thrown to indicate that the application has attempted to convert a string to one of the numeric types, but that the string does not have the appropriate format.
    class NumberFormatException $final : public lang::RuntimeException
    {
    public:
        /// Constructs a @c NumberFormatException with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT NumberFormatException(const String &message);

        ~NumberFormatException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_NUMBERFORMATEXCEPTION_H
