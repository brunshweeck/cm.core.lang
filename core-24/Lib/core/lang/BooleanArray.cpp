//
// Created by brunshweeck on 4/29/25.
//

#include "BooleanArray.h"

#include "Array.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "Null.h"
#include "meta/lang/ArrayIndexOutOfBoundsException.h"

namespace core
{
    BooleanArray::BooleanArray(VarArgs values) {
        glong length = (glong) values.size();
        if (length > Integer::MAX_VALUE || length < 0)
            length = Integer::MAX_VALUE;
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = (gint) length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = *(values.begin() + i);
    }

    BooleanArray::BooleanArray(gint length, gboolean initializer) {
        if (length < 0)
            IllegalArgumentException($toString(Negative array length)).throws($ftrace());
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) AbstractPrimitiveArray::values[i] = initializer;
    }

    BooleanArray::BooleanArray(const BooleanArray& other) {
        gint length = other.length();
        if (length == 0)
            return;
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length && other.values; i += 1) AbstractPrimitiveArray::values[i] = other.values[i];
    }

    BooleanArray& BooleanArray::operator=(const BooleanArray& other) {
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

    BooleanArray::BooleanArray(BooleanArray&& other) CORE_NOTHROW {
        gint length = other.length();
        AbstractPrimitiveArray::length = length;
        AbstractPrimitiveArray::values = other.values;
        other.AbstractPrimitiveArray::length = {};
        other.values = {};
    }

    BooleanArray& BooleanArray::operator=(BooleanArray&& other) CORE_NOTHROW {
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

    BooleanArray::~BooleanArray() {
        if (length() > 0) {
            Values oldValues = values;
            AbstractPrimitiveArray::length = {};
            AbstractPrimitiveArray::values = {};
            delete [] oldValues;
        }
    }

    gint BooleanArray::length() const { return AbstractPrimitiveArray::length; }

    gboolean BooleanArray::isEmpty() const { return length() == 0; }

    gboolean& BooleanArray::get(gint index) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    const gboolean& BooleanArray::get(gint index) const {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return AbstractPrimitiveArray::values[index];
    }

    gboolean BooleanArray::set(gint index, gboolean newValue) {
        if (index >= length() || index < 0)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        gboolean oldValue = AbstractPrimitiveArray::values[index];
        AbstractPrimitiveArray::values[index] = newValue;
        return oldValue;
    }

    gboolean BooleanArray::equals(const Object& other) const {
        if (this == &other)
            return true;
        const BooleanArray& array = $cast(const BooleanArray&, other);
        gint numberOfElement = length();
        if (numberOfElement != array.length())
            return false;
        for (gint i = 0; i < numberOfElement; i += 1)
            if (Boolean::compare(array.values[i], AbstractPrimitiveArray::values[i]) != 0)
                return false;
        return true;
    }

    gint BooleanArray::hash() const {
        gint result = 0;
        gint length = AbstractPrimitiveArray::length;
        for (gint i = 0; i < length; i += 1)
            result = result * 31 + Boolean::hash(AbstractPrimitiveArray::values[i]);
        return result;
    }

    String BooleanArray::toString() const {
        gint length = AbstractPrimitiveArray::length;
        if (length == 0)
            return $toString([]);
        String result = $toString([);
        for (gint i = 0; i < length; i += 1) {
            result += Boolean::toString(AbstractPrimitiveArray::values[i]);
            if (i != length - 1)
                result += ", "_Sl;
        }
        result += $toString(]);
        return result;
    }

    BooleanArray& BooleanArray::clone() const {
        gint length = this->AbstractPrimitiveArray::length;
        BooleanArray& clone = *new BooleanArray();
        clone.AbstractPrimitiveArray::length = length;
        clone.AbstractPrimitiveArray::values = length > 0 ? new Value[length] : null;
        for (gint i = 0; i < length; i += 1) clone.values[i] = AbstractPrimitiveArray::values[i];
        return clone;
    }

    BooleanArray BooleanArray::copyOf(const Array<Boolean>& array) {
        gint length = array.length();
        BooleanArray copy = BooleanArray();
        copy.AbstractPrimitiveArray::length = length;
        copy.AbstractPrimitiveArray::values = new Value[length];
        for (gint i = 0; i < length; i += 1) {
            Object const& item = array.getOrNull(i);
            copy.values[i] = item == null ? false : $cast(const Boolean&, item).booleanValue();
        }
        return copy;
    }

    BooleanArray::ReferenceStep::ReferenceStep(BooleanArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    gboolean& BooleanArray::ReferenceStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    BooleanArray::ReferenceStep& BooleanArray::ReferenceStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean BooleanArray::ReferenceStep::isDone() const { return index >= array.length(); }

    gint BooleanArray::ReferenceStep::position() const { return index; }

    const Object& BooleanArray::ReferenceStep::target() const { return array; }

    BooleanArray::ConstantStep::ConstantStep(const BooleanArray& array, gboolean gotoEnd)
        : array(array), index(gotoEnd ? Integer::MAX_VALUE : 0) {
    }

    const gboolean& BooleanArray::ConstantStep::get() {
        if (index > array.length())
            IllegalStateException($toString()).throws($ftrace());
        return array[index];
    }

    BooleanArray::ConstantStep& BooleanArray::ConstantStep::next() {
        index = (index < Integer::MAX_VALUE && index >= array.length()) ? Integer::MAX_VALUE : index + 1;
        return *this;
    }

    gboolean BooleanArray::ConstantStep::isDone() const { return index >= array.length(); }

    gint BooleanArray::ConstantStep::position() const { return index; }

    const Object& BooleanArray::ConstantStep::target() const { return array; }

    CORE_INTRINSIC_INDEXED_ITEM_ACCESS_IMPL(gboolean, gint, BooleanArray, get,)

    CORE_INTRINSIC_FOR_EACH_IMPL(
        BooleanArray::ConstantStep,
        BooleanArray::ReferenceStep,
        BooleanArray,
        (*this, false),
        (*this, true),
    )
} // core
