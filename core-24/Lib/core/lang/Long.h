//
// Created by brunshweeck on 4/20/25.
//

#ifndef CORE_LANG_LONG_H
#define CORE_LANG_LONG_H

#include "Byte.h"
#include "Comparable.h"
#include "Number.h"

namespace core
{
    /// The @c Long class wraps a value of the primitive type @c long in an object.
    /// An object of type @c Long contains a single field whose type is @c long.
    /// In addition, this class provides several methods for converting a @c long to a @c String and a @c String to a @c long, as well as other constants and methods useful when dealing with a @c long.
    /// Implementation note: The implementations of the "bit twiddling" methods (such as @b highestOneBit and @b numberOfTrailingZeros) are based on material from Henry S. Warren, Jr.'s <i>Hacker's Delight</i>, (Addison Wesley, 2002).
    class Long $final : public lang::Comparable<Long>, public lang::Number
    {
        glong value;

    public:
        /// A constant holding the maximum value a byte can have, 2<sup>63</sup> -1
        static CORE_FAST glong MAX_VALUE = 0x7FFFFFFFFFFFFFFFL;

        /// A constant holding the minimum value a byte can have,  -2<sup>63</sup>
        static CORE_FAST glong MIN_VALUE = (glong)0x8000000000000000L;

        /// The number of bits used to represent a @c glong value in two's complement binary form.
        static CORE_FAST gint SIZE = 1 << 6;

        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        /// Constructs a newly allocated @c Long object that represents the specified @c long argument.
        /// @param  value the value to be represented by the @c Long object.
        Long(glong value = 0L);

        ~Long() override = default;

        /// Returns the value of this @c Long as a @c gbyte after a narrowing primitive conversion.
        /// @return The value of this @c Long as gbyte.
        gbyte byteValue() const override;

        /// Returns the value of this @c Long as a @c gshort after a narrowing primitive conversion.
        /// @return The value of this @c Long as gshort.
        gshort shortValue() const override;

        /// Returns the value of this @c Long as a @c gint after a narrowing primitive conversion.
        /// @return The value of this @c Long as gint.
        gint intValue() const override;

        /// Returns the value of this @c Long as a @c glong.
        /// @return The value of this @c Long as glong.
        glong longValue() const override;

        /// Returns the value of this @c Long as a @c gfloat after a widening primitive conversion.
        /// @return The value of this @c Long as gfloat.
        gfloat floatValue() const override;

        /// Returns the value of this @c Long as a @c gdouble after a widening primitive conversion.
        /// @return The value of this @c Long as gdouble.
        gdouble doubleValue() const override;

        /// Returns a @c String object representing this @c Long's value.
        /// The value is converted to signed decimal representation and returned as a string, exactly as if the @c long value were given as an argument to the @b Long.toString(long) method.
        /// @return A string representation of the value of this object in base @c 10.
        String toString() const override;

        /// Returns a string representation of the first argument in the radix specified by the second argument.
        /// If the radix is smaller than @c Character.MIN_RADIX or larger than @c Character.MAX_RADIX, then the radix @c 10 is used instead.
        /// If the first argument is negative, the first element of the result is the ASCII minus character @c '-' (@c U+002D). If the first argument is not negative, no sign character appears in the result.
        /// The remaining characters of the result represent the magnitude of the first argument. If the magnitude is zero, it is represented by a single zero character @c '0' (@c U+0030); otherwise, the first character of the representation of the magnitude will not be the zero character.
        /// The following ASCII characters are used as digits: @c 0123456789abcdefghijklmnopqrstuvwxyz .
        /// These are @c U+0030 through @c U+0039 and @c U+0061 through @c U+007A.
        /// If @c radix is <var>N</var>, then the first <var>N</var> of these characters are used as radix-<var>N</var> digits in the order shown.
        /// Thus, the digits for hexadecimal (radix 16) are @c 0123456789abcdef. If uppercase letters are desired, the @b String.toUpperCase() method may be called on the result: @code Long.toString(n, 16).toUpperCase() @endcode
        /// @param value a @c long to be converted to a string.
        /// @param radix The radix to use in the string representation.
        /// @return A string representation of the argument in the specified radix.
        static String toString(glong value, gint radix = 10);

