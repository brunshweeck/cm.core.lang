//
// Created by brunshweeck on 4/27/25.
//

#include "RuntimeException.h"

#include <core/misc/VarHandle.h>


namespace core::lang
{
    RuntimeException::RuntimeException(const String &message): Exception(message) {
    }

    RuntimeException::RuntimeException(const String &message, const Throwable &cause): Exception(message, cause) {
    }

    RuntimeException::RuntimeException(const Throwable &cause): Exception(cause) {
    }

    Exception &RuntimeException::clone() const {
        return VH::newObject<RuntimeException>(*this);
    }

    void RuntimeException::selfThrow() const { throw *this; }
} // lang
// core
