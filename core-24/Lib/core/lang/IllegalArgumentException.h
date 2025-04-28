//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ILLEGALARGUMENTEXCEPTION_H
#define CORE_LANG_ILLEGALARGUMENTEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    class IllegalArgumentException : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT IllegalArgumentException(const String& message);
        CORE_EXPLICIT IllegalArgumentException(const String& message, const Throwable& cause);
        CORE_EXPLICIT IllegalArgumentException(const Throwable& cause);
        ~IllegalArgumentException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ILLEGALARGUMENTEXCEPTION_H
