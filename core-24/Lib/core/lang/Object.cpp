//
// Created by brunshweeck on 01/04/25.
//

#include "Object.h"

#include "Null.h"

namespace core
{
    gboolean Object::equals(Object const& other) const { return this == &other; }

    gint Object::hash() const
    {
        glong identityHash = (glong)this;
        return (gint)(identityHash ^ (identityHash >> 16));
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
