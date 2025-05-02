//
// Created by brunshweeck on 4/30/25.
//

#ifndef CORE_LANG_FLOATARRAY_H
#define CORE_LANG_FLOATARRAY_H
#include "Integer.h"
#include "Float.h"
#include "spi/AbstractPrimitiveArray.h"

namespace core
{
    /// The class {@code FloatArray} wraps the array of a primitive type {@code float} in the object.
    /// An object of type {@code FloatArray} contains two fields whose first is a pointer of {@code float}, and the second is the number of places allocated in this pointer.
    /// In Addition, this class provides several methods for random access to any value stored, for converting this array type to {@code String}, and generate an array from a specified generator function.
    class FloatArray $final : public lang::spi::AbstractPrimitiveArray<Float, FloatArray>
    {
        class ReferenceStep;
        class ConstantStep;

    public:
        /// Construct new empty {@code FloatArray}.
        FloatArray() = default;

        /// Construct new {@code FloatArray} and initialize content with given values.
        /// @param values the list of value to be used to initialize elements of this array.
        FloatArray(VarArgs values);

        /// Construct new {@code FloatArray} able to contain the given number of values.
        /// During this operation, Each value will be initialized with a given {@code initializer} value.
        /// @param length the number of elements to be allocated into a resulting array.
        /// @throws IllegalArgumentException If the specified length is negative.
        CORE_EXPLICIT FloatArray(gint length, gfloat initializer = 0.0f);

        /// Construct new  {@code FloatArray} containing the elements of specified array; in other they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into a resulting array.
        FloatArray(const FloatArray& other);

        /// Set the content of this {@code FloatArray} with its specified array; During this operation, the elements will be copied to this array in order they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into this array as new content.
        /// @return this array
        FloatArray& operator=(const FloatArray& other);

        /// Construct new  {@code FloatArray} containing the elements of specified array; in other they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into a resulting array.
        FloatArray(FloatArray&& other) CORE_NOTHROW;

        /// Set the content of this {@code FloatArray} with its specified array; During this operation, the elements will be copied to this array in order they are returned by the array's iterator.
        /// @param other the array whose elements are to be placed into this array as new content.
        /// @return this array
        FloatArray& operator=(FloatArray&& other) CORE_NOTHROW;

        ~FloatArray() override;

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
        gfloat& get(gint index) override;

        /// Returns the element at the specified position in this array.
        /// @param index index of the element to return
        /// @return the element at the specified position in this array
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        const gfloat& get(gint index) const override;

        /// Replaces the element at the specified position in this list with the specified element.
        /// @param index index of the element to replace.
        /// @param newValue element to be stored at the specified position
        /// @return the element previously at the specified position
        /// @throws IndexOutOfBoundsException if index is negative or index is great-than or equals this array length.
        gfloat set(gint index, gfloat newValue) override;

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
        FloatArray& clone() const override;

        /// Return a new array containing an arbitrary number of elements.
        /// @tparam Args the types of given arguments
        /// @param args the elements to be contained in the array
        /// @return an array containing the specified elements
        template <class... Args>
        static FloatArray of(const Args&... args);

        /// Return a new array containing the ordered value of the specified range.
        /// The order is defined by value of {@code offsetByValue} parameter.
        /// In other words, if {@code offsetByValue} is negative content of the resulting array will be sorted from {@code end} value to {@code start} value, in otherwise the resulting array will be sorted from {@code start} value to {@code end} value.
        /// @param start the min bound of range (inclusive)
        /// @param end the max bound of range (exclusive)
        /// @param offsetByValue the offset between two values into range.
        /// @return a new array containing the ordered value of the specified range.
        /// @throws IllegalArgumentException
        ///                 - if the given {@code start} value is not a number;
        ///                 - if the given {@code end} value is not a number;
        ///                 - if the given {@code offsetByValue} argument is not a number or is zero
        ///                 - if {@code start } value less than {@code end} value and  {@code offsetByValue} is negative;
        ///                 - if {@code start } value greater than {@code end} value and  {@code offsetByValue} is positive.
        /// @throws OutOfMemoryException if the number of elements in specified range exceeds array implementation limit.
        static FloatArray ofRange(gfloat start, gfloat end, gfloat offsetByValue = 1.0f);

        /// Returns an array containing the elements of the given array, in its iteration order.
        /// If the given array is subsequently modified, the returned array will not reflect such modifications.
        /// @note The value {@code 0.0f} will replace each undefined element of a given array.
        /// @param array an array from which elements are drawn.
        /// @return an array containing the elements of the given array.
        static FloatArray copyOf(const Array<Float>& array);

        /// Returns an array containing the elements of the given array, in its iteration order.
        /// If the given array is subsequently modified, the returned array will not reflect such modifications.
        /// @tparam Array the type of given array
        /// @param array an array from which elements are drawn.
        /// @return an array containing the elements of the given array.
        template <class Array, ClassOf(true)::OnlyIf<Class<Array>::isArray()>  = true,
                  class Item = typename Class<Array>::NoArray, ClassOf(true)::OnlyIf<Class<Item>::isNumber()>  = true>
        static FloatArray copyOf(const Array& array);

        CORE_INTRINSIC_INDEXED_ITEM_ACCESS_DECL(gfloat, gint);

        CORE_INTRINSIC_FOR_EACH_DECL(ConstantStep, ReferenceStep);
    };

    class FloatArray::ReferenceStep $final : public AbstractStep
    {
        FloatArray& array;
        gint index;

    public:
        CORE_EXPLICIT ReferenceStep(FloatArray& array, gboolean gotoEnd);

        ~ReferenceStep() override = default;

        gfloat& get() override;

        ReferenceStep& next() override;

        gboolean isDone() const override;

    private:
        gint position() const override;

        const Object& target() const override;
    };

    class FloatArray::ConstantStep $final : public AbstractConstantStep
    {
        const FloatArray& array;
        gint index;

    public:
        CORE_EXPLICIT ConstantStep(const FloatArray& array, gboolean gotoEnd);

        ~ConstantStep() override = default;

        const gfloat& get() override;

        ConstantStep& next() override;

        gboolean isDone() const override;

    private:
        gint position() const override;

        const Object& target() const override;
    };

    template <class... Args>
    FloatArray FloatArray::of(const Args&... args) {
        CORE_FAST_ASSERT(ClassOf(true)::ALL<Class<Args>::isNumber()...>);
        gfloat values[] = {(gfloat)args...};
        return FloatArray::copyOf(values);
    }

    template <class Array, ClassOf(true)::OnlyIf<Class<Array>::isArray()>,
              class Item, ClassOf(true)::OnlyIf<Class<Item>::isNumber()>>
    FloatArray FloatArray::copyOf(const Array& array) {
        CORE_FAST glong aLen = ClassOf(array)::COUNT;
        gint length = aLen > Integer::MAX_VALUE ? Integer::MAX_VALUE : aLen;
        FloatArray copy = FloatArray(length);
        for (gint i = 0; i < length; i += 1) copy[i] = (gfloat)array[i];
        return copy;
    }
} // core

#endif // CORE_LANG_FLOATARRAY_H
