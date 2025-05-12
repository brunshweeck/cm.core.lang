//
// Created by brunshweeck on 4/27/25.
//

#include "OutOfMemoryError.h"

#include "../misc/VarHandle.h"

namespace core
{
    OutOfMemoryError::OutOfMemoryError(const String &message): Error(message) {
    }

    lang::Error &OutOfMemoryError::clone() const {
        return VH::newObject<OutOfMemoryError>(*this);
    }

    void OutOfMemoryError::selfThrow() const { throw *this; }
} // core
