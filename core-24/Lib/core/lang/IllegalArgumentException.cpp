//
// Created by brunshweeck on 4/27/25.
//

#include "IllegalArgumentException.h"

#include "../misc/VarHandle.h"

namespace core
{
    IllegalArgumentException::IllegalArgumentException(const String &message): RuntimeException(message) {
    }

    IllegalArgumentException::IllegalArgumentException(const String &message, const Throwable &cause)
        : RuntimeException(message, cause) {
    }

    IllegalArgumentException::IllegalArgumentException(const Throwable &cause): RuntimeException(cause) {
    }

    lang::Exception &IllegalArgumentException::clone() const {
        return VH::newObject<IllegalArgumentException>(*this);
    }

    void IllegalArgumentException::selfThrow() const { throw *this; }
} // core
