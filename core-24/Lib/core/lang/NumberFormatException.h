//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_NUMBERFORMATEXCEPTION_H
#define CORE_LANG_NUMBERFORMATEXCEPTION_H
#include "RuntimeException.h"

namespace core
{
    class NumberFormatException $final : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT NumberFormatException(const String& message);
        ~NumberFormatException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_NUMBERFORMATEXCEPTION_H
