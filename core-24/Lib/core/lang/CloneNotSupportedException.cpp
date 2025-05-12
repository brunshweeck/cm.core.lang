//
// Created by brunshweeck on 4/27/25.
//

#include "CloneNotSupportedException.h"

#include "../misc/VarHandle.h"

namespace core
{
    CloneNotSupportedException::CloneNotSupportedException(const String &message): RuntimeException(message) {
    }

    lang::Exception & CloneNotSupportedException::clone() const {
        return misc::VarHandle::newObject<CloneNotSupportedException>(*this);
    }

    void CloneNotSupportedException::selfThrow() const { throw *this; }
} // core