        ///  Returns an @c Long instance representing the specified @c long value.
        /// @param value An @c long value.
        /// @return An @c Long instance representing @c value.
        static Long valueOf(glong value);

        /// Returns an @c Long object holding the value extracted from the specified @c String when parsed with the radix given by the second argument.
        /// The first argument is interpreted as representing a signed @c long in the radix specified by the second argument, exactly as if the arguments were given to the @b parseLong(String, long) method.
        /// The result is an @c Long object that represents the @c long value specified by the string.
        /// In other words, this method returns an @c Long object equal to the value of: @code Long(Long.parseLong(s, radix)) @endcode
        /// @param str The string to be parsed.
        /// @param radix The radix to be used in interpreting @c str
        /// @return A @c Long object holding the value represented by the string argument in the specified radix.
        /// @throws NumberFormatException If the @c String does not contain a parsable byte.
        static Long valueOf(const String& str, gint radix = 10);

        /// Parses the string argument as a signed @c long in the radix specified by the second argument.
        /// The characters in the string must all be digits of the specified radix (as determined by whether @b Character.digit(char, int) returns a nonnegative value), except that the first character may be an ASCII minus sign @c '-' (@c U+002D) to indicate a negative value or an ASCII plus sign @c '+' (@c U+002B) to indicate a positive value.
        /// The resulting @c long value is returned.
        /// Note that neither the character @c L (@c U+004C) nor @c l (@c U+006C) is permitted to appear at the end of the string as a type indicator, as would be permitted in C++ programming language source code - except that either @c L or @c l may appear as a digit for a radix greater than or equal to 22.
        /// An exception of type @c NumberFormatException is thrown if any of the following situations occurs:
        /// - The first argument is @c null or is a string of length zero.
        /// - The radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        /// - Any character of the string is not a digit of the specified radix, except that the first character may be a minus sign @c '-' (@c U+002D) or plus sign @c '+' (@c U+002B) provided that the string is longer than length 1.
        /// - The value represented by the string is not a value of type @c long.
        /// Examples:
        ///     @code
        ///         parseLong("0", 10) returns 0L
        ///         parseLong("473", 10) returns 473L
        ///         parseLong("+42", 10) returns 42L
        ///         parseLong("-0", 10) returns 0L
        ///         parseLong("-FF", 16) returns -255L
        ///         parseLong("1100110", 2) returns 102L
        ///         parseLong("99", 8) throws a NumberFormatException
        ///         parseLong("Hazelnut", 10) throws a NumberFormatException
        ///         parseLong("Hazelnut", 36) returns 1356099454469L
        ///     @endcode
        /// @param str The @c String containing the @c long representation to be parsed.
        /// @param radix The radix to be used while parsing @c str.
        /// @return The @c long represented by the string argument in the specified radix.
        /// @exception NumberFormatException if the @c String does not contain a parsable @c long.
        static gint parseLong(const String& str, gint radix = 10);

        /// Parses the string argument as an unsigned @c long in the radix specified by the second argument.
        /// An unsigned @c long maps the values usually associated with negative numbers to positive numbers larger than @c MAX_VALUE.
        /// The characters in the string must all be digits of the specified radix (as determined by whether @b Character.digit(char, int) returns a nonnegative value), except that the first character may be an ASCII plus sign @c '+' (@c U+002B).
        /// The resulting @c long value is returned.
        /// An exception of type @c NumberFormatException is thrown if any of the following situations occurs:
        /// - The first argument is @c null or is a string of length zero.
        /// - The radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        /// - Any character of the string is not a digit of the specified radix, except that the first character may be a plus sign @c '+' (@c U+002B) provided that the string is longer than length 1.
        /// - The value represented by the string is larger than the largest unsigned @c long, 2<sup>64</sup>-1.
        /// @param str A @c String containing the unsigned @c long representation to be parsed
        /// @param radix The radix to be used while parsing @c s.
        /// @return The @c long represented by the string argument in the specified radix.
        /// @throws NumberFormatException if the @c String does not contain a parsable @c long.
        static gint parseUnsignedLong(const String& str, gint radix = 10);

