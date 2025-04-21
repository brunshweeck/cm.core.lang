//
// Created by brunshweeck on 4/20/25.
//

#ifndef CORE_LANG_INTEGER_H
#define CORE_LANG_INTEGER_H

#include "Byte.h"
#include "Comparable.h"
#include "Number.h"

namespace core
{
    /// The @c Integer class wraps a value of the primitive type @c int in an object. An object of type @c Integer contains a single field whose type is @c int.
    /// In addition, this class provides several methods for converting an @c int to a @c String and a @c String to an @c int, as well as other constants and methods useful when dealing with an @c int.
    /// Implementation note: The implementations of the "bit twiddling" methods (such as @b highestOneBit and @b numberOfTrailingZeros) are based on material from Henry S. Warren, Jr.'s <i>Hacker's Delight</i>, (Addison Wesley, 2002).
    class Integer $final : public lang::Comparable<Integer>, public lang::Number
    {
        gint value;

    public:
        /// A constant holding the maximum value a byte can have, 2<sup>31</sup> -1
        static CORE_FAST gint MAX_VALUE = 0x7FFFFFFF;

        /// A constant holding the minimum value a byte can have,  -2<sup>31</sup>
        static CORE_FAST gint MIN_VALUE = (gint)0x80000000;

        /// The number of bits used to represent a @c gint value in two's complement binary form.
        static CORE_FAST gint SIZE = 1 << 5;

        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        /// Constructs a newly allocated @c Integer object that represents the specified @c int argument.
        /// @param  value the value to be represented by the @c Integer object.
        Integer(gint value = 0);

        ~Integer() override = default;

        /// Returns the value of this @c Integer as a @c gbyte after a narrowing primitive conversion.
        /// @return The value of this @c Integer as gbyte.
        gbyte byteValue() const override;

        /// Returns the value of this @c Integer as a @c gshort after a narrowing primitive conversion.
        /// @return The value of this @c Integer as gshort.
        gshort shortValue() const override;

        /// Returns the value of this @c Integer as a @c gint.
        /// @return The value of this @c Integer as gint.
        gint intValue() const override;

        /// Returns the value of this @c Integer as a @c glong after a widening primitive conversion.
        /// @return The value of this @c Integer as glong.
        glong longValue() const override;

        /// Returns the value of this @c Integer as a @c gfloat after a widening primitive conversion.
        /// @return The value of this @c Integer as gfloat.
        gfloat floatValue() const override;

        /// Returns the value of this @c Integer as a @c gdouble after a widening primitive conversion.
        /// @return The value of this @c Integer as gdouble.
        gdouble doubleValue() const override;

        /// Returns a @c String object representing this @c Integer's value.
        /// The value is converted to signed decimal representation and returned as a string, exactly as if the integer value were given as an argument to the @b Integer.toString(int) method.
        /// @return A string representation of the value of this object in base @c 10.
        String toString() const override;

        /// Returns a string representation of the first argument in the radix specified by the second argument.
        /// If the radix is smaller than @c Character.MIN_RADIX or larger than @c Character.MAX_RADIX, then the radix @c 10 is used instead.
        /// If the first argument is negative, the first element of the result is the ASCII minus character @c '-' (@c U+002D). If the first argument is not negative, no sign character appears in the result.
        /// The remaining characters of the result represent the magnitude of the first argument. If the magnitude is zero, it is represented by a single zero character @c '0' (@c U+0030); otherwise, the first character of the representation of the magnitude will not be the zero character.
        /// The following ASCII characters are used as digits: @c 0123456789abcdefghijklmnopqrstuvwxyz .
        /// These are @c U+0030 through @c U+0039 and @c U+0061 through @c U+007A.
        /// If @c radix is <var>N</var>, then the first <var>N</var> of these characters are used as radix-<var>N</var> digits in the order shown.
        /// Thus, the digits for hexadecimal (radix 16) are @c 0123456789abcdef. If uppercase letters are desired, the @b String.toUpperCase() method may be called on the result: @code Integer.toString(n, 16).toUpperCase() @endcode
        /// @param value An integer to be converted to a string.
        /// @param radix The radix to use in the string representation.
        /// @return A string representation of the argument in the specified radix.
        static String toString(gint value, gint radix = 10);

