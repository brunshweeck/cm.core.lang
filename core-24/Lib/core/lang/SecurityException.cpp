//
// Created by brunshweeck on 4/27/25.
//

#include "SecurityException.h"

#include "../misc/VarHandle.h"

namespace core
{
    SecurityException::SecurityException(const String &message): RuntimeException(message) {
    }

    SecurityException::SecurityException(const String &message, const Throwable &cause)
        : RuntimeException(message, cause) {
    }

    SecurityException::SecurityException(const Throwable &cause): RuntimeException(cause) {
    }

    lang::Exception &SecurityException::clone() const {
        return VH::newObject<SecurityException>(*this);
    }

    void SecurityException::selfThrow() const { throw *this; }
} // core