        /// Parses the @b CharSequence argument as a signed @c long in the specified @c radix, beginning at the specified @c start index and extending to @code end - 1 @endcode .
        /// The method does not take steps to guard against the @c CharSequence being mutated while parsing.
        /// @param csq the @c CharSequence containing the @c long
        /// @param from the beginning index, inclusive.
        /// @param to the ending index, exclusive.
        /// @param radix the radix to be used while parsing @c csq.
        /// @return the signed @c long represented by the subsequence in the specified radix.
        /// @throws IndexOutOfBoundsException  if @c start index is negative, or if @c start index is greater than @c end index or if @c end index is greater than @code csq.length() @endcode .
        /// @throws NumberFormatException  if the @c CharSequence does not contain a parsable @c long in the specified @c radix, or if @c radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        static glong parseLong(const lang::CharSequence& csq, gint from, gint to, gint radix = 10);

        /// Parses the @b CharSequence argument as an unsigned @c long in the specified @c radix, beginning at the specified @c start index and extending to @code end - 1 @endcode .
        /// The method does not take steps to guard against the @c CharSequence being mutated while parsing.
        /// @param csq the @c CharSequence containing the unsigned
        /// @param from the beginning index, inclusive.
        /// @param to the ending index, exclusive.
        /// @param radix the radix to be used while parsing @c csq.
        /// @return the unsigned @c long represented by the subsequence in the specified radix.
        /// @throws IndexOutOfBoundsException  if @c start index is negative, or if @c start index is greater than @c end index or if @c end index is greater than @code csq.length() @endcode .
        /// @throws NumberFormatException  if the @c CharSequence does not contain a parsable unsigned @c long in the specified @c radix, or if @c radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        static glong parseUnsignedLong(const lang::CharSequence& csq, gint from, gint to, gint radix = 10);

        /// Returns a hash code for this @c Long.
        /// @return A hash code value for this object, equal to the primitive @c long value represented by this @c Long object.
        gint hash() const override;

        /// Returns a hash code for an @c long value; compatible with @c Long.hash().
        /// @param value The value to hash
        /// @return A hash code value for an @c long value.
        static gint hash(glong value);

        /// Compares this object to the specified object.
        /// The result is @c true if and only if the argument is not @c null and is an @c Long object that contains the same @c long value as this object.
        /// @param other The object to compare with
        /// @return The value @c true if the objects are the same; @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Compares two @c Long objects numerically.
        /// @param other The @c Long to be compared.
        /// @return The value @c 0 if this @c Long is equal to the argument @c Long; a value less than @c 0 if this @c Long is numerically less than the argument @c Long; and a value greater than @c 0 if this @c Long is numerically greater than the argument @c Long (signed comparison).
        gint compareTo(const Long& other) const override;

        /// Compares two @c long values numerically.
        /// The value returned is identical to what would be returned by: <pre>Long.valueOf(x).compareTo(Long.valueOf(y))</pre>
        /// @param a The first @c long to compare
        /// @param b The second @c long to compare
        /// @return The value @c 0 if @code x == y @endcode ; a value less than @c 0 if @code x < y @endcode ; and a value greater than @c 0 if @code x > y @endcode .
        static gint compare(glong a, glong b);

        /// Compares two @c long values numerically treating the values as unsigned.
        /// @param a The first @c long to compare
        /// @param b The second @c long to compare
        /// @return The value @c 0 if @code x == y @endcode ; a value less than @c 0 if @code x < y @endcode  as unsigned values; and a value greater than @c 0 if @code x > y @endcode as unsigned values.
        static gint compareUnsigned(glong a, glong b);

