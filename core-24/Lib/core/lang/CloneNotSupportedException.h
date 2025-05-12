//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_CLONENOTSUPPORTEDEXCEPTION_H
#define CORE_LANG_CLONENOTSUPPORTEDEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    /// Thrown to indicate that the @c clone method in class @c Object has been called to clone an object, but that the object's class does not support this operation.
    /// Applications that override the @c clone method can also throw this exception to indicate that an object could not or should not be cloned.
    class CloneNotSupportedException $final : public lang::RuntimeException
    {
    public:
        /// Constructs a @c CloneNotSupportedException with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT CloneNotSupportedException(const String &message);

        ~CloneNotSupportedException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_CLONENOTSUPPORTEDEXCEPTION_H
