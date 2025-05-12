//
// Created by brunshweeck on 4/27/25.
//

#include "AbstractObjectArray.h"

#include <core/lang/Memory.h>
#include <core/misc/VarHandle.h>

#include "../../../meta/lang/ArrayIndexOutOfBoundsException.h"
#include "../../../meta/lang/Strings.h"

namespace core::lang::spi
{
    static CORE_FAST glong ELEMENT_SIZE = Class<Object>::SIZE;

    AbstractObjectArray::AbstractObjectArray(gint length, Object &initialRef) {
        count = 0;
        values = null;
        if (length > 0) {
            count = length;
            values = (Values) VH::allocateMemory(ELEMENT_SIZE * length);
            if (initialRef == null)
                for (glong i = 0; i < count; i++) values[i] = null;
            else
                for (glong i = 0; i < count; i++) values[i] = &initialRef;
        }
    }

    Object &AbstractObjectArray::getObject(gint index) {
        Element element = values[index];
        if (element == null)
            return null;
        return *element;
    }

    const Object &AbstractObjectArray::getObject(gint index) const {
        if (index < 0 || index >= count)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        Element element = values[index];
        if (element == null)
            return null;
        return *element;
    }

    gboolean AbstractObjectArray::checkObject(gint index) const {
        if (index < 0 || index >= count)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        return values[index] != null;
    }

    Object &AbstractObjectArray::setObject(gint index, Object &newObject) {
        if (index < 0 || index >= count)
            ArrayIndexOutOfBoundsException(index).throws($ftrace());
        Element element = values[index];
        if (element == null)
            values[index] = null;
        else
            values[index] = &newObject;
        return *element;
    }

    void AbstractObjectArray::setAll(const AbstractObjectArray &newArray) {
        if (this == &newArray) return;
        gint length = newArray.length();
        if (count != length) {
            values = (Values) VH::reallocateMemory((glong) values, ELEMENT_SIZE * length);
            count = length;
        }
        for (gint i = 0; i < length; i++) values[i] = newArray.values[i];
    }

    void AbstractObjectArray::swapContents(AbstractObjectArray &newArray) {
        if (this == &newArray) return;
        Strings::swap(values, newArray.values);
        Strings::swap(count, newArray.count);
    }

    AbstractObjectArray::~AbstractObjectArray() {
        glong address = (glong) values;
        values = null;
        if (count != 0) {
            count = 0;
            VH::deallocateMemory(address);
        }
    }

    gint AbstractObjectArray::length() const {
        return count;
    }

    gboolean AbstractObjectArray::isEmpty() const {
        return count == 0;
    }

    gboolean AbstractObjectArray::equals(const Object &other) const {
        if (this == &other) return true;
        if (!Class<AbstractObjectArray>::hasInstance(other)) return false;
        const AbstractObjectArray &otherArray = $cast(const AbstractObjectArray &, other);
        if (count != otherArray.count) return false;
        for (glong i = 0; i < count; i++)
            if (values[i] != otherArray.values[i]) {
                if (values[i] == null) return false;
                if (otherArray.values[i] == null) return false;
                if ((*values[i]) != (*otherArray.values[i])) return false;
            }
        return true;
    }

    gint AbstractObjectArray::hash() const {
        gint hash = 0;
        for (glong i = 0; i < count; i++) {
            if (values[i] != null)
                hash = hash * 31 + values[i]->hash();
            else
                hash = hash * 31;
        }
        return hash;
    }

    String AbstractObjectArray::toString() const {
        String result = u"["_Su;
        for (glong i = 0; i < count; i++) {
            if (values[i] != null)
                result += values[i]->toString();
            else
                result += $toString(null);
            if (i != count - 1)
                result += u", "_Su;
        }
        result += u"]"_Su;
        return result;
    }

    AbstractObjectArray &AbstractObjectArray::clone() const {
        CloneNotSupportedException(toString()).throws($ftrace());
    }
}
