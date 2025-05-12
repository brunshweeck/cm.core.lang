//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_RUNTIMEEXCEPTION_H
#define CORE_LANG_RUNTIMEEXCEPTION_H
#include "Exception.h"

namespace core
{
    namespace lang
    {
        /// @c RuntimeException is the superclass of those exceptions that can be thrown during the normal operation.
        class RuntimeException : public Exception
        {
        public:
            /// Constructs a new runtime exception with the specified detail message.
            /// @param message The detail message. The detail message is saved for later retrieval by the @c getMessage() method.
            explicit RuntimeException(const String &message);

            /// Constructs a new runtime exception with the specified detail message and cause.
            /// @note the detail message associated with @c cause is @em not automatically incorporated in this runtime exception's detail message.
            /// @param message The detail message. The detail message is saved for later retrieval by the @c getMessage() method.
            /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
            explicit RuntimeException(const String &message, const Throwable &cause);

            /// Constructs a new runtime exception with the specified cause and a  detail message of @c cause.toString() (which typically contains the class and detail message of @c cause .
            /// This constructor is useful for runtime exceptions that are little more than wrappers for other throwables.
            /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
            explicit RuntimeException(const Throwable &cause);

            ~RuntimeException() override = default;

            Exception &clone() const override;

        private:
            void selfThrow() const override;
        };
    } // lang
} // core

#endif // CORE_LANG_RUNTIMEEXCEPTION_H