        ///  Returns an @c Integer instance representing the specified @c int value.
        /// @param value An @c int value.
        /// @return An @c Integer instance representing @c value.
        static Integer valueOf(gint value);

        /// Returns an @c Integer object holding the value extracted from the specified @c String when parsed with the radix given by the second argument.
        /// The first argument is interpreted as representing a signed integer in the radix specified by the second argument, exactly as if the arguments were given to the @b parseInt(String, int) method.
        /// The result is an @c Integer object that represents the integer value specified by the string.
        /// In other words, this method returns an @c Integer object equal to the value of: @code Integer(Integer.parseInt(s, radix)) @endcode
        /// @param str The string to be parsed.
        /// @param radix The radix to be used in interpreting @c str
        /// @return A @c Integer object holding the value represented by the string argument in the specified radix.
        /// @throws NumberFormatException If the @c String does not contain a parsable byte.
        static Integer valueOf(const String& str, gint radix = 10);

        /// Parses the string argument as a signed integer in the radix specified by the second argument.
        /// The characters in the string must all be digits of the specified radix (as determined by whether @b Character.digit(char, int) returns a nonnegative value), except that the first character may be an ASCII minus sign @c '-' (@c U+002D) to indicate a negative value or an ASCII plus sign @c '+' (@c U+002B) to indicate a positive value.
        /// The resulting integer value is returned.
        /// An exception of type @c NumberFormatException is thrown if any of the following situations occurs:
        /// - The first argument is @c null or is a string of length zero.
        /// - The radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        /// - Any character of the string is not a digit of the specified radix, except that the first character may be a minus sign @c '-' (@c U+002D) or plus sign @c '+' (@c U+002B) provided that the string is longer than length 1.
        /// - The value represented by the string is not a value of type @c int.
        /// Examples:
        ///     @code
        ///         parseInt("0", 10) returns 0
        ///         parseInt("473", 10) returns 473
        ///         parseInt("+42", 10) returns 42
        ///         parseInt("-0", 10) returns 0
        ///         parseInt("-FF", 16) returns -255
        ///         parseInt("1100110", 2) returns 102
        ///         parseInt("2147483647", 10) returns 2147483647
        ///         parseInt("-2147483648", 10) returns -2147483648
        ///         parseInt("2147483648", 10) throws a NumberFormatException
        ///         parseInt("99", 8) throws a NumberFormatException
        ///         parseInt("Kona", 10) throws a NumberFormatException
        ///         parseInt("Kona", 27) returns 411787
        ///     @endcode
        /// @param str The @c String containing the integer
        /// @param radix The radix to be used while parsing @c str.
        /// @return The integer represented by the string argument in the specified radix.
        /// @exception NumberFormatException if the @c String does not contain a parsable @c int.
        static gint parseInt(const String& str, gint radix = 10);

        /// Parses the string argument as an unsigned integer in the radix specified by the second argument.
        /// An unsigned integer maps the values usually associated with negative numbers to positive numbers larger than @c MAX_VALUE.
        /// The characters in the string must all be digits of the specified radix (as determined by whether @b Character.digit(char, int) returns a nonnegative value), except that the first character may be an ASCII plus sign @c '+' (@c U+002B).
        /// The resulting integer value is returned.
        /// An exception of type @c NumberFormatException is thrown if any of the following situations occurs:
        /// - The first argument is @c null or is a string of length zero.
        /// - The radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        /// - Any character of the string is not a digit of the specified radix, except that the first character may be a plus sign @c '+' (@c U+002B) provided that the string is longer than length 1.
        /// - The value represented by the string is larger than the largest unsigned @c int, 2<sup>32</sup>-1.
        /// @param str A @c String containing the unsigned integer representation to be parsed
        /// @param radix The radix to be used while parsing @c s.
        /// @return The integer represented by the string argument in the specified radix.
        /// @throws NumberFormatException if the @c String does not contain a parsable @c int.
        static gint parseUnsignedInt(const String& str, gint radix = 10);

