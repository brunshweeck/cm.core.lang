//
// Created by brunshweeck on 4/19/25.
//

#ifndef CORE_LANG_BOOLEAN_H
#define CORE_LANG_BOOLEAN_H
#include "Byte.h"
#include "Comparable.h"

namespace core
{
    ///  The Boolean class wraps a value of the primitive type @c gboolean in an object.
    ///  An object of type @c Boolean contains a single field whose type is @c gboolean.
    class Boolean $final : public lang::Comparable<Boolean>
    {
        /// The value of the Boolean.
        gboolean value;

    public:
        /// The @c Boolean object corresponding to the primitive value @c true.
        static const Boolean TRUE;

        /// The @c Boolean object corresponding to the primitive value @c false
        static const Boolean FALSE;

        /// The number of bits used to represent a byte value in two's complement binary form.
        static CORE_FAST gint SIZE = 8;

        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        /// Allocates a @c Boolean object representing the @c value argument.
        /// @param value The value of the @c Boolean.
        Boolean(gboolean value = false);

        ~Boolean() override = default;

        /// Parses the string argument as a boolean.
        /// The @c boolean returned represents the value @c true if the string argument is equal, ignoring case, to the string @c "true".
        /// Otherwise, a false value is returned. Example:
        ///     @code
        ///         Boolean::parse("True") returns true
        ///         Boolean::parse("yes") returns false
        ///     @endcode
        /// @param str The @c String containing the boolean representation to be parsed.
        /// @return The boolean represented by the string argument.
        static gboolean parseBoolean(const String& str);

        /// Returns the value of this @c Boolean object as a boolean primitive.
        /// @return The primitive boolean value of this object.
        gboolean booleanValue() const;

        /// Returns a @c Boolean instance representing the specified boolean value.
        /// If the specified boolean value is @c true, this method returns @c Boolean::TRUE;
        /// if it is @c false, this method returns @c Boolean::FALSE.
        /// @param value A boolean value.
        /// @return A @c Boolean instance representing @c b.
        static Boolean valueOf(gboolean value);

        /// Returns a @c Boolean with a value represented by the specified string.
        /// The @c Boolean returned represents a true value if the string argument is equal, ignoring case, to the string @c "true".
        /// Otherwise, a false value is returned.
        /// @param str A string
        /// @return The @c Boolean value represented by the string.
        static Boolean valueOf(const String& str);

        /// Returns a @c String object representing the specified boolean.
        /// If the specified boolean is @c true, then the string @c "true" will be returned, otherwise the string @c "false" will be returned.
        /// @param value The boolean to be converted.
        /// @return The string representation of the specified boolean
        static String toString(gboolean value);

        /// Returns a @c String object representing this Boolean's value.
        /// If this object represents the value @c true, a string equal to @c "true" is returned.
        /// Otherwise, a string equal to @c "false" is returned.
        /// @return A string representation of this object.
        String toString() const override;

        /// Returns a hash code for this @c Boolean object.
        /// @return The integer @c 1231 if this object represents @c true;
        ///                the integer @c 1237 if this object represents @c false.
        gint hash() const override;

        /// Returns a hash code for a @c boolean value; compatible with @c Boolean::hash().
        /// @param value The value to hash
        /// @return A hash code value for a @c boolean value.
        static gint hash(gboolean value);

        /// Returns @c true if and only if the argument is not @c null and is a @c Boolean object that represents the same @c boolean value as this object.
        /// @param other the object to compare with.
        /// @return The value @c true if the Boolean objects represent the same value; @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Compares this @c Boolean instance with another.
        /// @param other The @c Boolean instance to be compared.
        /// @return zero if this object represents the same boolean value as the argument;
        ///               a positive value if this object represents true and the argument represents false;
        ///               and a negative value if this object represents false and the argument represents true.
        gint compareTo(const Boolean& other) const override;

        /// Compares two boolean values.
        /// The value returned is identical to what would be returned by @code Boolean::valueOf(a).compareTo(Boolean::valueOf(b)) @endcode
        /// @param a The first @c boolean to compare.
        /// @param b The second @c boolean to compare.
        /// @return The value @c 0 if @code a == b @endcode ;
        ///                a value less than @c 0 if @code !a && b @endcode ;
        ///                and a value greater than @c 0 if @code a && !b @endcode.
        static gint compare(gboolean a, gboolean b);

        /// Returns the result of applying the logical OR operator to the specified @c boolean operands.
        /// @param a The first operand
        /// @param b The second operand.
        /// @return The logical OR of @c a and @c b.
        static gboolean logicalAnd(gboolean a, gboolean b);

        /// Returns the result of applying the logical AND operator to the specified @c boolean operands.
        /// @param a The first operand
        /// @param b The second operand.
        /// @return The logical AND of @c a and @c b.
        static gboolean logicalOr(gboolean a, gboolean b);

        /// Returns the result of applying the logical XOR operator to the specified @c boolean operands.
        /// @param a The first operand
        /// @param b The second operand.
        /// @return The logical XOR of @c a and @c b.
        static gboolean logicalXor(gboolean a, gboolean b);

        Boolean& clone() const override;
    };
} // core

#endif // CORE_LANG_BOOLEAN_H
