//
// Created by brunshweeck on 4/30/25.
//

#ifndef CORE_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H
#define CORE_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H

#include <core/lang/IndexOutOfBoundsException.h>

namespace core
{
    class ArrayIndexOutOfBoundsException $final : public IndexOutOfBoundsException
    {
    public:
        CORE_EXPLICIT ArrayIndexOutOfBoundsException(const String& message);
        CORE_EXPLICIT ArrayIndexOutOfBoundsException(gint index);
        ~ArrayIndexOutOfBoundsException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H
