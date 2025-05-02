//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ARRAY_H
#define CORE_LANG_ARRAY_H

#include "spi/AbstractObjectArray.h"
#include "Integer.h"

namespace core
{
    template <class T>
    class Array $final : public lang::spi::AbstractObjectArray
    {
    public:
        Array() = default;
        CORE_EXPLICIT Array(gint length, const T& initialValue);
        CORE_XDEPRECATED(
            "This Ctor does not initialize items of this array. "
            "But for access to item at index k require that, you ensure the existence of value at index k"
            " or T is compatible with value 'null'. in otherwise at the item accession moment the exception IllegalStateException will be thrown"
        )
        CORE_EXPLICIT Array(gint length);
        Array(const Array& other);
        Array(Array&& other) CORE_NOTHROW;
        Array& operator=(const Array& other);
        Array& operator=(Array&& other) CORE_NOTHROW;
        ~Array() override = default;
        gint length() const override;
        gboolean isEmpty() const override;
        T& get(gint index);
        const T& get(gint index) const;
        Object& getOrNull(gint index);
        const Object& getOrNull(gint index) const;
        T& getOrElse(gint index, const T& defaultValue);
        T const& getOrElse(gint index, const T& defaultValue) const;
        Object& set(gint index, const T& value);
        gboolean equals(const Object& other) const override;
        gint hash() const override;
        String toString() const override;
        AbstractObjectArray& clone() const override;
        template <class U, ClassOf(true)::OnlyIf<Class<T>::template isBaseOf<U>()>  = true>
        CORE_EXPLICIT operator Array<U>() const;
        template <class... Args>
        static Array of(const Args&... args);
        template <class Arr>
        static Array copyOf(const Arr& a);
    };
} // core

#endif // CORE_LANG_ARRAY_H
