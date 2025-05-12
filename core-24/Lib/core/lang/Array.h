//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ARRAY_H
#define CORE_LANG_ARRAY_H

#include "spi/AbstractObjectArray.h"
#include "Integer.h"
#include "Null.h"
#include <core/misc/VarHandle.h>

#include "AssertionError.h"
#include "ClassCastException.h"
#include "OutOfMemoryError.h"

namespace core
{
    /// The class @c Array wraps the array of object reference.
    /// An object of type @c Array contains two fields whose first represent the C array of object pointers, and the second represents the number of pointers able to store in the first fields.
    /// @note this implementation supports an unset pointer because all references are set to @c null object reference on array creation and throw @c NoSuchElementException if we're trying to access.
    /// @tparam T the type of this array element
    template<class T>
    class Array $final : public lang::spi::AbstractObjectArray
    {
    public:
        Array() = default;

        CORE_EXPLICIT Array(gint length, const T &initialValue)
            : AbstractObjectArray(length, VH::copyObject(initialValue)) {
        }

        CORE_XDEPRECATED(
            "This Ctor does not initialize items of this array. "
            "But for access to item at index k require that, you ensure the existence of value at index k"
            " or T is compatible with value 'null'. in otherwise at the item accession moment the exception IllegalStateException will be thrown"
        )
        CORE_EXPLICIT Array(gint length): AbstractObjectArray(length) {
        }

        Array(const Array &other) {
            setAll(other);
        }

        Array(Array &&other) CORE_NOTHROW {
            swapContents(other);
        }

        Array &operator=(const Array &other) {
            if (this != &other)
                setAll(other);
            return *this;
        }

        Array &operator=(Array &&other) CORE_NOTHROW {
            if (this != &other)
                swapContents(other);
            return *this;
        }

        ~Array() override = default;

        T &get(gint index) {
            Object &object = getObject(index);
            if (object == null && !Class<T>::hasInstance(null))
                ClassCastException($toString()).throws($ftrace());
            return $cast(T&, object);
        }

        const T &get(gint index) const {
            const Object &object = getObject(index);
            if (object == null && !Class<T>::hasInstance(null))
                ClassCastException($toString()).throws($ftrace());
            return $cast(const T&, object);
        }

        Object &getOrNull(gint index) {
            return getObject(index);
        }

        const Object &getOrNull(gint index) const {
            return getObject(index);
        }

        T &getOrElse(gint index, const T &defaultValue) {
            Object &object = getObject(index);
            if (object == null && !Class<T>::hasInstance(null))
                return VH::copyObject(defaultValue);
            return $cast(T&, object);
        }

        T const &getOrElse(gint index, const T &defaultValue) const {
            const Object &object = getObject(index);
            if (object == null && !Class<T>::hasInstance(null))
                return VH::copyObject(defaultValue);
            return $cast(const T&, object);
        }

        Object &set(gint index, const T &value) {
            return setObject(index, VH::copyObject(value));
        }

        AbstractObjectArray &clone() const override {
            return VH::newObject<Array>(*this);
        }

        CORE_WARNING_PUSH
        CORE_WARNING_DISABLE_DEPRECATED

        template<class U, ClassOf(true)::OnlyIf<Class<T>::template isBaseOf<U>()>  = true>
        CORE_EXPLICIT operator Array<U>() const {
            gint count = length();
            Array<U> array = Array<U>(count);
            for (gint i = 0; i < count; i++) {
                if (!checkObject(i)) continue;
                Object &object = (Object &) getObject(i);
                if (!Class<U>::hasInstance(object))
                    ClassCastException($toString(Source array contains incompatible elements)).throws($ftrace());
                array.setObject(i, object);
            }
            return array;
        }

        template<class... Args>
        static Array of(const Args &... args) {
            glong length = sizeof...(args);
            if (length > Integer::MAX_VALUE - 8)
                OutOfMemoryError($toString(Number of argument exceed implementation limit)).throws($ftrace());
            Array array = Array(length);
            gint index = 0;
            gboolean tmp[] = {(index = ElementFactory<Args>::create(array, index))...};
            if (length > 0 && tmp[length] != index)
                AssertionError(false).throws($ftrace());
            return array;
        }

        template<class Arr>
        static Array copyOf(const Arr &a) {
            glong length = Class<Arr>::COUNT;
            if (length > Integer::MAX_VALUE - 8)
                OutOfMemoryError($toString(Number of argument exceed implementation limit)).throws($ftrace());
            Array array = Array(length);
            gint index = 0;
            while (index < length) array.set(index++, a[index]);
            return array;
        }

        CORE_WARNING_POP

    private:
        template<class E,
            gboolean = Class<T>::template isCompatible<T>(),
            gboolean = Class<E>::isNumber() || Class<E>::isCharacter() || Class<E>::isBoolean(),
            gboolean = Class<E>::isString(),
            gboolean = Class<E>::isArray()
        >
        class ElementFactory
        {
        public:
            template<class Arg>
            static gint create(Array &target, gint index, Arg &&arg) {
                ClassCastException($toString(Incompatible array elements)).throws($ftrace());
            }
        };

        // Boolean, Character, Byte, Short, Integer, Long, Float, Double, etc.
        template<class E>
        class ElementFactory<E, true, true>
        {
        public:
            static gint create(Array &target, gint index, E arg) {
                using Element = typename Class<E>::ClassType;
                Element element = Element::valueOf(arg);
                target.set(index++, element);
                return index;
            }
        };

        // String
        template<class E>
        class ElementFactory<E, true, false, true>
        {
        public:
            template<class Arg>
            static gint create(Array &target, gint index, Arg &&arg) {
                String string = String(VH::forwardObject<Arg>(arg));
                target.set(index++, string);
                return index;
            }
        };

        // Array
        template<class E>
        class ElementFactory<E, true, false, false, true>
        {
        public:
            template<class Arg>
            static gint create(Array &target, gint index, Arg &&arg) {
                using Elmt = typename Class<E>::NoArray;
                using Element = typename Class<Elmt>::ClassType;
                Array<Element> array = Array<Element>::copyOf(VH::forwardObject<Arg>(arg));
                if (!Class<T>::hasInstance(array))
                    ClassCastException($toString()).throws($ftrace());
                target.set(index++, array);
                return index;
            }
        };
    };
} // core

#endif // CORE_LANG_ARRAY_H
