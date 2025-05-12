//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_SECURITYEXCEPTION_H
#define CORE_LANG_SECURITYEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    /// Thrown by the security manager to indicate a security violation.
    class SecurityException $final : public lang::RuntimeException
    {
    public:
        /// Constructs a @c SecurityException with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT SecurityException(const String &message);

        /// Creates a @c SecurityException with the specified detail message and cause.
        /// @param message the detail message
        /// @param cause the cause
        CORE_EXPLICIT SecurityException(const String &message, const Throwable &cause);

        /// Creates a {@code SecurityException} with the specified cause and a detail message of @c cause.toString() (which typically contains the class and detail message of @c cause).
        /// @param cause the cause
        CORE_EXPLICIT SecurityException(const Throwable &cause);

        ~SecurityException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_SECURITYEXCEPTION_H