        /// Parses the @b CharSequence argument as a signed @c int in the specified @c radix, beginning at the specified @c start index and extending to @code end - 1 @endcode.
        /// The method does not take steps to guard against the @c CharSequence being mutated while parsing.
        /// @param csq the @c CharSequence containing the @c int
        /// @param from the beginning index, inclusive.
        /// @param to the ending index, exclusive.
        /// @param radix the radix to be used while parsing @c csq.
        /// @return the signed @c int represented by the subsequence in the specified radix.
        /// @throws IndexOutOfBoundsException  if @c start index is negative, or if @c start index is greater than @c end index or if @c end index is greater than @c csq.length().
        /// @throws NumberFormatException  if the @c CharSequence does not contain a parsable @c int in the specified @c radix, or if @c radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        static glong parseLong(const lang::CharSequence& csq, gint from, gint to, gint radix = 10);

        /// Parses the @b CharSequence argument as an unsigned @c int in the specified @c radix, beginning at the specified @c start index and extending to @code end - 1 @endcode.
        /// The method does not take steps to guard against the @c CharSequence being mutated while parsing.
        /// @param csq the @c CharSequence containing the unsigned
        /// @param from the beginning index, inclusive.
        /// @param to the ending index, exclusive.
        /// @param radix the radix to be used while parsing @c csq.
        /// @return the unsigned @c int represented by the subsequence in the specified radix.
        /// @throws IndexOutOfBoundsException  if @c start index is negative, or if @c start index is greater than @c end index or if @c end index is greater than @c csq.length().
        /// @throws NumberFormatException  if the @c CharSequence does not contain a parsable unsigned @c int in the specified @c radix, or if @c radix is either smaller than @b Character.MIN_RADIX or larger than @b Character.MAX_RADIX.
        static glong parseUnsignedLong(const lang::CharSequence& csq, gint from, gint to, gint radix = 10);

        /// Returns a hash code for this @c Integer.
        /// @return A hash code value for this object, equal to the primitive @c int value represented by this @c Integer object.
        gint hash() const override;

        /// Returns a hash code for an @c int value; compatible with @c Integer.hashCode().
        /// @param value The value to hash
        /// @return A hash code value for an @c int value.
        static gint hash(gint value);

        /// Compares this object to the specified object.
        /// The result is @c true if and only if the argument is not @c null and is an @c Integer object that contains the same @c int value as this object.
        /// @param other The object to compare with
        /// @return The value @c true if the objects are the same; @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Compares two @c Integer objects numerically.
        /// @param other The @c Integer to be compared.
        /// @return The value @c 0 if this @c Integer is equal to the argument @c Integer; a value less than @c 0 if this @c Integer is numerically less than the argument @c Integer; and a value greater than @c 0 if this @c Integer is numerically greater than the argument @c Integer (signed comparison).
        gint compareTo(const Integer& other) const override;

        /// Compares two @c int values numerically.
        /// The value returned is identical to what would be returned by: <pre>Integer.valueOf(x).compareTo(Integer.valueOf(y))</pre>
        /// @param a The first @c int to compare
        /// @param b The second @c int to compare
        /// @return The value @c 0 if @code x == y @endcode; a value less than @c 0 if @code x < y @endcode; and a value greater than @c 0 if @code x > y @endcode .
        static gint compare(gint a, gint b);

        /// Compares two @c int values numerically treating the values as unsigned.
        /// @param a The first @c int to compare
        /// @param b The second @c int to compare
        /// @return The value @c 0 if @code x == y @endcode; a value less than @c 0 if @code x < y @endcode as unsigned values; and a value greater than @c 0 if @code x > y @endcode as unsigned values.
        static gint compareUnsigned(gint a, gint b);

