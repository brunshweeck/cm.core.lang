//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ILLEGALSTATEEXCEPTION_H
#define CORE_LANG_ILLEGALSTATEEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    class IllegalStateException $final : public lang::RuntimeException
    {
    public:
        explicit IllegalStateException(const String& message);
        explicit IllegalStateException(const String& message, const Throwable& cause);
        explicit IllegalStateException(const Throwable& cause);
        ~IllegalStateException() override = default;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ILLEGALSTATEEXCEPTION_H
