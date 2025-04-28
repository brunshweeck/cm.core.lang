//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
#define CORE_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    class UnsupportedOperationException $final : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT UnsupportedOperationException(const String& message);
        CORE_EXPLICIT UnsupportedOperationException(const String& message, const Throwable& cause);
        CORE_EXPLICIT UnsupportedOperationException(const Throwable& cause);
        ~UnsupportedOperationException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
