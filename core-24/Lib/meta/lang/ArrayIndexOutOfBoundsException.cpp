//
// Created by brunshweeck on 4/30/25.
//

#include "ArrayIndexOutOfBoundsException.h"

#include "../../core/misc/VarHandle.h"

namespace core
{
    ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(const String &message)
        : IndexOutOfBoundsException(message) {
    }

    ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(gint index)
        : IndexOutOfBoundsException(u"Array index out of range "_Su + index) {
    }

    lang::Exception &ArrayIndexOutOfBoundsException::clone() const {
        return VH::newObject<ArrayIndexOutOfBoundsException>(*this);
    }

    void ArrayIndexOutOfBoundsException::selfThrow() const { throw *this; }
} // core
