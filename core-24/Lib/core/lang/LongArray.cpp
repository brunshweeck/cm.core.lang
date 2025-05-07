//
// Created by brunshweeck on 01/05/25.
//

#include "LongArray.h"

#include <meta/lang/ArrayIndexOutOfBoundsException.h>

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "OutOfMemoryError.h"

namespace core
{
    LongArray::LongArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    LongArray::LongArray(gint length, glong initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    LongArray::LongArray(const LongArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    LongArray& LongArray::operator=(const LongArray& other) {
        if (this != &other) {
            gint newLength = other.length();
            Values oldValues = values;
            AbstractPrimitiveArray::length = newLength;
            AbstractPrimitiveArray::values = newLength > 0 ? new Value[newLength] : null;
            for (gint i = 0; i < newLength && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
            delete [] oldValues;
        }
        return *this;
    }

    LongArray::LongArray(LongArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    LongArray& LongArray::operator=(LongArray&& other) CORE_NOTHROW {
        if (this != &other) {
            gint oldLength = length();
            gint newLength = other.length();
            Values oldValues = values;
            Values newValues = new Value[newLength];
            AbstractPrimitiveArray::length = newLength;
            AbstractPrimitiveArray::values = newValues;
            other.AbstractPrimitiveArray::length = oldLength;
            other.values = oldValues;
        }
        return *this;
    }

    LongArray::~LongArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint LongArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean LongArray::isEmpty() const { return length() == 0; }

    glong& LongArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const glong& LongArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    glong LongArray::set(gint index, glong newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        glong oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean LongArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const LongArray& array = $cast(const LongArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Long::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint LongArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Long::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String LongArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Long::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    LongArray& LongArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        LongArray& clone = *new LongArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    LongArray LongArray::ofRange(glong start, glong end, glong offsetByValue) {
        if ((start < end && offsetByValue < 0) || (end < start && 0 < offsetByValue))
            IllegalArgumentException($toString(Invalid range)).throws($ftrace());
        if (offsetByValue == 0)
            IllegalArgumentException($toString(Zero offset)).throws($ftrace());
        glong rangeLength = end - start;
        glong numberOfElements = rangeLength / offsetByValue;
        if (numberOfElements < 0)
            numberOfElements = -numberOfElements;
        if (numberOfElements > (glong)Integer::MAX_VALUE)
            OutOfMemoryError($toString(The array length required is too large)).throws($ftrace());
        gint length = (gint)numberOfElements;
        LongArray array = LongArray(length, start);
        for (gint i = 0; i < length; i += 1) array.values[i] += (offsetByValue * i);
        return array;
    }

    LongArray LongArray::copyOf(const Array<Long>& array) {
        gint length = array.length();
        LongArray copy = LongArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? 0 : $cast(const Long&, item).longValue();
        }
        return copy;
    }

    LongArray::ReferenceStep::ReferenceStep(LongArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    glong& LongArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    LongArray::ReferenceStep& LongArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean LongArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint LongArray::ReferenceStep::position() const { return index; }

    const Object& LongArray::ReferenceStep::target() const { return array; }

    LongArray::ConstantStep::ConstantStep(const LongArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const glong& LongArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    LongArray::ConstantStep& LongArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean LongArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint LongArray::ConstantStep::position() const { return index; }

    const Object& LongArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(glong, gint, LongArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        LongArray::ConstantStep,
        LongArray::ReferenceStep,
        LongArray,
        (*this, false),
        (*this, true),
    )
} // core
