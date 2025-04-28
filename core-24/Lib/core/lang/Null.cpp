//
// Created by brunshweeck on 4/15/25.
//

#include "Null.h"

namespace core
{
    namespace lang
    {
        Null& Null::getInstance()
        {
            static Null instance;
            return instance;
        }

        Null& Null::clone() const
        {
            return getInstance();
        }
    } // lang

    lang::Null& null = lang::Null::getInstance();

    inline namespace literals
    {
        gboolean operator ==(lang::Null const& lhs, lang::Null const& rhs) { return true; }
        gboolean operator !=(lang::Null const& lhs, lang::Null const& rhs) { return false; }
        gboolean operator ==(lang::Null const& lhs, void* rhs) { return !rhs; }
        gboolean operator ==(void* lhs, lang::Null const& rhs) { return !lhs; }
        gboolean operator !=(lang::Null const& lhs, void* rhs) { return !!rhs; }
        gboolean operator !=(void* lhs, lang::Null const& rhs) { return !!lhs; }
    }
} // core
