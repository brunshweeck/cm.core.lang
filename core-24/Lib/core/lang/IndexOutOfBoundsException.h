//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
#define CORE_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
#include "IllegalArgumentException.h"

namespace core
{
    class IndexOutOfBoundsException : public IllegalArgumentException
    {
    public:
        CORE_EXPLICIT IndexOutOfBoundsException(const String& message);
        CORE_EXPLICIT IndexOutOfBoundsException(glong index);
        ~IndexOutOfBoundsException() override = default;
        Exception& clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
