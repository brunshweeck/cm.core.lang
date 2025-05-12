//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ILLEGALSTATEEXCEPTION_H
#define CORE_LANG_ILLEGALSTATEEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    /// Signals that a method has been invoked at an illegal or inappropriate time.
    /// In other words, the environment or application is not in an appropriate state for the requested operation.
    class IllegalStateException $final : public lang::RuntimeException
    {
    public:
        /// Constructs an IllegalStateException with the specified detail message.
        /// A detail message is a String that describes this particular exception.
        /// @param message the String that contains a detailed message
        CORE_EXPLICIT IllegalStateException(const String &message);

        /// Constructs a new exception with the specified detail message and cause.
        /// @note the detail message associated with @c cause is @em not automatically incorporated in this exception's detail message.
        /// @param message the detail message (which is saved for later retrieval by the @c getMessage() method).
        /// @param cause the cause (which is saved for later retrieval by the  @c getCause() method).
        CORE_EXPLICIT IllegalStateException(const String &message, const Throwable &cause);

        /// Constructs a new exception with the specified cause and a detail message of @c cause.toString() (which typically contains the class and detail message of @c cause).
        /// This constructor is useful for exceptions that are little more than  for other throwables.
        /// @param cause the cause (which is saved for later retrieval by the  @c getCause() method).
        CORE_EXPLICIT IllegalStateException(const Throwable &cause);

        ~IllegalStateException() override = default;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ILLEGALSTATEEXCEPTION_H
