//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_SECURITYEXCEPTION_H
#define CORE_LANG_SECURITYEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    class SecurityException $final : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT SecurityException(const String& message);
        CORE_EXPLICIT SecurityException(const String& message, const Throwable& cause);
        CORE_EXPLICIT SecurityException(const Throwable& cause);
        ~SecurityException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_SECURITYEXCEPTION_H