        /// Converts the argument to a @c long by an unsigned conversion.
        /// In an unsigned conversion to a @c long, the high-order 32 bits of the @c long are zero and the low-order 32 bits are equal to the bits of the integer argument.
        /// Consequently, zero and positive @c int values are mapped to a numerically equal @c long value and negative @c int values are mapped to a @c long value equal to the input plus 2<sup>32</sup>.
        /// @param value the value to convert to an unsigned @c long.
        /// @return the argument converted to @c long by an unsigned conversion.
        static glong toUnsignedLong(gint value);

        /// Decodes a @c String into an @c Integer.
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
        /// The sequence of characters following an optional sign and/or radix specifier ( @c "0x",  @c "0X",  @c "0b",  @c "0B",  @c "#", or leading zero) is parsed as by the @c Integer.parseInt method with the indicated radix (10, 16, or 8).
        /// This sequence of characters must represent a positive value or a @b NumberFormatException will be thrown.
        /// The result is negated if first character of the specified @c String is the minus sign.  No whitespace characters are permitted in the @c String.
        /// @param nm the @c String to decode.
        /// @return an @c Integer object holding the @c int value represented by @c nm
        /// @exception NumberFormatException  if the @c String does not contain a parsable integer.
        static String decode(const String& nm);

        /// Returns the unsigned quotient of dividing the first argument by the second where each argument and the result is interpreted as an unsigned value.
        /// Note that in two's complement arithmetic, the three other basic arithmetic operations of add, subtract, and multiply are bit-wise identical if the two operands are regarded as both being signed or both being unsigned.
        /// Therefore separate @c addUnsigned, etc. methods are not provided.
        /// @param dividend the value to be divided.
        /// @param divisor the value doing the dividing
        /// @return the unsigned quotient of the first argument divided by the second argument.
        static gint divideUnsigned(gint dividend, gint divisor);

        /// Returns the unsigned remainder from dividing the first argument by the second where each argument and the result is interpreted as an unsigned value.
        /// @param dividend the value to be divided.
        /// @param divisor the value doing the dividing
        /// @return the unsigned remainder of the first argument divided by the second argument.
        static gint remainderUnsigned(gint dividend, gint divisor);

        /// Returns an @c int value with at most a single one-bit, in the position of the highest-order ("leftmost") one-bit in the specified @c int value.
        /// Returns zero if the specified value has no one-bits in its two's complement binary representation, that is, if it is equal to zero.
        /// @param value the value whose highest one bit is to be computed
        /// @return an @c int value with a single one-bit, in the position of the highest-order one-bit in the specified value, or zero if the specified value is itself equal to zero.
        static gint highestOneBit(gint value);

        /// Returns an @c int value with at most a single one-bit, in the position of the lowest-order ("rightmost") one-bit in the specified @c int value.
        /// Returns zero if the specified value has no one-bits in its two's complement binary representation, that is, if it is equal to zero.
        /// @param value the value whose lowest one bit is to be computed.
        /// @return an @c int value with a single one-bit, in the position of the lowest-order one-bit in the specified value, or zero if the specified value is itself equal to zero.
        static gint lowestOneBit(gint value);

        /// Returns the number of zero bits preceding the highest-order ("leftmost") one-bit in the two's complement binary representation of the specified @c int value.
        /// Returns 32 if the specified value has no one-bits in its two's complement representation, in other words if it is equal to zero.
        /// Note that this method is closely related to the logarithm base 2. or all positive @c int values x:
        /// - floor(log<sub>2</sub>(x)) = @code 31 - numberOfLeadingZeros(x) @endcode
        /// - ceil(log<sub>2</sub>(x)) = @code 32 - numberOfLeadingZeros(x - 1) @endcode
        /// @param value the value whose number of leading zeros is to be computed
        /// @return the number of zero bits preceding the highest-order ("leftmost") one-bit in the two's complement binary representation of the specified @c int value, or 32 if the value is equal to zero.
        static gint numberOfLeadingZeros(gint value);

