//
// Created by brunshweeck on 10/05/25.
//

#ifndef CORE_LANG_FIELDS_H
#define CORE_LANG_FIELDS_H

#include <core/lang/Class.h>
#include <core/lang/CloneNotSupportedException.h>
#include <core/lang/Null.h>
#include <core/lang/UnsupportedOperationException.h>

#include <core/lang/spi/AbstractObjectArray.h>
#include <core/lang/ByteArray.h>

#include "../lang/Boolean.h"
#include "../lang/Character.h"
#include "../lang/Double.h"
#include "../lang/Float.h"
#include "../lang/Long.h"
#include "../lang/Short.h"

namespace core::misc
{
    class VarHandle : public Object
    {
        template<class T>
        $alias(NoRef, typename Class<T>::NoReference);
        template<class T>
        $alias(Slimmed, typename Class<T>::Slimmed);
        template<class T>
        $alias(Ref, typename Class<Slimmed<T>>::Reference);

        /// The type object required to use @c newObject method
        /// @tparam T
        /// @tparam Args
        template<class T, class... Args>
        $alias(SafeRef, typename Class<Ref<T>>::template OnlyIfAll<
               Class<T>::isSlimmed(),
               Class<Slimmed<T>>::isSizeable(),
               !Class<Slimmed<T>>::isAbstract(),
               Class<Object>::isBaseOf<Slimmed<T>>(),
               Class<Slimmed<T>>::template isConstructible<Args...>()>
        );

        /// The type of object required to use perfect forwarding
        /// @tparam T
        template<class T>
        $alias(NoLvalue, typename Class<T>::template OnlyIf<Class<T>::isRvalue()>);

        static CORE_FAST gboolean BE = CORE_BYTE_ORDER == CORE_BIG_ENDIAN;

        VarHandle() = default;

    public:
        ~VarHandle() override = default;

