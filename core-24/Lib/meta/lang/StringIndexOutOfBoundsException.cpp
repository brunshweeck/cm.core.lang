//
// Created by brunshweeck on 4/27/25.
//

#include "StringIndexOutOfBoundsException.h"

#include "../../core/misc/VarHandle.h"

namespace core
{
    StringIndexOutOfBoundsException::StringIndexOutOfBoundsException(const String &message)
        : IndexOutOfBoundsException(message) {
    }

    StringIndexOutOfBoundsException::StringIndexOutOfBoundsException(gint index)
        : IndexOutOfBoundsException(u"String index out of range "_Su + index) {
    }

    lang::Exception &StringIndexOutOfBoundsException::clone() const {
        return VH::newObject<StringIndexOutOfBoundsException>(*this);
    }

    void StringIndexOutOfBoundsException::selfThrow() const { throw *this; }
} // core
