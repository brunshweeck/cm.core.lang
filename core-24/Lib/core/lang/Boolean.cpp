//
// Created by brunshweeck on 4/19/25.
//

#include "Boolean.h"

#include "String.h"

namespace core
{
    Boolean::Boolean(gboolean value): value(value)
    {
    }

    gboolean Boolean::parseBoolean(const String& str) { return str.equalsIgnoreCase("true"_Sl); }

    gboolean Boolean::booleanValue() const { return value; }

    Boolean Boolean::valueOf(gboolean value) { return value; }

    Boolean Boolean::valueOf(const String& str) { return parseBoolean(str); }

    String Boolean::toString(gboolean value) { return value ? "true"_Sl : "false"_Sl; }

    String Boolean::toString() const { return toString(value); }

    gint Boolean::hash() const { return hash(value); }

    gint Boolean::hash(gboolean value) { return value ? 1231 : 1237; }

    gboolean Boolean::equals(const Object& other) const
    {
        return this == &other || Class<Boolean>::hasInstance(other) && value == $cast(Boolean const&, other).value;
    }

    gint Boolean::compareTo(const Boolean& other) const { return compare(value, other.value); }

    gint Boolean::compare(gboolean a, gboolean b) { return a && b ? 0 : a ? 1 : -1; }

    gboolean Boolean::logicalAnd(gboolean a, gboolean b) { return a && b; }

    gboolean Boolean::logicalOr(gboolean a, gboolean b) { return a || b; }

    gboolean Boolean::logicalXor(gboolean a, gboolean b) { return a != b; }
} // core