        /// Decodes a @c String into an @c Long.
        /// Accepts decimal, hexadecimal, and octal numbers given by the following grammar:
        /// -<b>Decodable String:</b>
        /// - @em Sign <sub>opt</sub> @em DecimalNumeral ;
        /// - @em Sign <sub>opt</sub> @c 0x @em HexDigits ;
        /// - @em Sign <sub>opt</sub> @c 0X @em HexDigits ;
        /// - @em Sign <sub>opt</sub> @c # @em HexDigits ;
        /// - @em Sign <sub>opt</sub> @c 0 @em OctalDigits ;
        /// - @em Sign <sub>opt</sub> @c 0b @em BinaryDigits ;
        /// - @em Sign <sub>opt</sub> @c 0b @em BinaryDigits ;
        /// - @b Sign:
        /// - @c - (U+002D) ;
        /// - @c + (U+002B) .
        ///
        /// <i>DecimalNumeral</i>, <i>HexDigits</i>, <i>OctalDigits</i>, and <i>BinaryDigits</i> are as defined in C++ language feature.
        /// The sequence of characters following an optional sign and/or radix specifier (@c "0x", @c "0X", @c "0b", @c "0B", @c "#", or leading zero) is parsed as by the @c Long.parseLong method with the indicated radix (10, 16, 8, or 2).
        /// This sequence of characters must represent a positive value or a @b NumberFormatException will be thrown.
        /// The result is negated if first character of the specified @c String is the minus sign.  No whitespace characters are permitted in the @c String.
        /// @param nm the @c String to decode.
        /// @return an @c Long object holding the @c long value represented by @c nm
        /// @exception NumberFormatException  if the @c String does not contain a parsable @c long.
        static String decode(const String& nm);

        /// Returns the unsigned quotient of dividing the first argument by the second where each argument and the result is interpreted as an unsigned value.
        /// Note that in two's complement arithmetic, the three other basic arithmetic operations of add, subtract, and multiply are bit-wise identical if the two operands are regarded as both being signed or both being unsigned.
        /// Therefore separate @c addUnsigned, etc. methods are not provided.
        /// @param dividend the value to be divided.
        /// @param divisor the value doing the dividing
        /// @return the unsigned quotient of the first argument divided by the second argument.
        static glong divideUnsigned(glong dividend, glong divisor);

        /// Returns the unsigned remainder from dividing the first argument by the second where each argument and the result is interpreted as an unsigned value.
        /// @param dividend the value to be divided.
        /// @param divisor the value doing the dividing
        /// @return the unsigned remainder of the first argument divided by the second argument.
        static glong remainderUnsigned(glong dividend, glong divisor);

        /// Returns an @c long value with at most a single one-bit, in the position of the highest-order ("leftmost") one-bit in the specified @c long value.
        /// Returns zero if the specified value has no one-bits in its two's complement binary representation, that is, if it is equal to zero.
        /// @param value the value whose highest one bit is to be computed
        /// @return an @c long value with a single one-bit, in the position of the highest-order one-bit in the specified value, or zero if the specified value is itself equal to zero.
        static glong highestOneBit(glong value);

        /// Returns an @c long value with at most a single one-bit, in the position of the lowest-order ("rightmost") one-bit in the specified @c long value.
        /// Returns zero if the specified value has no one-bits in its two's complement binary representation, that is, if it is equal to zero.
        /// @param value the value whose lowest one bit is to be computed.
        /// @return an @c long value with a single one-bit, in the position of the lowest-order one-bit in the specified value, or zero if the specified value is itself equal to zero.
        static glong lowestOneBit(glong value);

        /// Returns the number of zero bits preceding the highest-order ("leftmost") one-bit in the two's complement binary representation of the specified @c long value.
        /// Returns 64 if the specified value has no one-bits in its two's complement representation, in other words if it is equal to zero.
        /// Note that this method is closely related to the logarithm base 2. or all positive @c long values x:
        /// - floor(log<sub>2</sub>(x)) = @code 63 - numberOfLeadingZeros(x) @endcode
        /// - ceil(log<sub>2</sub>(x)) = @code 64 - numberOfLeadingZeros(x - 1) @endcode
        /// @param value the value whose number of leading zeros is to be computed
        /// @return the number of zero bits preceding the highest-order ("leftmost") one-bit in the two's complement binary representation of the specified @c long value, or 64 if the value is equal to zero.
        static gint numberOfLeadingZeros(glong value);

