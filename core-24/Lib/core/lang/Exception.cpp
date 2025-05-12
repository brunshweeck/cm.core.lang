//
// Created by brunshweeck on 4/27/25.
//

#include "Exception.h"

#include "../misc/VarHandle.h"


namespace core::lang
{
    Exception::Exception(const String &message): Throwable(message) {
    }

    Exception::Exception(const String &message, const Throwable &cause): Throwable(message, cause) {
    }

    Exception::Exception(const Throwable &cause): Throwable(cause.toString(), cause) {
    }

    Exception::Exception(const Exception &other): Throwable(other) {
    }

    Exception::Exception(Exception &&other) CORE_NOTHROW: Throwable(VH::moveObject(other)) {
    }

    Exception &Exception::clone() const {
        return VH::newObject<Exception>(*this);
    }

    void Exception::selfThrow() const { throw *this; }
} // lang
// core
