//
// Created by brunshweeck on 4/27/25.
//

#include "IllegalStateException.h"

namespace core
{
    IllegalStateException::IllegalStateException(const String &message): RuntimeException(message) {
    }

    IllegalStateException::IllegalStateException(const String &message, const Throwable &cause)
        : RuntimeException(message, cause) {
    }

    IllegalStateException::IllegalStateException(const Throwable &cause): RuntimeException(cause) {
    }

    void IllegalStateException::selfThrow() const { throw *this; }
} // core
