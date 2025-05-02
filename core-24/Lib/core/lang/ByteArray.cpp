//
// Created by brunshweeck on 01/05/25.
//

#include "ByteArray.h"

#include <meta/lang/ArrayIndexOutOfBoundsException.h>

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "OutOfMemoryError.h"

namespace core
{
    ByteArray::ByteArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    ByteArray::ByteArray(gint length, gbyte initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    ByteArray::ByteArray(const ByteArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    ByteArray& ByteArray::operator=(const ByteArray& other) {
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

    ByteArray::ByteArray(ByteArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    ByteArray& ByteArray::operator=(ByteArray&& other) CORE_NOTHROW {
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

    ByteArray::~ByteArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint ByteArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean ByteArray::isEmpty() const { return length() == 0; }

    gbyte& ByteArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const gbyte& ByteArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    gbyte ByteArray::set(gint index, gbyte newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        gbyte oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean ByteArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const ByteArray& array = $cast(const ByteArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Byte::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint ByteArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Byte::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String ByteArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Byte::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    ByteArray& ByteArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        ByteArray& clone = *new ByteArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    ByteArray ByteArray::ofRange(gbyte start, gbyte end, gbyte offsetByValue) {
        if ((start < end && offsetByValue < 0) || (end < start && 0 < offsetByValue))
            IllegalArgumentException($toString(Invalid range)).throws($ftrace());
        if (offsetByValue == 0)
            IllegalArgumentException($toString(Zero offset)).throws($ftrace());
        glong rangeLength = end - start;
        glong numberOfElements = rangeLength / offsetByValue;
        if (numberOfElements < 0)
            numberOfElements = -numberOfElements;
        if (numberOfElements > (gbyte)Integer::MAX_VALUE)
            OutOfMemoryError($toString(The array length required is too large)).throws($ftrace());
        gint length = (gint)numberOfElements;
        ByteArray array = ByteArray(length, start);
        for (gint i = 0; i < length; i += 1) array.values[i] += (gbyte) (offsetByValue * i);
        return array;
    }

    ByteArray ByteArray::copyOf(const Array<Byte>& array) {
        gint length = array.length();
        ByteArray copy = ByteArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? 0 : $cast(const Byte&, item).byteValue();
        }
        return copy;
    }

    ByteArray::ReferenceStep::ReferenceStep(ByteArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    gbyte& ByteArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    ByteArray::ReferenceStep& ByteArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean ByteArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint ByteArray::ReferenceStep::position() const { return index; }

    const Object& ByteArray::ReferenceStep::target() const { return array; }

    ByteArray::ConstantStep::ConstantStep(const ByteArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const gbyte& ByteArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    ByteArray::ConstantStep& ByteArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean ByteArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint ByteArray::ConstantStep::position() const { return index; }

    const Object& ByteArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(gbyte, gint, ByteArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        ByteArray::ConstantStep,
        ByteArray::ReferenceStep,
        ByteArray,
        (*this, false),
        (*this, true),
    )
} // core
