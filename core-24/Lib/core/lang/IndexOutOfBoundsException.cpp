//
// Created by brunshweeck on 4/27/25.
//

#include "IndexOutOfBoundsException.h"

#include "../misc/VarHandle.h"

namespace core
{
    IndexOutOfBoundsException::IndexOutOfBoundsException(const String &message): IllegalArgumentException(message) {
    }

    IndexOutOfBoundsException::IndexOutOfBoundsException(glong index)
        : IllegalArgumentException(u"Index out of range "_Su + index) {
    }

    lang::Exception & IndexOutOfBoundsException::clone() const {
        return VH::newObject<IndexOutOfBoundsException>(*this);
    }

    void IndexOutOfBoundsException::selfThrow() const { throw *this; }
} // core
