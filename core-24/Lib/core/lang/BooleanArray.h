//
// Created by brunshweeck on 4/29/25.
//

#ifndef CORE_LANG_BOOLEANARRAY_H
#define CORE_LANG_BOOLEANARRAY_H
#include "Integer.h"
#include "Boolean.h"
#include "spi/AbstractPrimitiveArray.h"

namespace core
{
    /// The class {@code BooleanArray} wraps the array of a primitive type {@code bool} in the object.
    /// An object of type {@code BooleanArray} contains two fields whose first is a pointer of {@code bool}, and the second is the number of places allocated in this pointer.
    /// In Addition, this class provides several methods for random access to any value stored, for converting this array type to {@code String}, and generate an array from a specified generator function.
    class BooleanArray $final : public lang::spi::AbstractPrimitiveArray<Boolean, BooleanArray>
    {
        class ReferenceStep;
        class ConstantStep;

    public:
        /// Construct new empty {@code BooleanArray}.
        BooleanArray() = default;

        /// Construct new {@code BooleanArray} and initialize content with given values.
        /// @param values the list of value to be used to initialize elements of this array.
        BooleanArray(VarArgs values);

        /// Construct new {@code BooleanArray} able to contain the given number of values.
        /// During this operation, Each value will be initialized with given {@code initializer} value.
        /// @param length the number of elements to be allocated into a resulting array.
        /// @throws IllegalArgumentException If the specified length is negative.
        CORE_EXPLICIT BooleanArray(gint length, gboolean initializer = false);

        /// Construct new  {@code BooleanArray} containing the elements of specified array; in other they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into a resulting array.
        BooleanArray(const BooleanArray& other);

        /// Set the content of this {@code BooleanArray} with its specified array; During this operation, the elements will be copied to this array in order they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into this array as new content.
        /// @return this array
        BooleanArray& operator=(const BooleanArray& other);

        /// Construct new  {@code BooleanArray} containing the elements of specified array; in other they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into a resulting array.
        BooleanArray(BooleanArray&& other) CORE_NOTHROW;

        /// Set the content of this {@code BooleanArray} with its specified array; During this operation, the elements will be copied to this array in order they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into this array as new content.
        /// @return this array
        BooleanArray& operator=(BooleanArray&& other) CORE_NOTHROW;

        ~BooleanArray() override;

        /// Returns the number of elements in this array.
        /// @return the number of elements in this array.
        gint length() const override;

        /// Return @c true if this array contains no elements.
        /// @return @c true if this array contains no elements.
        gboolean isEmpty() const override;

        /// Returns the element at the specified position in this array.
        /// @param index index of the element to return
        /// @return the element at the specified position in this array
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        gboolean& get(gint index) override;

        /// Returns the element at the specified position in this array.
        /// @param index index of the element to return
        /// @return the element at the specified position in this array
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        const gboolean& get(gint index) const override;

        /// Replaces the element at the specified position in this list with the specified element.
        /// @param index index of the element to replace.
        /// @param newValue element to be stored at the specified position
        /// @return the element previously at the specified position
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        gboolean set(gint index, gboolean newValue) override;

        /// Compare the content of given array with this array.
        /// @param other the array to be compared
        /// @return {@code true} if this array and given array have same content.
        gboolean equals(const Object& other) const override;

        /// Return the hash code of this array.
        /// @return the hash code of this array.
        gint hash() const override;

        /// Return the string representation of this array.
        /// @return the string representation of this array.
        String toString() const override;

        /// Return the shadow copy of this array.
        /// @return the shadow copy of this array.
        BooleanArray& clone() const override;

        /// Return a new array containing an arbitrary number of elements.
        /// @tparam Args the types of given arguments
        /// @param args the elements to be contained in the array
        /// @return an array containing the specified elements
        template <class... Args>
        static BooleanArray of(const Args&... args);

        /// Returns an array containing the elements of the given array, in its iteration order.
        /// If the given array is subsequently modified, the returned array will not reflect such modifications.
        /// @note The value {@code false} will replace each undefined element of a given array.
        /// @param array an array from which elements are drawn.
        /// @return an array containing the elements of the given array.
        static BooleanArray copyOf(const Array<Boolean>& array);

        /// Returns an array containing the elements of the given array, in its iteration order.
        /// If the given array is subsequently modified, the returned array will not reflect such modifications.
        /// @tparam Array the type of given array
        /// @param array an array from which elements are drawn.
        /// @return an array containing the elements of the given array.
        template <class Array, ClassOf(true)::OnlyIf<Class<Array>::isArray()>  = true,
                  class Item = typename Class<Array>::NoArray, ClassOf(true)::OnlyIf<Class<Item>::isIntegral()>  = true>
        static BooleanArray copyOf(const Array& array);

        CORE_INTRINSIC_INDEXED_ITEM_ACCESS_DECL(gboolean, gint);

        CORE_INTRINSIC_FOR_EACH_DECL(ConstantStep, ReferenceStep);
    };

    class BooleanArray::ReferenceStep $final : public AbstractStep
    {
        BooleanArray& array;
        gint index;

    public:
        CORE_EXPLICIT ReferenceStep(BooleanArray& array, gboolean gotoEnd);

        ~ReferenceStep() override = default;

        gboolean& get() override;

        ReferenceStep& next() override;

        gboolean isDone() const override;

    private:
        gint position() const override;

        const Object& target() const override;
    };

    class BooleanArray::ConstantStep $final : public AbstractConstantStep
    {
        const BooleanArray& array;
        gint index;

    public:
        CORE_EXPLICIT ConstantStep(const BooleanArray& array, gboolean gotoEnd);

        ~ConstantStep() override = default;

        const gboolean& get() override;

        ConstantStep& next() override;

        gboolean isDone() const override;

    private:
        gint position() const override;

        const Object& target() const override;
    };

    template <class... Args>
    BooleanArray BooleanArray::of(const Args&... args) {
        CORE_FAST_ASSERT(ClassOf(true)::ALL<Class<Args>::isIntegral()...>);
        gboolean values[] = {(gboolean)args...};
        return BooleanArray::copyOf(values);
    }

    template <class Array, ClassOf(true)::OnlyIf<Class<Array>::isArray()>,
              class Item, ClassOf(true)::OnlyIf<Class<Item>::isIntegral()>>
    BooleanArray BooleanArray::copyOf(const Array& array) {
        CORE_FAST glong aLen = ClassOf(array)::COUNT;
        gint length = aLen > Integer::MAX_VALUE ? Integer::MAX_VALUE : aLen;
        BooleanArray copy = BooleanArray(length);
        for (gint i = 0; i < length; i += 1) copy[i] = (gboolean)array[i];
        return copy;
    }
} // core

#endif // CORE_LANG_BOOLEANARRAY_H
