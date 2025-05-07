//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H
#define CORE_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H

#include <core/lang/IndexOutOfBoundsException.h>

namespace core
{
    class StringIndexOutOfBoundsException $final : public IndexOutOfBoundsException
    {
    public:
        CORE_EXPLICIT StringIndexOutOfBoundsException(const String& message);
        CORE_EXPLICIT StringIndexOutOfBoundsException(gint index);
        ~StringIndexOutOfBoundsException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H
