//
// Created by brunshweeck on 4/19/25.
//

#include "Byte.h"

#include "String.h"

namespace core
{
    Byte::Byte(gbyte value): value(value)
    {
    }

    gbyte Byte::byteValue() const { return value; }

    gshort Byte::shortValue() const { return value; }

    gint Byte::intValue() const { return value; }

    glong Byte::longValue() const { return value; }

    gfloat Byte::floatValue() const { return value; }

    gdouble Byte::doubleValue() const { return value; }

    String Byte::toString() const { return toString(value); }

    String Byte::toString(gbyte value)
    {
    }

    Byte Byte::valueOf(gbyte value) { return Byte(value); }

    Byte Byte::valueOf(const String& str, gint radix)
    {
    }

    gbyte Byte::parseByte(const String& str, gint radix)
    {
    }

    gint Byte::hash() const { return hash(value); }

    gint Byte::hash(gbyte value) { return value; }

    gboolean Byte::equals(const Object& other) const
    {
        return this == &other || Class<Byte>::hasInstance(other) && value == $cast(Byte const&, other).value;
    }

    gint Byte::compareTo(const Byte& other) const { return compare(value, other.value); }

    gint Byte::compare(gbyte a, gbyte b) { return a - b; }

    gint Byte::compareUnsigned(gbyte a, gbyte b) { return (a & 0xFF) - (b & 0xFF); }

    gint Byte::toUnsignedInt(gbyte value) { return value & 0xFF; }

    glong Byte::toUnsignedLong(gbyte value) { return value & 0xFF; }

    Byte Byte::decode(const String& nm)
    {
    }

    CORE_INTRINSIC_ACCESS_IMPL(gbyte, Byte, value);
} // core
