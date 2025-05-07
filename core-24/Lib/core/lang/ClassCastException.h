//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_CLASSCASTEXCEPTION_H
#define CORE_LANG_CLASSCASTEXCEPTION_H

#include "RuntimeException.h"

namespace core
{
    class ClassCastException $final : public lang::RuntimeException
    {
    public:
        CORE_EXPLICIT ClassCastException(const String& message);
        ~ClassCastException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_CLASSCASTEXCEPTION_H
