//
// Created by brunshweeck on 4/30/25.
//

#include "FloatArray.h"

#include <meta/lang/ArrayIndexOutOfBoundsException.h>

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "OutOfMemoryError.h"

namespace core
{
    FloatArray::FloatArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    FloatArray::FloatArray(gint length, gfloat initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    FloatArray::FloatArray(const FloatArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    FloatArray& FloatArray::operator=(const FloatArray& other) {
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

    FloatArray::FloatArray(FloatArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    FloatArray& FloatArray::operator=(FloatArray&& other) CORE_NOTHROW {
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

    FloatArray::~FloatArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint FloatArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean FloatArray::isEmpty() const { return length() == 0; }

    gfloat& FloatArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const gfloat& FloatArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    gfloat FloatArray::set(gint index, gfloat newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        gfloat oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean FloatArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const FloatArray& array = $cast(const FloatArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Float::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint FloatArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Float::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String FloatArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Float::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    FloatArray& FloatArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        FloatArray& clone = *new FloatArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    FloatArray FloatArray::ofRange(gfloat start, gfloat end, gfloat offsetByValue) {
        if (Float::isNaN(start) || Float::isNaN(end) || (start < end && offsetByValue < 0.0f) || (end < start && 0.0f <
            offsetByValue))
            IllegalArgumentException($toString(Invalid range)).throws($ftrace());
        if (offsetByValue == 0.0f)
            IllegalArgumentException($toString(Zero offset)).throws($ftrace());
        if (Float::isNaN(offsetByValue))
            IllegalArgumentException($toString(Invalid offset)).throws($ftrace());
        gfloat rangeLength = end - start;
        gfloat numberOfElements = rangeLength / offsetByValue;
        if (numberOfElements < 0)
            numberOfElements = -numberOfElements;
        if (!Float::isFinite(numberOfElements) || numberOfElements > (gfloat)Integer::MAX_VALUE)
            OutOfMemoryError($toString(The array length required is too large)).throws($ftrace());
        gint length = (gint)numberOfElements;
        FloatArray array = FloatArray(length, start);
        for (gint i = 0; i < length; i += 1) array.values[i] += offsetByValue * (gfloat)i;
        return array;
    }

    FloatArray FloatArray::copyOf(const Array<Float>& array) {
        gint length = array.length();
        FloatArray copy = FloatArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? 0.0f : $cast(const Float&, item).floatValue();
        }
        return copy;
    }

    FloatArray::ReferenceStep::ReferenceStep(FloatArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    gfloat& FloatArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    FloatArray::ReferenceStep& FloatArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean FloatArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint FloatArray::ReferenceStep::position() const { return index; }

    const Object& FloatArray::ReferenceStep::target() const { return array; }

    FloatArray::ConstantStep::ConstantStep(const FloatArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const gfloat& FloatArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    FloatArray::ConstantStep& FloatArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean FloatArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint FloatArray::ConstantStep::position() const { return index; }

    const Object& FloatArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(gfloat, gint, FloatArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        FloatArray::ConstantStep,
        FloatArray::ReferenceStep,
        FloatArray,
        (*this, false),
        (*this, true),
    )
} // core
