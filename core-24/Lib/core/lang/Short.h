//
// Created by brunshweeck on 4/20/25.
//

#ifndef CORE_LANG_SHORT_H
#define CORE_LANG_SHORT_H

#include "Byte.h"
#include "Comparable.h"
#include "Number.h"

namespace core
{
    /// The @c Short class wraps a value of primitive type @c short in an object.  An object of type @c Short contains a single field whose type is @c short.
    /// In addition, this class provides several methods for converting a @c short to a @c String and a @c String to a @c short, as well as other constants and methods useful when dealing with a @c short.
    class Short $final : public lang::Comparable<Short>, public lang::Number
    {
        /// The value of the @c Short.
        gshort value;

    public:
        /// A constant holding the maximum value a short can have, 2<sup>15</sup> -1
        static CORE_FAST gshort MAX_VALUE = 0x7FFF;

        /// A constant holding the minimum value a short can have,  -2<sup>15</sup>
        static CORE_FAST gshort MIN_VALUE = 0x8000;

        /// The number of bits used to represent a @c gshort value in two's complement binary form.
        static CORE_FAST gint SIZE = 1 << 4;

        static CORE_FAST gint SHORTS = SIZE / Byte::SIZE;

        /// Constructs a newly allocated @c Short object that represents the specified @c short value.
        /// @param value the value to be represented by the @c Short
        Short(gshort value = 0);

        ~Short() override = default;

        /// Returns the value of this @c Short as a @c gbyte after a narrowing primitive conversion.
        /// @return The value of this @c Short as gshort.
        gbyte byteValue() const override;

        /// Returns the value of this @c Short as a @c gshort.
        /// @return The value of this @c Short as gshort.
        gshort shortValue() const override;

        /// Returns the value of this @c Short as a @c gint after a widening primitive conversion.
        /// @return The value of this @c Short as gint.
        gint intValue() const override;

        /// Returns the value of this @c Short as a @c glong after a widening primitive conversion.
        /// @return The value of this @c Short as glong.
        glong longValue() const override;

        /// Returns the value of this @c Short as a @c gfloat after a widening primitive conversion.
        /// @return The value of this @c Short as gfloat.
        gfloat floatValue() const override;

        /// Returns the value of this @c Short as a @c gdouble after a widening primitive conversion.
        /// @return The value of this @c Short as gdouble.
        gdouble doubleValue() const override;

        /// Returns a @c String object representing this @c Short 's value.
        /// The value is converted to signed decimal representation and returned as a string, exactly as if the @c gshort value were given as an argument to the @c Short::toString(gshort) method.
        /// @return A string representation of the value of this object in base @c 10.
        String toString() const override;

        /// Returns a new @c String object representing the specified @c gshort. The radix is assumed to be 10.
        /// @param value The short int to be converted
        /// @return The string representation of the specified short int.
        static String toString(gshort value);

        ///  Returns a @c Short instance representing the specified short value.
        /// @param value A short value.
        /// @return A @c Short instance representing @c value.
        static Short valueOf(gshort value);

        /// Returns a @c Short object holding the value extracted from the specified @c String when parsed with the radix given by the second argument.
        /// The first argument is interpreted as representing a signed @c gshort in the radix specified by the second argument, exactly as if the argument were given to the @c parseShort(String,gint) method.
        /// The result is a @c Short object that represents the @c gshort value specified by the string.
        /// In other words, this method returns a @c Short object equal to the value of: @c Short::valueOf(Short::parseShort(s,radix))
        /// @param str The string to be parsed.
        /// @param radix The radix to be used in interpreting string.
        /// @return A @c Short object holding the value represented by the string argument in the specified radix.
        /// @throws NumberFormatException If the @c String does not contain a parsable short.
        static Short valueOf(const String& str, gint radix = 10);

        /// Parses the string argument as a signed short in the radix specified by the second argument.
        /// The characters in the string must all be digits, of the specified radix (as etermined by whether @code Character::digit(gchar, gint) @endcode returns a non-negative value) except that the first character may be an ASCII minus sign @c '-' (U+002D) to indicate a negative value or an ASCII plus sign @c '+' (U+002B) to indicate a positive value.
        /// The resulting short value is returned.
        /// An exception of type @c NumberFormatException is thrown if any of the following situations occurs:
        /// - The first argument is a string of length zero;
        /// - The radix is either smaller than @c Character::MIN_RADIX or larger than @c Character::MAX_RADIX;
        /// - Any character of the string is not a digit of the pecified radix, except that the first character may be a minus sign @c '-' (U+002D) or plus sign @c '+' (U+002B) provided that the string is longer than length @c 1;
        /// - The value represented by the string is not a value of type @c gshort.
        /// @param str The @c String containing the short representation to be parsed
        /// @param radix The radix to be used while parsing string.
        /// @return The short value represented by the string argument in the specified radix.
        /// @throws NumberFormatException If the string does not contain a parsable @c gshort.
        static gshort parseShort(const String& str, gint radix = 10);

