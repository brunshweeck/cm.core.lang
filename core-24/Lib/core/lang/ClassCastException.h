//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_CLASSCASTEXCEPTION_H
#define CORE_LANG_CLASSCASTEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    /// Thrown to indicate that the code has attempted to cast an object to a subclass of which it is not an instance.
    /// For example, the following code generates a @c ClassCastException
    class ClassCastException $final : public lang::RuntimeException
    {
    public:
        /// Construct a new instance of @c ClassCastException with given details message.
        /// @param message the details message
        CORE_EXPLICIT ClassCastException(const String &message);

        ~ClassCastException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_CLASSCASTEXCEPTION_H