        // Plain Accessors

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gboolean getBoolean(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gbyte getByte(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gshort getShort(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gchar getChar(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gint getInt(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static glong getLong(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gfloat getFloat(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared non-@c volatile.
        /// Commonly referred to as plain read access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gdouble getDouble(const Object &object, glong offset);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gboolean newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gbyte newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gshort newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gchar newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gint newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, glong newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gfloat newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared non-@c volatile and non-@c final.
        /// Commonly referred to as plain write access.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void set(const Object &object, glong offset, gdouble newValue);

        // Volatile accessors

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gboolean getBooleanVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gbyte getByteVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gshort getShortVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gchar getCharVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gint getIntVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static glong getLongVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gfloat getFloatVolatile(const Object &object, glong offset);

        /// Returns the value of a variable, with memory semantics of reading as if the variable was declared @c volatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gdouble getDoubleVolatile(const Object &object, glong offset);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gboolean newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gbyte newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gshort newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gchar newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gint newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, glong newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gfloat newValue);

        /// Sets the value of a variable to the @c newValue, with memory semantics of setting as if the variable was declared @c volatile.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_seq_cst.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setVolatile(const Object &object, glong offset, gdouble newValue);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gboolean getBooleanOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gbyte getByteOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gshort getShortOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gchar getCharOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gint getIntOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static glong getLongOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gfloat getFloatOpaque(const Object &object, glong offset);

        /// Returns the value of a variable, accessed in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gdouble getDoubleOpaque(const Object &object, glong offset);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gboolean newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gbyte newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gshort newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gchar newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gint newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, glong newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gfloat newValue);

        /// Sets the value of a variable to the @c newValue, in program order, but with no assurance of memory ordering effects with respect to other threads.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setOpaque(const Object &object, glong offset, gdouble newValue);

        // Lazy accessors

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gboolean getBooleanAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gbyte getByteAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gshort getShortAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gchar getCharAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gint getIntAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static glong getLongAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gfloat getFloatAcquire(const Object &object, glong offset);

        /// Returns the value of a variable, and ensures that subsequent loads and stores are not reordered before this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_acquire ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @return the signature-polymorphic result that is the value of the variable.
        static gdouble getDoubleAcquire(const Object &object, glong offset);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gboolean newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gbyte newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gshort newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gchar newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gint newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, glong newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gfloat newValue);

        /// Sets the value of a variable to the @c newValue, and ensures that prior loads and stores are not reordered after this access.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c memory_order_release ordering.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        static void setRelease(const Object &object, glong offset, gdouble newValue);

        // Compare and set accessors

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gboolean expectedValue, gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gbyte expectedValue, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gshort expectedValue, gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gchar expectedValue, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, glong expectedValue, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gfloat expectedValue, gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndSet(const Object &object, glong offset, gdouble expectedValue, gdouble newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean compareAndExchange(const Object &object, glong offset, gboolean expectedValue,
                                           gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gbyte compareAndExchange(const Object &object, glong offset, gbyte expectedValue, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gshort compareAndExchange(const Object &object, glong offset, gshort expectedValue, gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gchar compareAndExchange(const Object &object, glong offset, gchar expectedValue, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gint compareAndExchange(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static glong compareAndExchange(const Object &object, glong offset, glong expectedValue, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gfloat compareAndExchange(const Object &object, glong offset, gfloat expectedValue, gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gdouble compareAndExchange(const Object &object, glong offset, gdouble expectedValue, gdouble newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean compareAndExchangeAcquire(const Object &object, glong offset, gboolean expectedValue,
                                                  gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gbyte compareAndExchangeAcquire(const Object &object, glong offset, gbyte expectedValue, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gshort compareAndExchangeAcquire(const Object &object, glong offset, gshort expectedValue,
                                                gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gchar compareAndExchangeAcquire(const Object &object, glong offset, gchar expectedValue, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gint compareAndExchangeAcquire(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static glong compareAndExchangeAcquire(const Object &object, glong offset, glong expectedValue, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gfloat compareAndExchangeAcquire(const Object &object, glong offset, gfloat expectedValue,
                                                gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gdouble compareAndExchangeAcquire(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean compareAndExchangeRelease(const Object &object, glong offset, gboolean expectedValue,
                                                  gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gbyte compareAndExchangeRelease(const Object &object, glong offset, gbyte expectedValue, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gshort compareAndExchangeRelease(const Object &object, glong offset, gshort expectedValue,
                                                gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gchar compareAndExchangeRelease(const Object &object, glong offset, gchar expectedValue, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gint compareAndExchangeRelease(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static glong compareAndExchangeRelease(const Object &object, glong offset, glong expectedValue, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gfloat compareAndExchangeRelease(const Object &object, glong offset, gfloat expectedValue,
                                                gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the witness value, which will be the same as the @c expectedValue if successful
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gdouble compareAndExchangeRelease(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue);

        // Weak (spurious failures allowed)

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gboolean expectedValue,
                                               gboolean newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gbyte expectedValue, gbyte newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gshort expectedValue,
                                               gshort newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gchar expectedValue, gchar newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, glong expectedValue, glong newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gfloat expectedValue,
                                               gfloat newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetPlain(const Object &object, glong offset, gdouble expectedValue,
                                               gdouble newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gboolean expectedValue,
                                          gboolean newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gbyte expectedValue, gbyte newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gshort expectedValue, gshort newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gchar expectedValue, gchar newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, glong expectedValue, glong newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gfloat expectedValue, gfloat newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setVolatile if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getVolatile.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean weakCompareAndSet(const Object &object, glong offset, gdouble expectedValue, gdouble newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gboolean expectedValue,
                                                 gboolean newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gbyte expectedValue,
                                                 gbyte newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gshort expectedValue,
                                                 gshort newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gchar expectedValue,
                                                 gchar newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, glong expectedValue,
                                                 glong newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gfloat expectedValue,
                                                 gfloat newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b set if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b getAcquire.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean weakCompareAndSetAcquire(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gboolean expectedValue,
                                                 gboolean newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gbyte expectedValue,
                                                 gbyte newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gshort expectedValue,
                                                 gshort newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gchar expectedValue,
                                                 gchar newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gint expectedValue, gint newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, glong expectedValue,
                                                 glong newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gfloat expectedValue,
                                                 gfloat newValue);

        /// Possibly atomically sets the value of a variable to the @c newValue with the semantics of @b setRelease if the variable's current value, referred to as the <em>witness value</em>, @c == the @c expectedValue, as accessed with the memory semantics of @b get.
        /// This operation may fail spuriously (typically, due to memory contention) even if the witness value does match the expected value.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param expectedValue the suspected value
        /// @param newValue the value to store into the indicated C variable
        /// @return @c true if successful, otherwise @c false if the witness value was not the same as the @c expectedValue or if this operation spuriously failed.
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean weakCompareAndSetRelease(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean getAndSet(const Object &object, glong offset, gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gbyte getAndSet(const Object &object, glong offset, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gshort getAndSet(const Object &object, glong offset, gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gchar getAndSet(const Object &object, glong offset, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gint getAndSet(const Object &object, glong offset, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static glong getAndSet(const Object &object, glong offset, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gfloat getAndSet(const Object &object, glong offset, gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gdouble getAndSet(const Object &object, glong offset, gdouble newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean getAndSetAcquire(const Object &object, glong offset, gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gbyte getAndSetAcquire(const Object &object, glong offset, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gshort getAndSetAcquire(const Object &object, glong offset, gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gchar getAndSetAcquire(const Object &object, glong offset, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gint getAndSetAcquire(const Object &object, glong offset, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static glong getAndSetAcquire(const Object &object, glong offset, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gfloat getAndSetAcquire(const Object &object, glong offset, gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gdouble getAndSetAcquire(const Object &object, glong offset, gdouble newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean getAndSetRelease(const Object &object, glong offset, gboolean newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gbyte getAndSetRelease(const Object &object, glong offset, gbyte newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gshort getAndSetRelease(const Object &object, glong offset, gshort newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gchar getAndSetRelease(const Object &object, glong offset, gchar newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gint getAndSetRelease(const Object &object, glong offset, gint newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static glong getAndSetRelease(const Object &object, glong offset, glong newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gfloat getAndSetRelease(const Object &object, glong offset, gfloat newValue);

        /// Atomically sets the value of a variable to the @c newValue with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gdouble getAndSetRelease(const Object &object, glong offset, gdouble newValue);

        // Primitive adders

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gbyte getAndAdd(const Object &object, glong offset, gbyte value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gshort getAndAdd(const Object &object, glong offset, gshort value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gchar getAndAdd(const Object &object, glong offset, gchar value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gint getAndAdd(const Object &object, glong offset, gint value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static glong getAndAdd(const Object &object, glong offset, glong value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gfloat getAndAdd(const Object &object, glong offset, gfloat value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setVolatile, and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gdouble getAndAdd(const Object &object, glong offset, gdouble value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gbyte getAndAddAcquire(const Object &object, glong offset, gbyte value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gshort getAndAddAcquire(const Object &object, glong offset, gshort value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gchar getAndAddAcquire(const Object &object, glong offset, gchar value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gint getAndAddAcquire(const Object &object, glong offset, gint value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static glong getAndAddAcquire(const Object &object, glong offset, glong value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gfloat getAndAddAcquire(const Object &object, glong offset, gfloat value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b set, and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gdouble getAndAddAcquire(const Object &object, glong offset, gdouble value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gbyte getAndAddRelease(const Object &object, glong offset, gbyte value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gshort getAndAddRelease(const Object &object, glong offset, gshort value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gchar getAndAddRelease(const Object &object, glong offset, gchar value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gint getAndAddRelease(const Object &object, glong offset, gint value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static glong getAndAddRelease(const Object &object, glong offset, glong value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gfloat getAndAddRelease(const Object &object, glong offset, gfloat value);

        /// Atomically adds the @c value to the current value of a variable with the memory semantics of @b setRelease, and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param value the value to add
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gdouble getAndAddRelease(const Object &object, glong offset, gdouble value);

        // Bitwise operations

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean getAndBitwiseOr(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gbyte getAndBitwiseOr(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gshort getAndBitwiseOr(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gchar getAndBitwiseOr(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gint getAndBitwiseOr(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static glong getAndBitwiseOr(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean getAndBitwiseOrAcquire(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gbyte getAndBitwiseOrAcquire(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gshort getAndBitwiseOrAcquire(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gchar getAndBitwiseOrAcquire(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gint getAndBitwiseOrAcquire(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static glong getAndBitwiseOrAcquire(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean getAndBitwiseOrRelease(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gbyte getAndBitwiseOrRelease(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gshort getAndBitwiseOrRelease(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gchar getAndBitwiseOrRelease(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gint getAndBitwiseOrRelease(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise OR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical OR is performed instead of a bitwise OR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static glong getAndBitwiseOrRelease(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean getAndBitwiseAnd(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gbyte getAndBitwiseAnd(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gshort getAndBitwiseAnd(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gchar getAndBitwiseAnd(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gint getAndBitwiseAnd(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static glong getAndBitwiseAnd(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean getAndBitwiseAndAcquire(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gbyte getAndBitwiseAndAcquire(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gshort getAndBitwiseAndAcquire(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gchar getAndBitwiseAndAcquire(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gint getAndBitwiseAndAcquire(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static glong getAndBitwiseAndAcquire(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean getAndBitwiseAndRelease(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gbyte getAndBitwiseAndRelease(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gshort getAndBitwiseAndRelease(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gchar getAndBitwiseAndRelease(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gint getAndBitwiseAndRelease(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise AND between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical AND is performed instead of a bitwise AND.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static glong getAndBitwiseAndRelease(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gboolean getAndBitwiseXor(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gbyte getAndBitwiseXor(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gshort getAndBitwiseXor(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gchar getAndBitwiseXor(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static gint getAndBitwiseXor(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setVolatile and returns the variable's previous value, as accessed with the memory semantics of @b getVolatile.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setVolatile(Object...)
        /// @see #getVolatile(Object...)
        static glong getAndBitwiseXor(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gboolean getAndBitwiseXorAcquire(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gbyte getAndBitwiseXorAcquire(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gshort getAndBitwiseXorAcquire(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gchar getAndBitwiseXorAcquire(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static gint getAndBitwiseXorAcquire(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b set and returns the variable's previous value, as accessed with the memory semantics of @b getAcquire.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #set(Object...)
        /// @see #getAcquire(Object...)
        static glong getAndBitwiseXorAcquire(const Object &object, glong offset, glong mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gboolean getAndBitwiseXorRelease(const Object &object, glong offset, gboolean mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gbyte getAndBitwiseXorRelease(const Object &object, glong offset, gbyte mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gshort getAndBitwiseXorRelease(const Object &object, glong offset, gshort mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gchar getAndBitwiseXorRelease(const Object &object, glong offset, gchar mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static gint getAndBitwiseXorRelease(const Object &object, glong offset, gint mask);

        /// Atomically sets the value of a variable to the result of bitwise XOR between the variable's current value and the @c mask with the memory semantics of @b setRelease and returns the variable's previous value, as accessed with the memory semantics of @b get.
        /// If the variable type is the non-integral @c boolean type then a logical XOR is performed instead of a bitwise XOR.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param mask
        /// @return the signature-polymorphic result that is the previous value of the variable
        /// @see #setRelease(Object...)
        /// @see #get(Object...)
        static glong getAndBitwiseXorRelease(const Object &object, glong offset, glong mask);

        // Fence methods

        /// Ensures that loads and stores before the fence will not be reordered with loads and stores after the fence.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c  atomic_thread_fence(memory_order_seq_cst)
        static void fullFence();

        /// Ensures that loads before the fence will not be reordered with loads and stores after the fence.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c  atomic_thread_fence(memory_order_acquire)
        static void acquireFence();

        /// Ensures that loads and stores before the fence will not be reordered with stores after the fence.
        /// @note Ignoring the many semantic differences from C and C++, this method has memory ordering effects compatible with @c  atomic_thread_fence(memory_order_release)
        static void releaseFence();

        /// Ensures that loads before the fence will not be reordered with loads after the fence.
        static void loadLoadFence();

        /// Ensures that stores before the fence will not be reordered with stores after the fence.
        static void storeStoreFence();

        /// Returns true if the native byte ordering of this platform is big-endian, false if it is little-endian.
        static gboolean isBigEndian();

        /// Returns true if this platform is capable of performing accesses at addresses which are not aligned for the type of the primitive type being accessed, false otherwise.
        static gboolean unalignedAccess();

        /// Reports the size in bytes of a native pointer.
        /// This value will be either 4 or 8.
        /// Note that the sizes of other primitive types (as stored in native memory blocks) are determined fully by their information content.
        static gint addressSize();

        /// Reports the size in bytes of a native memory page (whatever that is).
        /// This value will always be a power of two.
        static gint pageSize();

        /// Fetches a value at some byte offset into a given object.
        /// More specifically, fetches a value within the given <code>object</code> at the given offset, or (if <code>o</code> is null) from the memory address whose numerical value is the given offset.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// Unless an <code>object</code> is null, the value accessed must be entirely within the allocated object.
        /// The read will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, getShortUnaligned will make atomic reads of 2-byte storage units if the offset is zero mod 2.
        /// There are no other guarantees of atomicity.
        /// 2-byte atomicity is only guaranteed on platforms on which support atomic access to shorts.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param bigEndian The endianness of the value
        /// @return the value fetched from the indicated object
        static gshort getShortUnaligned(const Object &object, glong offset, gboolean bigEndian = BE);

        /// Fetches a value at some byte offset into a given object.
        /// More specifically, fetches a value within the given <code>object</code> at the given offset, or (if <code>o</code> is null) from the memory address whose numerical value is the given offset.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// Unless an <code>object</code> is null, the value accessed must be entirely within the allocated object.
        /// The read will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, getCharUnaligned will make atomic reads of 2-byte storage units if the offset is zero mod 2.
        /// There are no other guarantees of atomicity.
        /// 2-byte atomicity is only guaranteed on platforms on which support atomic access to chars.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param bigEndian The endianness of the value
        /// @return the value fetched from the indicated object
        static gchar getCharUnaligned(const Object &object, glong offset, gboolean bigEndian = BE);

        /// Fetches a value at some byte offset into a given object.
        /// More specifically, fetches a value within the given <code>object</code> at the given offset, or (if <code>o</code> is null) from the memory address whose numerical value is the given offset.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// Unless an <code>object</code> is null, the value accessed must be entirely within the allocated object.
        /// The read will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, getIntUnaligned will make atomic reads of 2-, 4-byte storage units if the offset is zero mod 2, or 4, respectively.
        /// There are no other guarantees of atomicity.
        /// 4-byte atomicity is only guaranteed on platforms on which support atomic access to ints.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param bigEndian The endianness of the value
        /// @return the value fetched from the indicated object
        static gint getIntUnaligned(const Object &object, glong offset, gboolean bigEndian = BE);

        /// Fetches a value at some byte offset into a given object.
        /// More specifically, fetches a value within the given <code>object</code> at the given offset, or (if <code>o</code> is null) from the memory address whose numerical value is the given offset.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// Unless an <code>object</code> is null, the value accessed must be entirely within the allocated object.
        /// The read will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, getLongUnaligned will make atomic reads of 2-, 4-, or 8-byte storage units if the offset is zero mod 2, 4, or 8, respectively.
        /// There are no other guarantees of atomicity.
        /// 8-byte atomicity is only guaranteed on platforms on which support atomic access to longs.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param bigEndian The endianness of the value
        /// @return the value fetched from the indicated object
        static glong getLongUnaligned(const Object &object, glong offset, gboolean bigEndian = BE);

        /// Stores a value at some byte offset into a given object.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// The endianness of the value in memory is the endianness of the native platform.
        /// The writing will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, setUnaligned will make atomic writes of 2-, 4-, or 8-byte storage units if the offset is zero mod 2, 4, or 8, respectively.
        /// There are no other guarantees of atomicity.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @param bigEndian The endianness of the value
        static void setUnaligned(const Object &object, glong offset, gshort newValue, gboolean bigEndian = BE);

        /// Stores a value at some byte offset into a given object.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// The endianness of the value in memory is the endianness of the native platform.
        /// The writing will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, setUnaligned will make atomic writes of 2-, 4-, or 8-byte storage units if the offset is zero mod 2, 4, or 8, respectively.
        /// There are no other guarantees of atomicity.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @param bigEndian The endianness of the value
        static void setUnaligned(const Object &object, glong offset, gchar newValue, gboolean bigEndian = BE);

        /// Stores a value at some byte offset into a given object.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// The endianness of the value in memory is the endianness of the native platform.
        /// The writing will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, setUnaligned will make atomic writes of 2-, 4-, or 8-byte storage units if the offset is zero mod 2, 4, or 8, respectively.
        /// There are no other guarantees of atomicity.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @param bigEndian The endianness of the value
        static void setUnaligned(const Object &object, glong offset, gint newValue, gboolean bigEndian = BE);

        /// Stores a value at some byte offset into a given object.
        /// The value in memory is raw data, and need not correspond to any variable.
        /// The endianness of the value in memory is the endianness of the native platform.
        /// The writing will be atomic with respect to the largest power of two that divides the GCD of the offset and the storage size.
        /// For example, setUnaligned will make atomic writes of 2-, 4-, or 8-byte storage units if the offset is zero mod 2, 4, or 8, respectively.
        /// There are no other guarantees of atomicity.
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param newValue the value to store into the indicated C variable
        /// @param bigEndian The endianness of the value
        static void setUnaligned(const Object &object, glong offset, glong newValue, gboolean bigEndian = BE);

        // Objects Manipulations

        /// Create a new allocated instance of a type @c T
        /// @tparam T the type of object to be created
        /// @tparam Args the signature-polymorphic parameter type list required to build a desired object.
        /// @param args the signature-polymorphic parameter list required to build a desired object.
        /// @return new object instance of type T
        template<class T, class... Args>
        static SafeRef<T> newObject(Args &&... args);

        /// Create a new copy of a given object.
        /// @note If the given object has been previously created via @b newObject method and the second argument is set to false, this method returns himself
        /// @tparam T the type of object to be copied
        /// @param original the object to be copied
        /// @param duplicate boolean value used to force copy operation to create a new instance.
        /// @return the copy of given instance or himself if it has been previously created with @b newObject
        template<class T>
        static Ref<T> copyObject(T &&original, gboolean duplicate = false);

        /// Convert given object to rvalue reference.
        /// @tparam T the type of object to move
        /// @param object C heap object in which the variable resides, if any, else null the object to be moved
        /// @return the rvalue reference version of a given object
        template<class T>
        static CORE_FAST NoRef<T> &&moveObject(T &&object);

        /// Perfect forwarding.
        /// @tparam T the type of given object
        /// @param object C heap object in which the variable resides, if any, else null the given object
        /// @return the given object.
        template<class T>
        static CORE_FAST T &&forwardObject(NoRef<T> &object);

        /// Perfect forwarding.
        /// @tparam T the type of given object
        /// @param object C heap object in which the variable resides, if any, else null the given object
        /// @return the given object.
        template<class T>
        static CORE_FAST NoLvalue<T> &&forwardObject(NoRef<T> &&object);

        // wrappers for malloc, realloc, etc.

        /// Allocates a new block of native memory, of the given size in bytes.
        /// The contents of the memory are uninitialized; they will generally be garbage.
        /// The resulting native pointer will never be zero, and will be aligned for all value types.
        /// Dispose of this memory by calling @c VH::deallocateMemory, or resize it with @c VH::reallocateMemory.
        /// @note It is the responsibility of the caller to make sure arguments are checked before the methods are called.
        /// While some rudimentary checks are performed on the input, the checks are the best effort and when performance is an overriding priority, as when methods of this class are optimized by the runtime compiler, some or all checks (if any) may be elided.
        /// Hence, the caller must not rely on the checks and corresponding exceptions!
        /// @param sizeInBytes the size of memory block to be allocated
        /// @return the address of memory block allocated.
        /// @throws RuntimeException if the size is negative or too large for the native @c size_t type
        /// @throws OutOfMemoryError if the system refuses the allocation
        static glong allocateMemory(glong sizeInBytes);

        /// Resizes a new block of native memory, to the given size in bytes.
        /// The contents of the new block past the size of the old block are uninitialized; they will generally be garbage.
        /// The resulting native pointer will be zero if and only if the requested size is zero.
        /// The resulting native pointer will be aligned for all value types.
        /// Dispose of this memory by calling @c VH::deallocateMemory, or resize it with @c Unsafe::reallocateMemory.
        /// The address passed to this method may be null, in which case an allocation will be performed.
        /// @note It is the responsibility of the caller to make sure arguments are checked before the methods are called.
        /// While some rudimentary checks are performed on the input, the checks are the best effort and when performance is an overriding priority, as when methods of this class are optimized by the runtime compiler, some or all checks (if any) may be elided.
        /// Hence, the caller must not rely on the checks and corresponding exceptions!
        /// @param sizeInBytes the new size of memory block to be resized
        /// @return the address of block resized.
        /// @throws RuntimeException if the size is negative or too large for the native @c size_t type
        /// @throws OutOfMemoryError if the system refuses the allocation
        /// @see VH::allocateMemory
        static glong reallocateMemory(glong address, glong sizeInBytes);

        /// Sets all bytes in a given block of memory to a fixed value (usually zero).
        ///
        /// This method determines a block's base address by two parameters, and so it provides (in effect) a <em>double-register</em> addressing mode, as discussed in @code VH::getInt(Object, long) @endcode .
        /// When the object reference is null, the offset supplies an absolute base address.
        ///
        /// The stores are incoherent (atomic) units of a size determined by the address and length parameters.
        /// If the effective address and length are all even modulo 8, the stores take place in 'long' units.
        /// If the effective address and length are (resp.) even modulo 4 or 2, the stores take place in units of 'int' or 'short'.
        /// @note It is the responsibility of the caller to make sure arguments are checked before the methods are called.
        /// While some rudimentary checks are performed on the input, the checks are the best effort and when performance is an overriding priority, as when methods of this class are optimized by the runtime compiler, some or all checks (if any) may be elided.
        /// Hence, the caller must not rely on the checks and corresponding exceptions!
        /// @param object C heap object in which the variable resides, if any, else null
        /// @param offset indication of where the variable resides in a C heap object, if any, else a memory address locating the variable statically
        /// @param sizeInBytes the size of memory block to be set.
        /// @param newValue the value to store into given number of bytes of the indicated C variable
        /// @throws RuntimeException if any of the arguments is invalid
        static void setMemory(const Object &object, glong offset, glong sizeInBytes, gbyte newValue);

        /// Sets all bytes in a given block of memory to a copy of another block.
        /// This method determines each block's base address by means of two parameters, and so it provides (in effect) a <em>double-register</em> addressing mode, as discussed in @c Unsafe::getInt(Object,long).
        /// When the object reference is null, the offset supplies an absolute base address.
        ///
        /// The transfers are in coherent (atomic) units of a size determined by the address and length parameters.
        /// If the effective addresses and length are all even modulo 8, the transfer takes place in 'long' units.
        /// If the effective addresses and length are (resp.) even modulo 4 or 2, the transfer takes place in units of 'int' or 'short'.
        ///
        /// @note It is the responsibility of the caller to make sure arguments are checked before the methods are called.
        /// While some rudimentary checks are performed on the input, the checks are the best effort and when performance is an overriding priority, as when methods of this class are optimized by the runtime compiler, some or all checks (if any) may be elided.
        /// Hence, the caller must not rely on the checks and corresponding exceptions!
        /// @param sourceObject C heap object in which the source variable resides, if any, else null
        /// @param sourceOffset indication of where the source variable resides in a C heap object, if any, else a memory address locating the source variable statically
        /// @param destinationObject C heap object in which the destination variable resides, if any, else null
        /// @param destinationOffset indication of where the destionation variable resides in a C heap object, if any, else a memory address locating the destionation variable statically
        /// @param sizeInBytes the size of memory block to be copied
        /// @throws RuntimeException if any of the arguments is invalid
        static void copyMemory(const Object &sourceObject, glong sourceOffset, const Object &destinationObject,
                               glong destinationOffset, glong sizeInBytes);

        /// Copies all elements from one block of memory to another block, *unconditionally* byte swapping the elements on the fly.
        /// This method determines each block's base address by means of two parameters, and so it provides (in effect) a <em>double-register</em> addressing mode, as discussed in @code VH::getInt(Object, long) @endcode .
        /// When the object reference is null, the offset supplies an absolute base address.
        ///
        /// @note It is the responsibility of the caller to make sure arguments are checked before the methods are called.
        /// While some rudimentary checks are performed on the input, the checks are the best effort and when performance is an overriding priority, as when methods of this class are optimized by the runtime compiler, some or all checks (if any) may be elided.
        /// Hence, the caller must not rely on the checks and corresponding exceptions!
        /// @param sourceObject C heap object in which the source variable resides, if any, else null
        /// @param sourceOffset indication of where the source variable resides in a C heap object, if any, else a memory address locating the source variable statically
        /// @param destinationObject C heap object in which the destination variable resides, if any, else null
        /// @param destinationOffset indication of where the destination variable resides in a C heap object, if any, else a memory address locating the destination variable statically
        /// @param sizeInBytes the size of memory block to be copied
        /// @param elementSize the memory blocks element to be swapped during copy. (this value must be 2, 4, or 8)
        /// @throws RuntimeException if any of the arguments is invalid
        static void copySwapMemory(const Object &sourceObject, glong sourceOffset, const Object &destinationObject,
                                   glong destinationOffset, glong sizeInBytes, glong elementSize);

        /// Disposes of a block of native memory, as obtained from @c VH::allocateMemory or @c VH::reallocateMemory.
        /// The address passed to this method may be null, in which case no action is taken.
        /// @note It is the responsibility of the caller to make sure arguments are checked before the methods are called.
        /// While some rudimentary checks are performed on the input, the checks are the best effort and when performance is an overriding priority, as when methods of this class are optimized by the runtime compiler, some or all checks (if any) may be elided.
        /// Hence, the caller must not rely on the checks and corresponding exceptions!
        /// @param address
        /// @throws RuntimeException if any of the arguments is invalid
        static void deallocateMemory(glong address);

        // offset constants

        CORE_WARNING_PUSH
        CORE_WARNING_DISABLE_INVALID_OFFSETOF
        static CORE_FAST glong ARRAY_BASE_OFFSET = CORE_FIELD_OFFSET(ByteArray, values);
        static CORE_FAST glong ARRAY_OBJECT_BASE_OFFSET = CORE_FIELD_OFFSET(spi::AbstractObjectArray, values);
        CORE_WARNING_POP
        static CORE_FAST glong ARRAY_BOOLEAN_INDEX_SCALE = Boolean::SIZE;
        static CORE_FAST glong ARRAY_BYTE_INDEX_SCALE = Byte::SIZE;
        static CORE_FAST glong ARRAY_SHORT_INDEX_SCALE = Short::SIZE;
        static CORE_FAST glong ARRAY_CHAR_INDEX_SCALE = Character::SIZE;
        static CORE_FAST glong ARRAY_INT_INDEX_SCALE = Integer::SIZE;
        static CORE_FAST glong ARRAY_LONG_INDEX_SCALE = Long::SIZE;
        static CORE_FAST glong ARRAY_FLOAT_INDEX_SCALE = Float::SIZE;
        static CORE_FAST glong ARRAY_DOUBLE_INDEX_SCALE = Double::SIZE;

    private:
        // Builders

        /// Create a short value from given bytes values
        /// @param b0 the 1st value
        /// @param b1 the 2nd value
        /// @return a short value
        static gshort makeShort(gbyte b0, gbyte b1);

        /// Create char value from given bytes values
        /// @param b0 the 1st value
        /// @param b1 the 2nd value
        /// @return a char value
        static gchar makeChar(gbyte b0, gbyte b1);

        /// Create int value from given bytes values
        /// @param b0 the 1st value
        /// @param b1 the 2nd value
        /// @param b2 the 3rd value
        /// @param b3 the 4th value
        /// @return an int value
        static gint makeInt(gbyte b0, gbyte b1, gbyte b2, gbyte b3);

        /// Create long value from given bytes values
        /// @param b0 the 1st value
        /// @param b1 the 2nd value
        /// @param b2 the 3rd value
        /// @param b3 the 4th value
        /// @param b4 the 5th value
        /// @param b5 the 6th value
        /// @param b6 the 7th value
        /// @param b7 the 8th value
        /// @return a long value
        static glong makeLong(gbyte b0, gbyte b1, gbyte b2, gbyte b3, gbyte b4, gbyte b5, gbyte b6, gbyte b7);

        /// Create int value from given shorts values
        /// @param s0 the 1st value
        /// @param s1 the 2nd value
        /// @return an int value
        static gint makeInt(gshort s0, gshort s1);

        /// Create int value from given shorts values
        /// @param s0 the 1st value
        /// @param s1 the 2nd value
        /// @param s2 the 3rd value
        /// @param s3 the 4th value
        /// @return an int value
        static glong makeLong(gshort s0, gshort s1, gshort s2, gshort s3);

        /// Create long from given ints values
        /// @param i0 the 1st value
        /// @param i1 the 2nd value
        /// @return a long value
        static glong makeLong(gint i0, gint i1);

        // Picker

        static gbyte pick(gbyte be, gbyte le);

        static gshort pick(gshort be, gshort le);

        static gint pick(gint be, gint le);

        static gint pickDistance(gint top, gint pos);

        // Parts writers

        static void writeParts(const Object &object, glong offset, gbyte b0, gbyte b1);

        static void writeParts(const Object &object, glong offset, gbyte b0, gbyte b1, gbyte b2, gbyte b3);

        static void writeParts(const Object &object, glong offset, gbyte b0, gbyte b1, gbyte b2, gbyte b3, gbyte b4,
                               gbyte b5, gbyte b6, gbyte b7);

        static void writeParts(const Object &object, glong offset, gshort s0, gshort s1, gshort s2, gshort s3);

        static void writeParts(const Object &object, glong offset, gshort s0, gshort s1);

        static void writeParts(const Object &object, glong offset, gint i0, gint i1);

        // Zero-extend an integer

        static gint toUnsignedInt(gbyte b);

        static gint toUnsignedInt(gshort s);

        static glong toUnsignedLong(gbyte b);

        static glong toUnsignedLong(gshort s);

        static glong toUnsignedLong(gint i);

        // Maybe byte-reverse an integer

        static gshort convertEndian(gboolean bigEndian, gshort s);

        static gchar convertEndian(gboolean bigEndian, gchar c);

        static gint convertEndian(gboolean bigEndian, gint i);

        static glong convertEndian(gboolean bigEndian, glong l);

        // Object store of cache

        template<class T>
        class DefaultStore : public Object
        {
        public:
            ~DefaultStore() override = default;

            virtual Object &loadObject(const T &) { return null; }

            virtual Object &storeObject(T &object) { return null; }

            virtual gboolean compareObject(const T &a, const T &b) { return false; }

            Object &clone() const override {
                CloneNotSupportedException($toString(clone)).throws($ftrace());
            }
        };

        class ObjectStore : public DefaultStore<Object>
        {
        public:
            ~ObjectStore() override = default;

            Object &loadObject(const Object &object) override;

            Object &storeObject(Object &object) override;

            gboolean compareObject(const Object &a, const Object &b) override;
        };

        class StaticCache : public ObjectStore
        {
        public:
            ~StaticCache() override = default;

            static Object &getDefaultCache();

            static Object &getSharedCache();

            static Object &getExclusiveCache();

            static Object &getEnumCache();

            static Object &getCache(glong metadata);

            static void checkOffset(glong offset);

            static void checkSize(glong sizeInBytes);

            static void checkObject(glong metadata);

            static glong resolveOffset(const Object &object, glong offset);

            static glong newHeap(glong heapSize);
        };

        template<class T,
            gboolean isCopyable = Class<T>::template isConstructible<const T &>(),
            gboolean isCloneable = Class<Object>::isBaseOf<T>()>
        class ObjectFactory : public Object
        {
            ObjectFactory() = default;

        public:
            ~ObjectFactory() override = default;

            template<class U>
            static Ref<T> newCopy(U &&original) {
                UnsupportedOperationException($toString(Non copyable type)).throws($ftrace());
            }
        };

        template<class T>
        class ObjectFactory<T, true, true> : public Object
        {
            ObjectFactory() = default;

        public:
            ~ObjectFactory() override = default;

            template<class U>
            static Ref<T> newCopy(U &&original) {
                try {
                    // Try copy by cloning
                    return ObjectFactory<T, false, true>::newCopy(forwardObject<U>(original));
                }
                catch (const CloneNotSupportedException &cnse) {
                    // Fallback copy using copy-constructor
                    return ObjectFactory<T, true, false>::newCopy(forwardObject<U>(original));
                }
            }
        };

        template<class T>
        class ObjectFactory<T, true, false> : public Object
        {
            ObjectFactory() = default;

        public:
            ~ObjectFactory() override = default;

            template<class U>
            static Ref<T> newCopy(U &&original) {
                CORE_FAST_ASSERT(Class<Object>::isBaseOf<U>());
                return newObject<T>(forwardObject<U>(original));
            }
        };

        template<class T>
        class ObjectFactory<T, false, true> : public Object
        {
            ObjectFactory() = default;

        public:
            ~ObjectFactory() override = default;

            template<class U>
            static Ref<T> newCopy(U &&original) {
                const Object &source = $cast(const Object&, original);
                Object &result = source.clone();
                if (&result == &source)
                    CloneNotSupportedException($toString()).throws($ftrace());
                return $cast(Ref<T>, result);
            }
        };

        template<class T>
        $alias(Store, Class<ObjectStore>::IfOrElse<Class<Object>::isBaseOf<T>(), DefaultStore<T>>);
    };

    template<class T, class... Args>
    VarHandle::SafeRef<T> VarHandle::newObject(Args &&... args) {
        $alias(SafePtr, typename Class<Slimmed<T>>::Pointer);
        $alias(SafeType, Slimmed<T>);
        // Prepare cache store
        Store<SafeType> store;
        // Allocate memory space required to create a new instance of type T
        glong heap = StaticCache::newHeap(Class<T>::SIZE);
        // Build the instance in the heap previously allocated
        new((SafePtr) heap) SafeType(forwardObject<Args>(args)...);
        // Store the instance into cache for the next usage.
        Object &result = store.storeObject(StaticCache::getCache(heap));
        return $cast(SafeRef<T>, result);
    }

    template<class T>
    VarHandle::Ref<T> VarHandle::copyObject(T &&original, gboolean duplicate) {
        $alias(SafeType, Slimmed<T>);
        Store<SafeType> store;
        Object &existingObject = duplicate ? null : store.loadObject(original);
        if (existingObject != null || ClassOf(null)::hasInstance(original)) return $cast(Ref<T>, existingObject);
        return ObjectFactory<SafeType>::newCopy(forwardObject<T>(original));
    }

    template<class T>
    CORE_FAST VarHandle::NoRef<T> &&VarHandle::moveObject(T &&object) { return (NoRef<T> &&) object; }

    template<class T>
    CORE_FAST T &&VarHandle::forwardObject(NoRef<T> &object) { return (T &&) object; }

    template<class T>
    CORE_FAST VarHandle::NoLvalue<T> &&VarHandle::forwardObject(NoRef<T> &&object) { return (T &&) object; }
} // lang
// core

#endif // CORE_LANG_FIELDS_H
