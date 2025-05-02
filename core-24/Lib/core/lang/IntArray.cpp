//
// Created by brunshweeck on 01/05/25.
//

#include "IntArray.h"

#include <meta/lang/ArrayIndexOutOfBoundsException.h>

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "OutOfMemoryError.h"

namespace core
{
    IntArray::IntArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    IntArray::IntArray(gint length, gint initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    IntArray::IntArray(const IntArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    IntArray& IntArray::operator=(const IntArray& other) {
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

    IntArray::IntArray(IntArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    IntArray& IntArray::operator=(IntArray&& other) CORE_NOTHROW {
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

    IntArray::~IntArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint IntArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean IntArray::isEmpty() const { return length() == 0; }

    gint& IntArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const gint& IntArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    gint IntArray::set(gint index, gint newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        gint oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean IntArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const IntArray& array = $cast(const IntArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Integer::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint IntArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Integer::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String IntArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Integer::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    IntArray& IntArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        IntArray& clone = *new IntArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    IntArray IntArray::ofRange(gint start, gint end, gint offsetByValue) {
        if ((start < end && offsetByValue < 0) || (end < start && 0 < offsetByValue))
            IllegalArgumentException($toString(Invalid range)).throws($ftrace());
        if (offsetByValue == 0)
            IllegalArgumentException($toString(Zero offset)).throws($ftrace());
        glong rangeLength = end - start;
        glong numberOfElements = rangeLength / offsetByValue;
        if (numberOfElements < 0)
            numberOfElements = -numberOfElements;
        if (numberOfElements > (gint)Integer::MAX_VALUE)
            OutOfMemoryError($toString(The array length required is too large)).throws($ftrace());
        gint length = (gint)numberOfElements;
        IntArray array = IntArray(length, start);
        for (gint i = 0; i < length; i += 1) array.values[i] += (gint) (offsetByValue * i);
        return array;
    }

    IntArray IntArray::copyOf(const Array<Integer>& array) {
        gint length = array.length();
        IntArray copy = IntArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? 0 : $cast(const Integer&, item).intValue();
        }
        return copy;
    }

    IntArray::ReferenceStep::ReferenceStep(IntArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    gint& IntArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    IntArray::ReferenceStep& IntArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean IntArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint IntArray::ReferenceStep::position() const { return index; }

    const Object& IntArray::ReferenceStep::target() const { return array; }

    IntArray::ConstantStep::ConstantStep(const IntArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const gint& IntArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    IntArray::ConstantStep& IntArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean IntArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint IntArray::ConstantStep::position() const { return index; }

    const Object& IntArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(gint, gint, IntArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        IntArray::ConstantStep,
        IntArray::ReferenceStep,
        IntArray,
        (*this, false),
        (*this, true),
    )
} // core