        /// Returns the number of zero bits following the lowest-order ("rightmost") one-bit in the two's complement binary representation of the specified @c long value.
        /// Returns 64 if the specified value has no one-bits in its two's complement representation, in other words if it is equal to zero.
        /// @param value the value whose number of trailing zeros is to be computed
        /// @return the number of zero bits following the lowest-order ("rightmost") one-bit in the two's complement binary representation of the specified @c long value, or 64 if the value is equal to zero.
        static gint numberOfTrailingZeros(glong value);

        /// Returns the number of one-bits in the two's complement binary representation of the specified @c long value.
        /// This function is sometimes referred to as the <i>population count</i>.
        /// @param value the value whose bits are to be counted
        /// @return the number of one-bits in the two's complement binary representation of the specified @c long value.
        static gint bitCount(glong value);

        /// Returns the value obtained by rotating the two's complement binary representation of the specified @c long value left by the specified number of bits.
        /// (Bits shifted out of the left hand, or high-order, side reenter on the right, or low-order.)
        /// Note that left rotation with a negative distance is equivalent to right rotation: @code rotateLeft(val, -distance) == rotateRight(val, distance) @endcode .
        /// Note also that rotation by any multiple of 64 is a no-op, so all but the last five bits of the rotation distance can be ignored, even if the distance is negative: @code rotateLeft(val, distance) == rotateLeft(val, distance & 0x1F) @endcode .
        /// @param value the value whose bits are to be rotated left
        /// @param distance the number of bit positions to rotate left
        /// @return the value obtained by rotating the two's complement binary representation of the specified @c long value left by the specified number of bits.
        static glong rotateLeft(glong value, gint distance);

        /// Returns the value obtained by rotating the two's complement binary representation of the specified @c long value right by the specified number of bits.
        /// (Bits shifted out of the right hand, or low-order, side reenter on the left, or high-order.)
        /// Note that right rotation with a negative distance is equivalent to left rotation: @code rotateRight(val, -distance) == rotateLeft(val, distance) @endcode .
        /// Note also that rotation by any multiple of 64 is a no-op, so all but the last five bits of the rotation distance can be ignored, even if the distance is negative: @code rotateRight(val, distance) == rotateRight(val, distance & 0x1F) @endcode .
        /// @param value the value whose bits are to be rotated right
        /// @param distance the number of bit positions to rotate right
        /// @return the value obtained by rotating the two's complement binary representation of the specified @c long value right by the specified number of bits.
        static glong rotateRight(glong value, gint distance);

        /// Returns the value obtained by reversing the order of the bits in the two's complement binary representation of the specified @c long value.
        /// @param value the value to be reversed
        /// @return the value obtained by reversing order of the bits in the specified @c long value.
        static glong reverse(glong value);

        /// Returns the value obtained by reversing the order of the bytes in the two's complement representation of the specified @c long value.
        /// @param value the value whose bytes are to be reversed
        /// @return the value obtained by reversing the bytes in the specified @c long value.
        static glong reverseBytes(glong value);

        /// Returns the signum function of the specified @c long value.
        /// (The return value is -1 if the specified value is negative; 0 if the specified value is zero; and 1 if the specified value is positive.)
        /// @param value the value whose signum is to be computed
        /// @return the signum function of the specified @c long value.
        static gint signum(glong value);

        /// Adds two integers together as per the + operator.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        static gint sum(glong a, glong b);

        /// Returns the greater of two @c long values as if by calling @b Math.max.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the greater of @c a and @c b
        static gint max(glong a, glong b);

        /// Returns the smaller of two @c long values as if by calling @b Math.min.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the smaller of @c a and @c b
        static gint min(glong a, glong b);

        CORE_INTRINSIC_ACCESS_DECL(glong)
    };
} // core

#endif // CORE_LANG_LONG_H
