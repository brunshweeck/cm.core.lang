//
// Created by brunshweeck on 01/05/25.
//

#ifndef CORE_LANG_SHORTARRAY_H
#define CORE_LANG_SHORTARRAY_H
#include "Integer.h"
#include "Short.h"
#include "spi/AbstractPrimitiveArray.h"

namespace core
{
    /// The class {@code ShortArray} wraps the array of a primitive type {@code short} in the object.
    /// An object of type {@code ShortArray} contains two fields whose first is a pointer of {@code short}, and the second is the number of places allocated in this pointer.
    /// In Addition, this class provides several methods for random access to any value stored, for converting this array type to {@code String}, and generate an array from a specified generator function.
    class ShortArray $final : public lang::spi::AbstractPrimitiveArray<Short, ShortArray>
    {
        class ReferenceStep;
        class ConstantStep;

    public:
        /// Construct new empty {@code ShortArray}.
        ShortArray() = default;

        /// Construct new {@code ShortArray} and initialize content with given values.
        /// @param values the list of value to be used to initialize elements of this array.
        ShortArray(VarArgs values);

        /// Construct new {@code ShortArray} able to contain the given number of values.
        /// During this operation, Each value will be initialized with a given {@code initializer} value.
        /// @param length the number of elements to be allocated into a resulting array.
        /// @throws IllegalArgumentException If the specified length is negative.
        CORE_EXPLICIT ShortArray(gint length, gshort initializer = 0);

        /// Construct new  {@code ShortArray} containing the elements of specified array; in other they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into a resulting array.
        ShortArray(const ShortArray& other);

        /// Set the content of this {@code ShortArray} with its specified array; During this operation, the elements will be copied to this array in order they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into this array as new content.
        /// @return this array
        ShortArray& operator=(const ShortArray& other);

        /// Construct new  {@code ShortArray} containing the elements of specified array; in other they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into a resulting array.
        ShortArray(ShortArray&& other) CORE_NOTHROW;

        /// Set the content of this {@code ShortArray} with its specified array; During this operation, the elements will be copied to this array in order they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into this array as new content.
        /// @return this array
        ShortArray& operator=(ShortArray&& other) CORE_NOTHROW;

        ~ShortArray() override;

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
        gshort& get(gint index) override;

        /// Returns the element at the specified position in this array.
        /// @param index index of the element to return
        /// @return the element at the specified position in this array
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        const gshort& get(gint index) const override;

        /// Replaces the element at the specified position in this list with the specified element.
        /// @param index index of the element to replace.
        /// @param newValue element to be stored at the specified position
        /// @return the element previously at the specified position
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        gshort set(gint index, gshort newValue) override;

        /// Compare the content of given array with this array.
        /// @param other the array to be compared
        /// @return {@code true} if this array and given array have the same content.
        gboolean equals(const Object& other) const override;

        /// Return the hash code of this array.
        /// @return the hash code of this array.
        gint hash() const override;

        /// Return the string representation of this array.
        /// @return the string representation of this array.
        String toString() const override;

        /// Return the shadow copy of this array.
        /// @return the shadow copy of this array.
        ShortArray& clone() const override;

        /// Return a new array containing an arbitrary number of elements.
        /// @tparam Args the types of given arguments
        /// @param args the elements to be contained in the array
        /// @return an array containing the specified elements
        template <class... Args>
        static ShortArray of(const Args&... args);

        /// Return a new array containing the ordered value of the specified range.
        /// The order is defined by value of {@code offsetByValue} parameter.
        /// In other words, if {@code offsetByValue} is negative content of the resulting array will be sorted from {@code end} value to {@code start} value, in otherwise the resulting array will be sorted from {@code start} value to {@code end} value.
        /// @param start the min bound of range (inclusive)
        /// @param end the max bound of range (exclusive)
        /// @param offsetByValue the offset between two values into range.
        /// @return a new array containing the ordered value of the specified range.
        /// @throws IllegalArgumentException
        ///                 - if the given {@code offsetByValue} argument is zero
        ///                 - if {@code start } value less than {@code end} value and  {@code offsetByValue} is negative;
        ///                 - if {@code start } value greater than {@code end} value and  {@code offsetByValue} is positive.
        /// @throws OutOfMemoryException if the number of elements in specified range exceeds array implementation limit.
        static ShortArray ofRange(gshort start, gshort end, gint offsetByValue = 1);

        /// Returns an array containing the elements of the given array, in its iteration order.
        /// If the given array is subsequently modified, the returned array will not reflect such modifications.
        /// @note The value {@code 0} will replace each undefined element of a given array.
        /// @param array an array from which elements are drawn.
        /// @return an array containing the elements of the given array.
        static ShortArray copyOf(const Array<Short>& array);

        /// Returns an array containing the elements of the given array, in its iteration order.
        /// If the given array is subsequently modified, the returned array will not reflect such modifications.
        /// @tparam Array the type of given array
        /// @param array an array from which elements are drawn.
        /// @return an array containing the elements of the given array.
        template <class Array, ClassOf(true)::OnlyIf<Class<Array>::isArray()>  = true,
                  class Item = typename Class<Array>::NoArray, ClassOf(true)::OnlyIf<Class<Item>::isNumber()>  = true>
        static ShortArray copyOf(const Array& array);

        CORE_INTRINSIC_INDEXED_ITEM_ACCESS_DECL(gshort, gint);

        CORE_INTRINSIC_FOR_EACH_DECL(ConstantStep, ReferenceStep);
    };

    class ShortArray::ReferenceStep $final : public AbstractStep
    {
        ShortArray& array;
        gint index;

    public:
        CORE_EXPLICIT ReferenceStep(ShortArray& array, gboolean gotoEnd);

        ~ReferenceStep() override = default;

        gshort& get() override;

        ReferenceStep& next() override;

        gboolean isDone() const override;

    private:
        gint position() const override;

        const Object& target() const override;
    };

    class ShortArray::ConstantStep $final : public AbstractConstantStep
    {
        const ShortArray& array;
        gint index;

    public:
        CORE_EXPLICIT ConstantStep(const ShortArray& array, gboolean gotoEnd);

        ~ConstantStep() override = default;

        const gshort& get() override;

        ConstantStep& next() override;

        gboolean isDone() const override;

    private:
        gint position() const override;

        const Object& target() const override;
    };

    template <class... Args>
    ShortArray ShortArray::of(const Args&... args) {
        CORE_FAST_ASSERT(ClassOf(true)::ALL<Class<Args>::isNumber()...>);
        gshort values[] = {(gshort)args...};
        return ShortArray::copyOf(values);
    }

    template <class Array, ClassOf(true)::OnlyIf<Class<Array>::isArray()>,
              class Item, ClassOf(true)::OnlyIf<Class<Item>::isNumber()>>
    ShortArray ShortArray::copyOf(const Array& array) {
        CORE_FAST glong aLen = ClassOf(array)::COUNT;
        gint length = aLen > Integer::MAX_VALUE ? Integer::MAX_VALUE : aLen;
        ShortArray copy = ShortArray(length);
        for (gint i = 0; i < length; i += 1) copy[i] = (gshort)array[i];
        return copy;
    }
} // core

#endif // CORE_LANG_SHORTARRAY_H
