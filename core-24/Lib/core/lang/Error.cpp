//
// Created by brunshweeck on 4/27/25.
//

#include "Error.h"

#include "../misc/VarHandle.h"


namespace core::lang
{
    Error::Error(const String &message): Throwable(message) {
    }

    Error::Error(const String &message, const Throwable &cause): Throwable(message, cause) {
    }

    Error::Error(const Throwable &cause): Throwable(cause.toString(), cause) {
    }

    Error::Error(const Error &other): Throwable(other) {
    }

    Error::Error(Error &&other) CORE_NOTHROW : Throwable(misc::VarHandle::moveObject(other)) {
    }

    Error &Error::clone() const {
        return misc::VarHandle::newObject<Error>(*this);
    }

    void Error::selfThrow() const { throw *this; }
} // lang
// core