        /// Returns the number of zero bits following the lowest-order ("rightmost") one-bit in the two's complement binary representation of the specified @c int value.
        /// Returns 32 if the specified value has no one-bits in its two's complement representation, in other words if it is equal to zero.
        /// @param value the value whose number of trailing zeros is to be computed
        /// @return the number of zero bits following the lowest-order ("rightmost") one-bit in the two's complement binary representation of the specified @c int value, or 32 if the value is equal to zero.
        static gint numberOfTrailingZeros(gint value);

        /// Returns the number of one-bits in the two's complement binary representation of the specified @c int value.
        /// This function is sometimes referred to as the <i>population count</i>.
        /// @param value the value whose bits are to be counted
        /// @return the number of one-bits in the two's complement binary representation of the specified @c int value.
        static gint bitCount(gint value);

        /// Returns the value obtained by rotating the two's complement binary representation of the specified @c int value left by the specified number of bits.
        /// (Bits shifted out of the left hand, or high-order, side reenter on the right, or low-order.)
        /// Note that left rotation with a negative distance is equivalent to right rotation: @code rotateLeft(val, -distance) == rotateRight(val, distance) @endcode .
        /// Note also that rotation by any multiple of 32 is a no-op, so all but the last five bits of the rotation distance can be ignored, even if the distance is negative: @code rotateLeft(val, distance) == rotateLeft(val, distance & 0x1F) @endcode .
        /// @param value the value whose bits are to be rotated left
        /// @param distance the number of bit positions to rotate left
        /// @return the value obtained by rotating the two's complement binary representation of the specified @c int value left by the specified number of bits.
        static gint rotateLeft(gint value, gint distance);

        /// Returns the value obtained by rotating the two's complement binary representation of the specified @c int value right by the specified number of bits.
        /// (Bits shifted out of the right hand, or low-order, side reenter on the left, or high-order.)
        /// Note that right rotation with a negative distance is equivalent to left rotation: @code rotateRight(val, -distance) == rotateLeft(val, distance) @endcode .
        /// Note also that rotation by any multiple of 32 is a no-op, so all but the last five bits of the rotation distance can be ignored, even if the distance is negative: @code rotateRight(val, distance) == rotateRight(val, distance & 0x1F) @endcode .
        /// @param value the value whose bits are to be rotated right
        /// @param distance the number of bit positions to rotate right
        /// @return the value obtained by rotating the two's complement binary representation of the specified @c int value right by the specified number of bits.
        static gint rotateRight(gint value, gint distance);

        /// Returns the value obtained by reversing the order of the bits in the two's complement binary representation of the specified @c int value.
        /// @param value the value to be reversed
        /// @return the value obtained by reversing order of the bits in the specified @c int value.
        static gint reverse(gint value);

        /// Returns the value obtained by reversing the order of the bytes in the two's complement representation of the specified @c int value.
        /// @param value the value whose bytes are to be reversed
        /// @return the value obtained by reversing the bytes in the specified @c int value.
        static gint reverseBytes(gint value);

        /// Returns the signum function of the specified @c int value.
        /// (The return value is -1 if the specified value is negative; 0 if the specified value is zero; and 1 if the specified value is positive.)
        /// @param value the value whose signum is to be computed
        /// @return the signum function of the specified @c int value.
        static gint signum(gint value);

        /// Adds two integers together as per the + operator.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        static gint sum(gint a, gint b);

        /// Returns the greater of two @c int values as if by calling @b Math.max.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the greater of @c a and @c b
        static gint max(gint a, gint b);

        /// Returns the smaller of two @c int values as if by calling @b Math.min.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the smaller of @c a and @c b
        static gint min(gint a, gint b);

        CORE_INTRINSIC_ACCESS_DECL(gint)
    };
} // core

#endif // CORE_LANG_INTEGER_H
