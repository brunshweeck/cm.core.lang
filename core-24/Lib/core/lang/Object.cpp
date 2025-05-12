//
// Created by brunshweeck on 01/04/25.
//

#include "Object.h"

#include "CloneNotSupportedException.h"
#include "Null.h"
#include "String.h"

namespace core
{
    gboolean Object::equals(Object const& other) const { return this == &other; }

    gint Object::hash() const
    {
        glong identityHash = (glong)this;
        return (gint)(identityHash ^ (identityHash >> 16));
    }

    String Object::toString() const
    {
        if (*this == null)
            return $toString(null);
        // todo: complete this implementation while to have the form:
        // typename@addressWithout0x
        return $toString();
    }

    Object & Object::clone() const {
        CloneNotSupportedException($toString()).throws($ftrace());
    }

    inline namespace literals
    {
        gboolean operator ==(Object const& lhs, Object const& rhs)
        {
            if (&lhs == &rhs) return true;
            if (&lhs == &null) return false;
            if (&rhs == &null) return false;
            return lhs.equals(rhs);
        }

        gboolean operator !=(Object const& lhs, Object const& rhs)
        {
            if (&lhs == &rhs) return false;
            if (&lhs == &null) return true;
            if (&rhs == &null) return true;
            return !lhs.equals(rhs);
        }
    }
} // core
