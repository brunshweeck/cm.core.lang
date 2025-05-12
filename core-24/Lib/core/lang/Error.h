//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ERROR_H
#define CORE_LANG_ERROR_H
#include "Throwable.h"


namespace core::lang
{
    /// An @c Error is a subclass of @c Throwable that indicates serious problems that a reasonable application should not try to catch.
    /// Most such errors are abnormal conditions.
    class Error : public Throwable
    {
    public:
        /// Constructs a new error with the specified detail message.
        /// @param message The detail message. The detail message is saved for later retrieval by the @c getMessage() method.
        CORE_EXPLICIT Error(const String &message);

        /// Constructs a new error with the specified detail message and cause.
        /// @note the detail message associated with @c cause is <i>not</i> automatically incorporated in this error's detail message.
        /// @param message the detail message (which is saved for later retrieval by the @c getMessage() method).
        /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
        CORE_EXPLICIT Error(const String &message, const Throwable &cause);

        /// Constructs a new error with the specified cause and a detail message of @c cause.toString() (which typically contains the class and detail message of @c cause).
        /// This constructor is useful for errors that are little more than wrappers for other throwables.
        /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
        CORE_EXPLICIT Error(const Throwable &cause);

        Error(const Error &other);

        Error(Error &&other) CORE_NOTHROW;

        ~Error() override = default;

        Error &clone() const override;

    private:
        void selfThrow() const override;
    };
} // lang
// core

#endif // CORE_LANG_ERROR_H
