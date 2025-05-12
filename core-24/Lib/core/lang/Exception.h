//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_EXCEPTION_H
#define CORE_LANG_EXCEPTION_H
#include "Throwable.h"


namespace core::lang
{
    /// The class @c Exception and its subclasses are a form of @c Throwable that indicates conditions that a reasonable application might want to catch.
    class Exception : public Throwable
    {
    public:
        /// Constructs a new exception with the specified detail message.
        /// @param message The detail message. The detail message is saved for later retrieval by the @c getMessage() method.
        CORE_EXPLICIT Exception(const String &message);

        /// Constructs a new exception with the specified detail message and cause.
        /// @param message message the detail message (which is saved for later retrieval by the @c getMessage() method).
        /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
        CORE_EXPLICIT Exception(const String &message, const Throwable &cause);

        /// Constructs a new exception with the specified cause and a detail message of @c cause.toString() (which typically contains the class and detail message of @c cause).
        /// This constructor is useful for exceptions that are little more than wrappers for other throwables.
        /// @param cause the cause (which is saved for later retrieval by the @c getCause() method).
        CORE_EXPLICIT Exception(const Throwable &cause);

        Exception(const Exception &other);

        Exception(Exception &&other) CORE_NOTHROW;

        ~Exception() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // lang
// core

#endif // CORE_LANG_EXCEPTION_H
