//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
#define CORE_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    /// Thrown to indicate that the requested operation is not supported.
    class UnsupportedOperationException $final : public lang::RuntimeException
    {
    public:
        /// Constructs an UnsupportedOperationException with the specified detail message.
        /// @param message the detail message
        CORE_EXPLICIT UnsupportedOperationException(const String &message);

        /// Constructs a new exception with the specified detail message and cause.
        /// @note the detail message associated with <code>cause</code> is <i>not</i> automatically incorporated in this exception's detail message.
        /// @param message the detail message
        /// @param cause the cause
        CORE_EXPLICIT UnsupportedOperationException(const String &message, const Throwable &cause);

        /// Constructs a new exception with the specified cause and a detail message of @c cause.toString() (which typically contains the class and detail message of @c cause).
        /// This constructor is useful for exceptions that are little more than wrappers for other throwables.
        /// @note the detail message associated with <code>cause</code> is <i>not</i> automatically incorporated in this exception's detail message.
       /// @param cause the cause
        CORE_EXPLICIT UnsupportedOperationException(const Throwable &cause);

        ~UnsupportedOperationException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
