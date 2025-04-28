//
// Created by brunshweeck on 4/19/25.
//

#ifndef CORE_LANG_BYTE_H
#define CORE_LANG_BYTE_H
#include "Comparable.h"
#include "Number.h"

namespace core
{
    class Byte $final : public lang::Comparable<Byte>, public lang::Number
    {
        /// The value of the @c Byte.
        gbyte value;

    public:
        /// A constant holding the maximum value a byte can have, 2<sup>7</sup> -1
        static CORE_FAST gbyte MAX_VALUE = 0x7F;

        /// A constant holding the minimum value a byte can have,  -2<sup>7</sup>
        static CORE_FAST gbyte MIN_VALUE = 0x80;

        /// The number of bits used to represent a @c gbyte value in two's complement binary form.
        static CORE_FAST gint SIZE = 1 << 3;

        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        Byte(gbyte value = 0);

        ~Byte() override = default;

        /// Returns the value of this @c Byte as a @c gbyte.
        /// @return The value of this @c Byte as gbyte.
        gbyte byteValue() const override;

        /// Returns the value of this @c Byte as a @c gshort after a widening primitive conversion.
        /// @return The value of this @c Byte as gshort.
        gshort shortValue() const override;

        /// Returns the value of this @c Byte as a @c gint after a widening primitive conversion.
        /// @return The value of this @c Byte as gint.
        gint intValue() const override;

        /// Returns the value of this @c Byte as a @c glong after a widening primitive conversion.
        /// @return The value of this @c Byte as glong.
        glong longValue() const override;

        /// Returns the value of this @c Byte as a @c gfloat after a widening primitive conversion.
        /// @return The value of this @c Byte as gfloat.
        gfloat floatValue() const override;

        /// Returns the value of this @c Byte as a @c gdouble after a widening primitive conversion.
        /// @return The value of this @c Byte as gdouble.
        gdouble doubleValue() const override;

        /// Returns a @c String object representing this @c Byte 's value.
        /// The value is converted to signed decimal representation and returned as a string, exactly as if the @c gbyte value were given as an argument to the @c Byte::toString(gbyte) method.
        /// @return A string representation of the value of this object in base @c 10.
        String toString() const override;

        /// Returns a new @c String object representing the specified @c gbyte. The radix is assumed to be 10.
        /// @param value The byte to be converted.
        /// @return The string representation of the specified byte.
        static String toString(gbyte value);

        ///  Returns a @c Byte instance representing the specified byte value.
        /// @param value A byte value.
        /// @return A @c Byte instance representing @c value.
        static Byte valueOf(gbyte value);

        /// Returns a @c Byte object holding the value extracted from the specified @c String when parsed with the radix given by the second argument.
        /// The first argument is interpreted as representing a signed @c gbyte in the radix specified by the second argument, exactly as if the argument were given to the @c parseByte(String,gint) method.
        /// The result is a @c Byte object that represents the @c gbyte value specified by the string.
        /// In other words, this method returns a @c Byte object equal to the value of: @c Byte::valueOf(Byte::parseByte(s,radix))
        /// @param str The string to be parsed.
        /// @param radix The radix to be used in interpreting string
        /// @return A @c Byte object holding the value represented by the string argument in the specified radix.
        /// @throws NumberFormatException If the @c String does not contain a parsable byte.
        static Byte valueOf(const String& str, gint radix = 10);

        /// Parses the string argument as a signed byte in the radix specified by the second argument.
        /// The characters in the string must all be digits, of the specified radix (as etermined by whether @code Character::digit(gchar, gint) @endcode returns a non-negative value) except that the first character may be an ASCII minus sign @c '-' (U+002D) to indicate a negative value or an ASCII plus sign @c '+' (U+002B) to indicate a positive value.
        /// The resulting byte value is returned.
        /// An exception of type @c NumberFormatException is thrown if any of the following situations occurs:
        /// - The first argument is a string of length zero;
        /// - The radix is either smaller than @c Character::MIN_RADIX or larger than @c Character::MAX_RADIX;
        /// - Any character of the string is not a digit of the pecified radix, except that the first character may be a minus sign @c '-' (U+002D) or plus sign @c '+' (U+002B) provided that the string is longer than length @c 1;
        /// - The value represented by the string is not a value of type @c gbyte.
        /// @param str The @c String containing the byte representation to be parsed
        /// @param radix The radix to be used while parsing string.
        /// @return The byte value represented by the string argument in the specified radix.
        /// @throws NumberFormatException If the string does not contain a parsable @c gbyte.
        static gbyte parseByte(const String& str, gint radix = 10);

