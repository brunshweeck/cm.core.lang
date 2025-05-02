//
// Created by brunshweeck on 4/20/25.
//

#include "Short.h"

#include "Class.h"
#include "NumberFormatException.h"
#include "String.h"

namespace core
{
    Short::Short(gshort value): value(value) {
    }

    gbyte Short::byteValue() const { return (gbyte)value; }

    gshort Short::shortValue() const { return value; }

    gint Short::intValue() const { return value; }

    glong Short::longValue() const { return value; }

    gfloat Short::floatValue() const { return value; }

    gdouble Short::doubleValue() const { return value; }

    String Short::toString() const { return toString(value); }

    String Short::toString(gshort value) { return Integer::toString(value); }

    Short Short::valueOf(gshort value) { return Short(value); }

    Short Short::valueOf(const String& str, gint radix) {
        try {
            return valueOf(parseShort(str, radix));
        }
        catch (const NumberFormatException& nfe) {
            nfe.throws($ftrace());
        }
    }

    gshort Short::parseShort(const String& str, gint radix) {
        gint value = 0;
        try {
            value = Integer::parseInt(str, radix);
        }
        catch (const NumberFormatException& nfe) {
            nfe.throws($ftrace());
        }
        if (value > MAX_VALUE || value < MIN_VALUE)
            NumberFormatException($toString(value out of range)).throws($ftrace());
        return (gshort)value;
    }

    gint Short::hash() const { return hash(value); }

    gint Short::hash(gshort value) { return value; }

    gboolean Short::equals(const Object& other) const {
        return this == &other || Class<Short>::hasInstance(other) && value == $cast(Short const&, other).value;
    }

    gint Short::compareTo(const Short& other) const { return compare(value, other.value); }

    gint Short::compare(gshort a, gshort b) { return a - b; }

    gint Short::compareUnsigned(gshort a, gshort b) { return (a & 0xFFFF) - (b & 0xFFFF); }

    gint Short::toUnsignedInt(gshort value) { return value & 0xFFFF; }

    glong Short::toUnsignedLong(gshort value) { return value & 0xFFFFL; }

    Short Short::decode(const String& nm) {
        Integer value = 0;
        try {
            value = Integer::decode(nm);
        } catch (const NumberFormatException& nfe) {
            nfe.throws($ftrace());
        }
        if (value > MAX_VALUE || value < MIN_VALUE)
            NumberFormatException($toString(value out of range)).throws($ftrace());
        return valueOf(value.shortValue());
    }

    gshort Short::reverseBytes(gshort value) { return (gshort)(((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8)); }
} // core
