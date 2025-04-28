//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_OUTOFMEMORYERROR_H
#define CORE_LANG_OUTOFMEMORYERROR_H
#include "Error.h"

namespace core
{
    class OutOfMemoryError $final : public lang::Error
    {
    public:
        CORE_EXPLICIT OutOfMemoryError(const String& message);
        ~OutOfMemoryError() override = default;
        Error& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_OUTOFMEMORYERROR_H
