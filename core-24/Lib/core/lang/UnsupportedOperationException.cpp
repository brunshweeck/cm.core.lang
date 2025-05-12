//
// Created by brunshweeck on 4/27/25.
//

#include "UnsupportedOperationException.h"

#include "../misc/VarHandle.h"

namespace core
{
    UnsupportedOperationException::UnsupportedOperationException(const String &message) : RuntimeException(message) {
    }

    UnsupportedOperationException::UnsupportedOperationException(const String &message, const Throwable &cause)
        : RuntimeException(message, cause) {
    }

    UnsupportedOperationException::UnsupportedOperationException(const Throwable &cause)
        : RuntimeException(cause) {
    }

    lang::Exception &UnsupportedOperationException::clone() const {
        return VH::newObject<UnsupportedOperationException>(*this);
    }

    void UnsupportedOperationException::selfThrow() const { throw *this; }
} // core