        /// Returns a hash code for this @c Byte; equal to the result of invoking @c intValue().
        /// @return A hash code value for this @c Byte.
        gint hash() const override;

        /// Returns a hash code for a @c gbyte value; compatible with @c Byte::hash().
        /// @param value The value to hash
        /// @return A hash code value for a @c gbyte value.
        static gint hash(gbyte value);

        /// Compares this object to the specified object.
        /// The result is @c true if and only if the argument is a @c Byte object that contains the same @c gbyte value as this object.
        /// @param other The object to compare with
        /// @return The value @c true if the objects are the same; @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Compares two @c Byte objects numerically.
        /// @param other The @c Byte to be compared.
        /// @return The value @c 0 if this @c Byte is equal to the argument @c Byte;
        ///                 a value less than @c 0 if this @c Byte is numerically less than the argument @c Byte;
        ///                 and a value greater than @c 0 if this @c Byte is numerically greater than the argument @c Byte (signed comparison).
        gint compareTo(const Byte& other) const override;

        /// Compares two @c gbyte values numerically.
        /// The value returned is identical to what would be returned by @code Byte::valueOf(a).compareTo(Byte::valueOf(b)) @endcode
        /// @param a The first @c gbyte to compare.
        /// @param b The second @c gbyte to compare.
        /// @return The value @c 0 if @code a == b @endcode ; a value less than @c 0 if @code a < b @endcode ; and a value greater than @c 0 if @code a > b @endcode .
        static gint compare(gbyte a, gbyte b);

        /// Compares two @c gbyte values numerically treating the values as unsigned.
        /// @param a The first @c gbyte to compare.
        /// @param b The second @c gbyte to compare.
        /// @return The value @c 0 if @code a == b @endcode ; a value less than @c 0 if @code a< b @endcode as unsigned values; and a value greater than @c 0 if @code a > b @endcode as unsigned values.
        static gint compareUnsigned(gbyte a, gbyte b);

        /// Converts the argument to a @c gint by an unsigned conversion.
        /// In an unsigned conversion to an @c gint, the high-order 24 bits of the @c gint are zero and the low-order 8 bits are equal to the bits of the @c gbyte argument.
        /// Consequently, zero and positive @c gbyte values are mapped to a numerically equal @c gint value and negative @c gbyte values are mapped to an @c gint value equal to the input plus 2<sup>8</sup>.
        /// @param value The value to convert to an unsigned @c gint.
        /// @return The argument converted to @c gint by an unsigned conversion.
        static gint toUnsignedInt(gbyte value);

        /// Converts the argument to a @c glong by an unsigned conversion.
        /// In an unsigned conversion to a @c glong, the high-order 56 bits of the @c glong are zero and the low-order 8 bits are equal to the bits of the @c gbyte argument.
        /// Consequently, zero and positive @c gbyte values are mapped to a numerically equal @c glong value and negative @c byte values are mapped to a @c glong value equal to the input plus 2<sup>8</sup>.
        /// @param value The value to convert to an unsigned @c glong.
        /// @return The argument converted to @c glong by an unsigned conversion.
        static glong toUnsignedLong(gbyte value);

        /// Decodes a @c String into a @c Byte.
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
        /// The sequence of characters following an optional sign and/or radix specifier ( @c "0x", @c "0X", @c "#", @c "0b", @c "0B", or @a leading-zero) is parsed as by the @c Byte::parseByte method with the indicated radix (10, 16, 8 or 2).
        /// This sequence of characters must represent a positive value or a @c NumberFormatException will be thrown.
        /// The result is negated if first character of the specified @c String is the minus sign.  No whitespace characters are permitted in the @c String.
        /// @param nm The @c String to decode.
        /// @return A @c Byte object holding the @c gbyte value represented by @c nm
        /// @throws NumberFormatException  If the @c String does not contain a parsable @c gbyte.
        static Byte decode(const String& nm);

        CORE_INTRINSIC_ACCESS_DECL(gbyte)

        Byte& clone() const override;
    };
} // core

#endif // CORE_LANG_BYTE_H
