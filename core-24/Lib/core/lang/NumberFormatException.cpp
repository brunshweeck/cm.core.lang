//
// Created by brunshweeck on 4/27/25.
//

#include "NumberFormatException.h"

#include "../misc/VarHandle.h"

namespace core
{
    NumberFormatException::NumberFormatException(const String &message): RuntimeException(message) {
    }

    lang::Exception &NumberFormatException::clone() const {
        return VH::newObject<NumberFormatException>(*this);
    }

    void NumberFormatException::selfThrow() const { throw *this; }
} // core
