//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ILLEGALARGUMENTEXCEPTION_H
#define CORE_LANG_ILLEGALARGUMENTEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    /// Thrown to indicate that a method has been passed an illegal or inappropriate argument.
    class IllegalArgumentException : public lang::RuntimeException
    {
    public:
        /// Constructs an @c IllegalArgumentException with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT IllegalArgumentException(const String &message);

        /// Constructs a new exception with the specified detail message and cause.
        /// @param message the detail message (which is saved for later retrieval by the @c getMessage() method).
        /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
        CORE_EXPLICIT IllegalArgumentException(const String &message, const Throwable &cause);

        /// Constructs a new exception with the specified cause and a detail message of @c cause.toString() (which typically contains the class and detail message of @c cause).
        /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
        CORE_EXPLICIT IllegalArgumentException(const Throwable &cause);

        ~IllegalArgumentException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ILLEGALARGUMENTEXCEPTION_H
