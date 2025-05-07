//
// Created by brunshweeck on 01/05/25.
//

#include "ShortArray.h"

#include <meta/lang/ArrayIndexOutOfBoundsException.h>

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "OutOfMemoryError.h"

namespace core
{
    ShortArray::ShortArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    ShortArray::ShortArray(gint length, gshort initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    ShortArray::ShortArray(const ShortArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    ShortArray& ShortArray::operator=(const ShortArray& other) {
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

    ShortArray::ShortArray(ShortArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    ShortArray& ShortArray::operator=(ShortArray&& other) CORE_NOTHROW {
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

    ShortArray::~ShortArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint ShortArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean ShortArray::isEmpty() const { return length() == 0; }

    gshort& ShortArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const gshort& ShortArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    gshort ShortArray::set(gint index, gshort newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        gshort oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean ShortArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const ShortArray& array = $cast(const ShortArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Short::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint ShortArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Short::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String ShortArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Short::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    ShortArray& ShortArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        ShortArray& clone = *new ShortArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    ShortArray ShortArray::ofRange(gshort start, gshort end, gint offsetByValue) {
        if ((start < end && offsetByValue < 0) || (end < start && 0 < offsetByValue))
            IllegalArgumentException($toString(Invalid range)).throws($ftrace());
        if (offsetByValue == 0)
            IllegalArgumentException($toString(Zero offset)).throws($ftrace());
        glong rangeLength = end - start;
        glong numberOfElements = rangeLength / offsetByValue;
        if (numberOfElements < 0)
            numberOfElements = -numberOfElements;
        if (numberOfElements > (gshort)Integer::MAX_VALUE)
            OutOfMemoryError($toString(The array length required is too large)).throws($ftrace());
        gint length = (gint)numberOfElements;
        ShortArray array = ShortArray(length, start);
        for (gint i = 0; i < length; i += 1) array.values[i] += (gshort) (offsetByValue * i);
        return array;
    }

    ShortArray ShortArray::copyOf(const Array<Short>& array) {
        gint length = array.length();
        ShortArray copy = ShortArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? 0 : $cast(const Short&, item).shortValue();
        }
        return copy;
    }

    ShortArray::ReferenceStep::ReferenceStep(ShortArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    gshort& ShortArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    ShortArray::ReferenceStep& ShortArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean ShortArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint ShortArray::ReferenceStep::position() const { return index; }

    const Object& ShortArray::ReferenceStep::target() const { return array; }

    ShortArray::ConstantStep::ConstantStep(const ShortArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const gshort& ShortArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    ShortArray::ConstantStep& ShortArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean ShortArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint ShortArray::ConstantStep::position() const { return index; }

    const Object& ShortArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(gshort, gint, ShortArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        ShortArray::ConstantStep,
        ShortArray::ReferenceStep,
        ShortArray,
        (*this, false),
        (*this, true),
    )
} // core
