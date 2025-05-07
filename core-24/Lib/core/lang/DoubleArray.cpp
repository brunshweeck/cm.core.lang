//
// Created by brunshweeck on 01/05/25.
//

#include "DoubleArray.h"

#include <meta/lang/ArrayIndexOutOfBoundsException.h>

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "OutOfMemoryError.h"

namespace core
{
    DoubleArray::DoubleArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    DoubleArray::DoubleArray(gint length, gdouble initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    DoubleArray::DoubleArray(const DoubleArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    DoubleArray& DoubleArray::operator=(const DoubleArray& other) {
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

    DoubleArray::DoubleArray(DoubleArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    DoubleArray& DoubleArray::operator=(DoubleArray&& other) CORE_NOTHROW {
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

    DoubleArray::~DoubleArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint DoubleArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean DoubleArray::isEmpty() const { return length() == 0; }

    gdouble& DoubleArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const gdouble& DoubleArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    gdouble DoubleArray::set(gint index, gdouble newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        gdouble oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean DoubleArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const DoubleArray& array = $cast(const DoubleArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Double::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint DoubleArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Double::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String DoubleArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Double::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    DoubleArray& DoubleArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        DoubleArray& clone = *new DoubleArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    DoubleArray DoubleArray::ofRange(gdouble start, gdouble end, gdouble offsetByValue) {
        if (Double::isNaN(start) || Double::isNaN(end) || (start < end && offsetByValue < 0.0f) || (end < start && 0.0f <
            offsetByValue))
            IllegalArgumentException($toString(Invalid range)).throws($ftrace());
        if (offsetByValue == 0.0f)
            IllegalArgumentException($toString(Zero offset)).throws($ftrace());
        if (Double::isNaN(offsetByValue))
            IllegalArgumentException($toString(Invalid offset)).throws($ftrace());
        gdouble rangeLength = end - start;
        gdouble numberOfElements = rangeLength / offsetByValue;
        if (numberOfElements < 0)
            numberOfElements = -numberOfElements;
        if (!Double::isFinite(numberOfElements) || numberOfElements > (gdouble)Integer::MAX_VALUE)
            OutOfMemoryError($toString(The array length required is too large)).throws($ftrace());
        gint length = (gint)numberOfElements;
        DoubleArray array = DoubleArray(length, start);
        for (gint i = 0; i < length; i += 1) array.values[i] += offsetByValue * (gdouble)i;
        return array;
    }

    DoubleArray DoubleArray::copyOf(const Array<Double>& array) {
        gint length = array.length();
        DoubleArray copy = DoubleArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? 0.0f : $cast(const Double&, item).doubleValue();
        }
        return copy;
    }

    DoubleArray::ReferenceStep::ReferenceStep(DoubleArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    gdouble& DoubleArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    DoubleArray::ReferenceStep& DoubleArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean DoubleArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint DoubleArray::ReferenceStep::position() const { return index; }

    const Object& DoubleArray::ReferenceStep::target() const { return array; }

    DoubleArray::ConstantStep::ConstantStep(const DoubleArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const gdouble& DoubleArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    DoubleArray::ConstantStep& DoubleArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean DoubleArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint DoubleArray::ConstantStep::position() const { return index; }

    const Object& DoubleArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(gdouble, gint, DoubleArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        DoubleArray::ConstantStep,
        DoubleArray::ReferenceStep,
        DoubleArray,
        (*this, false),
        (*this, true),
    )
} // core
