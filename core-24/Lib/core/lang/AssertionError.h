//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ASSERTIONERROR_H
#define CORE_LANG_ASSERTIONERROR_H

#include "Error.h"

namespace core
{
    class AssertionError $final : public lang::Error
    {
    public:
        CORE_EXPLICIT AssertionError(const String& message);
        CORE_EXPLICIT AssertionError(const Object& message);
        CORE_EXPLICIT AssertionError(gboolean message);
        CORE_EXPLICIT AssertionError(gchar message);
        CORE_EXPLICIT AssertionError(glong message);
        CORE_EXPLICIT AssertionError(gdouble message);
        ~AssertionError() override = default;
        Error& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ASSERTIONERROR_H
