//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ASSERTIONERROR_H
#define CORE_LANG_ASSERTIONERROR_H

#include "Error.h"

namespace core
{
    /// Thrown to indicate that an assertion has failed.
    /// The seven one-argument public constructors provided by this class ensure that the assertion error returned by the invocation:
    /// @code
    ///     AssertionError(expression)
    /// @endcode
    /// has as its detail message the <em>string conversion</em> of @em expression, regardless of the type of @em expression.
    class AssertionError $final : public lang::Error
    {
    public:
        /// Constructs an AssertionError with its detail message.
        /// @param message values to be used in constructing a detail message
        CORE_EXPLICIT AssertionError(const String &message);

        /// Constructs an AssertionError with its detail message derived from the specified object, which is converted to a string.
        /// @note If the specified object is an instance of @c Throwable, it becomes the @em cause of the newly constructed assertion error.
        /// @param message a value to be used in constructing a detail message
        CORE_EXPLICIT AssertionError(const Object &message);

        /// Constructs an AssertionError with its detail message derived from the specified boolean, which is converted to a string.
        /// @param message a value to be used in constructing a detail message
        CORE_EXPLICIT AssertionError(gboolean message);

        /// Constructs an AssertionError with its detail message derived from the specified character, which is converted to a string.
        /// @param message a value to be used in constructing a detail message
        CORE_EXPLICIT AssertionError(gchar message);

        /// Constructs an AssertionError with its detail message derived from the specified integer, which is converted to a string.
        /// @param message a value to be used in constructing a detail message
        CORE_EXPLICIT AssertionError(glong message);

        /// Constructs an AssertionError with its detail message derived from the specified float, which is converted to a string.
        /// @param message a value to be used in constructing a detail message
        CORE_EXPLICIT AssertionError(gdouble message);

        /// Constructs a new @c AssertionError with the specified detail message and cause.
        /// @note the detail message associated with @c cause is @em not automatically incorporated in this error's detail message.
        /// @param message the detail message
        /// @param throwable the cause
        CORE_EXPLICIT AssertionError(const String &message, const Throwable &throwable);

        ~AssertionError() override = default;

        Error &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ASSERTIONERROR_H
