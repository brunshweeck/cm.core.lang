//
// Created by brunshweeck on 06/04/25.
//

#include "Literals.h"

#include <core/lang/Character.h>
#include <core/lang/Double.h>
#include <core/lang/Float.h>
#include <core/lang/Long.h>
#include <core/lang/Short.h>
#include <core/lang/String.h>

namespace core { inline namespace literals
{
    String operator +(String const& a, String const& b) { return a.concat(b); }

    String operator +(String const& a, Object const& b) { return a.concat(b.toString()); }

    String operator +(String const& a, lang::spi::__literal_boolean b) {
        return a.concat(b ? $toString(true) : $toString(false));
    }

    String operator +(String const& a, lang::spi::__int8 b) { return a.concat(Byte::toString(b)); }

    String operator +(String const& a, lang::spi::__uint8 b) { return a.concat(Character::toString(b)); }

    String operator +(String const& a, lang::spi::__int16 b) { return a.concat(Short::toString(b)); }

    String operator +(String const& a, lang::spi::__uint16 b) { return a.concat(Integer::toString(b)); }

    String operator +(String const& a, lang::spi::__int32 b) { return a.concat(Integer::toString(b)); }

    String operator +(String const& a, lang::spi::__uint32 b) { return a.concat(Long::toString(b)); }

    String operator +(String const& a, lang::spi::__int64 b) { return a.concat(Long::toString(b)); }

    String operator +(String const& a, lang::spi::__uint64 b) { return a.concat(Long::toString(b)); }

    String operator +(String const& a, lang::spi::__varint b) { return a.concat(Long::toString(b)); }

    String operator +(String const& a, lang::spi::__uvarint b) { return a.concat(Long::toString(b)); }

    String operator +(String const& a, lang::spi::__float32 b) { return a.concat(Float::toString(b)); }

    String operator +(String const& a, lang::spi::__float64 b) { return a.concat(Double::toString(b)); }

    String operator +(String const& a, lang::spi::__literal_float64 b) { return a.concat(Double::toString(b)); }

    String operator +(String const& a, lang::spi::__literal_char8 b) { return a.concat(Byte::toString(b)); }

    String operator +(String const& a, lang::spi::__literal_char16 b) { return a.concat(Character::toString(b)); }

    String operator +(String const& a, lang::spi::__literal_char32 b) { return a.concat(Character::toString((gint)b)); }

    String operator +(String const& a, lang::spi::__literal_varchar b) {
        return a.concat(Character::toString((gint)b));
    }

    String& operator +=(String& a, Object const& b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__literal_boolean b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__int8 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__uint8 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__int16 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__uint16 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__int32 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__uint32 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__int64 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__uint64 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__varint b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__uvarint b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__float32 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__float64 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__literal_float64 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__literal_char8 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__literal_char16 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__literal_char32 b) { return a = a + b; }

    String& operator +=(String& a, lang::spi::__literal_varchar b) { return a = a + b; }

    gboolean operator ==(String const& a, String const& b) { return a.equals(b); }

    gboolean operator ==(String const& a, Object const& b) { return a.equals(b); }

    gboolean operator ==(Object const& a, String const& b) { return a.equals(b); }

    gboolean operator ==(String const& a, lang::Null const&) { return false; }

    gboolean operator ==(lang::Null const& a, String const& b) { return false; }

    gboolean operator !=(String const& a, String const& b) { return !(a == b); }

    gboolean operator !=(String const& a, Object const& b) { return !(a == b); }

    gboolean operator !=(Object const& a, String const& b) { return !(a == b); }

    gboolean operator !=(String const& a, lang::Null const& b) { return true; }

    gboolean operator !=(lang::Null const& a, String const& b) { return true; }
}}