        /// Returns a hash code for this @c Short; equal to the result of invoking @c intValue().
        /// @return A hash code value for this @c Short.
        gint hash() const override;

        /// Returns a hash code for a @c gshort value; compatible with @c Short::hash().
        /// @param value The value to hash
        /// @return A hash code value for a @c gshort value.
        static gint hash(gshort value);

        /// Compares this object to the specified object.
        /// The result is @c true if and only if the argument is a @c Short object that contains the same @c gshort value as this object.
        /// @param other The object to compare with
        /// @return The value @c true if the objects are the same; @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Compares two @c Short objects numerically.
        /// @param other The @c Short to be compared.
        /// @return The value @c 0 if this @c Short is equal to the argument @c Short;
        ///                 a value less than @c 0 if this @c Short is numerically less than the argument @c Short;
        ///                 and a value greater than @c 0 if this @c Short is numerically greater than the argument @c Short (signed comparison).
        gint compareTo(const Short& other) const override;

        /// Compares two @c gshort values numerically.
        /// The value returned is identical to what would be returned by @code Short::valueOf(a).compareTo(Short::valueOf(b)) @endcode
        /// @param a The first @c gshort to compare.
        /// @param b The second @c gshort to compare.
        /// @return The value @c 0 if @code a == b @endcode ; a value less than @c 0 if @code a < b @endcode ; and a value greater than @c 0 if @code a > b @endcode .
        static gint compare(gshort a, gshort b);

        /// Compares two @c gshort values numerically treating the values as unsigned.
        /// @param a The first @c gshort to compare.
        /// @param b The second @c gshort to compare.
        /// @return The value @c 0 if @code a == b @endcode ; a value less than @c 0 if @code a< b @endcode as unsigned values; and a value greater than @c 0 if @code a > b @endcode as unsigned values.
        static gint compareUnsigned(gshort a, gshort b);

        /// Converts the argument to a @c gint by an unsigned conversion.
        /// In an unsigned conversion to an @c gint, the high-order 24 bits of the @c gint are zero and the low-order 8 bits are equal to the bits of the @c gshort argument.
        /// Consequently, zero and positive @c gshort values are mapped to a numerically equal @c gint value and negative @c gshort values are mapped to an @c gint value equal to the input plus 2<sup>8</sup>.
        /// @param value The value to convert to an unsigned @c gint.
        /// @return The argument converted to @c gint by an unsigned conversion.
        static gint toUnsignedInt(gshort value);

        /// Converts the argument to a @c glong by an unsigned conversion.
        /// In an unsigned conversion to a @c glong, the high-order 56 bits of the @c glong are zero and the low-order 8 bits are equal to the bits of the @c gshort argument.
        /// Consequently, zero and positive @c gshort values are mapped to a numerically equal @c glong value and negative @c short values are mapped to a @c glong value equal to the input plus 2<sup>8</sup>.
        /// @param value The value to convert to an unsigned @c glong.
        /// @return The argument converted to @c glong by an unsigned conversion.
        static glong toUnsignedLong(gshort value);

        /// Decodes a @c String into a @c Short.
        /// Accepts decimal, hexadecimal, and octal numbers given by the following grammar:
        /// -<b>Decodable String:</b>
        /// - @em Sign <sub>opt</sub> @em DecimalNumeral ;
        /// - @em Sign <sub>opt</sub> @c 0x @em HexDigits ;
        /// - @em Sign <sub>opt</sub> @c 0X @em HexDigits ;
        /// - @em Sign <sub>opt</sub> @c # @em HexDigits ;
        /// - @em Sign <sub>opt</sub> @c 0 @em OctalDigits ;
        /// - @em Sign <sub>opt</sub> @c 0b @em BinaryDigits ;
        /// - @em Sign <sub>opt</sub> @c 0B @em BinaryDigits ;
        /// - @b Sign:
        /// - @c + (U+002D) ;
        /// - @c - (U+002B) .
        ///
        /// @em DecimalNumeral, @em HexDigits, @em OctalDigits, and @em BinaryDigits are defined in C++ language feature.
        /// The sequence of characters following an optional sign and/or radix specifier ( @c "0x", @c "0X", @c "#", @c "0b", @c "0B", or @a leading-zero) is parsed as by the @c Short::parseShort method with the indicated radix (10, 16, 8 or 2).
        /// This sequence of characters must represent a positive value or a @c NumberFormatException will be thrown.
        /// The result is negated if first character of the specified @c String is the minus sign.  No whitespace characters are permitted in the @c String.
        /// @param nm The @c String to decode.
        /// @return A @c Short object holding the @c gshort value represented by @c nm
        /// @throws NumberFormatException  If the @c String does not contain a parsable @c gshort.
        static Short decode(const String& nm);

        /// Returns the value obtained by reversing the order of the bytes in the two's complement representation of the specified @c short value.
        /// @param value The value whose bytes are to be reversed.
        /// @return The value obtained by reversing (or, equivalently, swapping) the bytes in the specified @c short value.
        static gshort reverseBytes(gshort value);
    };
} // core

#endif // CORE_LANG_SHORT_H
