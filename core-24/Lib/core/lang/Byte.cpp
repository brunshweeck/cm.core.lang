//
// Created by brunshweeck on 4/19/25.
//

#include "Byte.h"

#include "NumberFormatException.h"
#include "String.h"

namespace core
{
    Byte::Byte(gbyte value): value(value) {
    }

    gbyte Byte::byteValue() const { return value; }

    gshort Byte::shortValue() const { return value; }

    gint Byte::intValue() const { return value; }

    glong Byte::longValue() const { return value; }

    gfloat Byte::floatValue() const { return value; }

    gdouble Byte::doubleValue() const { return value; }

    String Byte::toString() const { return toString(value); }

    String Byte::toString(gbyte value) { return Integer::toString(value); }

    Byte Byte::valueOf(gbyte value) { return Byte(value); }

    Byte Byte::valueOf(const String& str, gint radix) {
        try {
            return valueOf(parseByte(str, radix));
        }
        catch (const NumberFormatException& nfe) {
            nfe.throws($ftrace());
        }
    }

    gbyte Byte::parseByte(const String& str, gint radix) {
        gint value = 0;
        try {
            value = Integer::parseInt(str, radix);
        }
        catch (const NumberFormatException& nfe) {
            nfe.throws($ftrace());
        }
        if (value > MAX_VALUE || value < MIN_VALUE)
            NumberFormatException($toString(value out of range)).throws($ftrace());
        return (gbyte)value;
    }

    gint Byte::hash() const { return hash(value); }

    gint Byte::hash(gbyte value) { return value; }

    gboolean Byte::equals(const Object& other) const {
        return this == &other || Class<Byte>::hasInstance(other) && value == $cast(Byte const&, other).value;
    }

    gint Byte::compareTo(const Byte& other) const { return compare(value, other.value); }

    gint Byte::compare(gbyte a, gbyte b) { return a - b; }

    gint Byte::compareUnsigned(gbyte a, gbyte b) { return (a & 0xFF) - (b & 0xFF); }

    gint Byte::toUnsignedInt(gbyte value) { return value & 0xFF; }

    glong Byte::toUnsignedLong(gbyte value) { return value & 0xFF; }

    Byte Byte::decode(const String& nm) {
        Integer value = 0;
        try {
            value = Integer::decode(nm);
        }
        catch (const NumberFormatException& nfe) {
            nfe.throws($ftrace());
        }
        if (value > MAX_VALUE || value < MIN_VALUE)
            NumberFormatException($toString(value out of range)).throws($ftrace());
        return valueOf(value.byteValue());
    }

    CORE_INTRINSIC_ACCESS_IMPL(gbyte, Byte, value);
} // core
