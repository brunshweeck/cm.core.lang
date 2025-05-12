//
// Created by brunshweeck on 4/27/25.
//

#include "ArithmeticException.h"

#include "../misc/VarHandle.h"

namespace core
{
    ArithmeticException::ArithmeticException(const String &message): RuntimeException(message) {
    }

    lang::Exception &ArithmeticException::clone() const {
        return misc::VarHandle::newObject<ArithmeticException>(*this);
    }

    void ArithmeticException::selfThrow() const { throw *this; }
} // core
