//
// Created by brunshweeck on 4/21/25.
//

#ifndef CORE_LANG_DOUBLE_H
#define CORE_LANG_DOUBLE_H

#include "Byte.h"
#include "Comparable.h"
#include "Number.h"

namespace core
{
    /// The @c Double class wraps a value of the primitive type @c double in an object.
    /// An object of type @c Double contains a single field whose type is @c double.
    /// In addition, this class provides several methods for converting a @c double to a @c String and a @c String to a @c double, as well as other constants and methods useful when dealing with a @c double.
    class Double $final : public lang::Comparable<Double>, public lang::Number
    {
        /// The value of the Double.
        gdouble value;

    public:
        /// A constant holding the largest positive finite value of type @c double, (2-2<sup>-52</sup>)·2<sup>1023</sup>.
        /// It is equal to the hexadecimal floating-point literal @c 0x1.fffffffffffffP+1023 and also equal to @c Double.fromLongBits(0x7fefffffffffffffL).
        static CORE_FAST gdouble MAX_VALUE = 0x1.FFFFFFFFFFFFFp+1023; // 1.7976931348623157e+308

        /// A constant holding the smallest positive normal value of type @c double, 2<sup>-1022</sup>.
        /// It is equal to the hexadecimal floating-point literal @c 0x1.0p-1022 and also equal to @c Double.fromLongBits(0x0010000000000000L).
        static CORE_FAST gdouble MIN_NORMAL = 0x1.0000000000000p-1022; // 2.2250738585072014E-308

        /// A constant holding the smallest positive normal value of type @c double, 2<sup>-1022</sup>.
        /// It is equal to the hexadecimal floating-point literal @c 0x1.0p-1022 and also equal to @c Double.fromLongBits(0x0010000000000000L).
        static CORE_FAST gdouble MIN_VALUE = 0x0.0000000000001p-1022; // 4.9e-324

        /// A constant holding the positive infinity of type @c double.
        /// It is equal to the value returned by @c Double.fromLongBits(0x7ff0000000000000L).
        static CORE_FAST gdouble INF = __builtin_infinity();

        /// A constant holding a Not-a-Number (NaN) value of type @c double.
        /// It is equivalent to the value returned by @c Double.fromLongBits(0x7ff8000000000000L).
        static CORE_FAST gdouble NaN = __builtin_nan();

        /// Maximum exponent a finite @c double variable may have.
        /// It is equal to the value returned by @c Math.getExponent(Double.MAX_VALUE).
        static CORE_FAST gint MAX_EXPONENT = 1023;

        /// Minimum exponent a normalized @c double variable may have.
        /// It is equal to the value returned by @c Math.getExponent(Double.MIN_NORMAL).
        static CORE_FAST gint MIN_EXPONENT = -1022;

        /// The number of bits used to represent a @c double value.
        static CORE_FAST gint SIZE = 1 << 6;

        /// The number of bytes used to represent a @c double value.
        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        /// Constructs a newly allocated @c Double object that represents the primitive @c double argument.
        /// @param value the value to be represented by the @c Double.
        Double(gdouble value = .0);

        ~Double() override = default;

        /// Returns the value of this @c Double as a @c byte after a narrowing primitive conversion.
        /// @return the @c double value represented by this object converted to type @c byte
        gbyte byteValue() const override;

        /// Returns the value of this @c Double as a @c short after a narrowing primitive conversion.
        /// @return the @c double value represented by this object converted to type @c short
        gshort shortValue() const override;

        /// Returns the value of this @c Double as an @c int after a narrowing primitive conversion.
        /// @return the @c double value represented by this object converted to type @c int
        gint intValue() const override;

        /// Returns the value of this @c Double as a @c long after a narrowing primitive conversion.
        /// @return the @c double value represented by this object converted to type @c long
        glong longValue() const override;

        /// Returns the value of this @c Double as a @c float after a narrowing primitive conversion.
        /// @return the @c double value represented by this object converted to type @c float
        gfloat floatValue() const override;

        /// Returns the @c double value of this @c Double object.
        /// @return the @c double value represented by this object
        gdouble doubleValue() const override;

        /// Returns a string representation of this @c Double object.
        /// The primitive @c double value represented by this object is converted to a string exactly as if by the method @c toString of one argument.
        /// @return a @c String representation of this object.
        /// @see core.lang::Double.toString(double)
        String toString() const override;

        /// Returns a string representation of the @c double argument.
        /// All characters mentioned below are ASCII characters.
        /// - If the argument is NaN, the result is the string "@c NaN".
        /// - Otherwise, the result is a string that represents the sign and magnitude (absolute value) of the argument. If the sign is negative, the first character of the result is @c '-' (U+002D); if the sign is positive, no sign character appears in the result.
        ///    As for the magnitude <i>m</i>:
        ///    - If <i>m</i> is an infinity, it is represented by the characters @c "infinity"; thus, positive infinity produces the result @c "infinity" and negative infinity produces the result @c "-infinity".
        ///    - If <i>m</i> is zero, it is represented by the characters @c "0.0"; thus, negative zero produces the result @c "-0.0" and positive zero produces the result @c "0.0".
        ///    - If <i>m</i> is greater than or equal to 10<sup>-3</sup> but less than 10<sup>7</sup>, then it is represented as the integer part of <i>m</i>, in decimal form with no leading zeroes, followed by @c '.' (U+002E), followed by one or more decimal digits representing the fractional part of <i>m</i>.
        ///    - If <i>m</i> is less than 10<sup>-3</sup> or greater than or equal to 10<sup>7</sup>, then it is represented in so-called "computerized scientific notation." Let <i>n</i> be the unique integer such that 10<sup><i>n</i></sup> &le; <i>m</i> < 10<sup><i>n</i>+1</sup>; then let <i>a</i> be the mathematically exact quotient of <i>m</i> and 10<sup><i>n</i></sup> so that 1 &le; <i>a</i> < 10.
        ///       The magnitude is then represented as the integer part of <i>a</i>, as a single decimal digit, followed by @c '.' (U+002E), followed by decimal digits representing the fractional part of <i>a</i>, followed by the letter @c 'E' (U+0045), followed by a representation of <i>n</i> as a decimal integer, as produced by the method @b Integer::toString(int).
        ///
        /// How many digits must be printed for the fractional part of <i>m</i> or <i>a</i>?
        /// There must be at least one digit to represent the fractional part, and beyond that as many, but only as many, more digits as are needed to uniquely distinguish the argument value from adjacent values of type @c double.
        /// That is, suppose that <i>x</i> is the exact mathematical value represented by the decimal representation produced by this method for a finite nonzero argument <i>d</i>.
        /// Then <i>d</i> must be the @c double value nearest to <i>x</i>; or if two @c double values are equally close to <i>x</i>, then <i>d</i> must be one of them and the least significant bit of the significand of <i>d</i> must be @c 0.
        /// To create localized string representations of a floating-point value, use subclasses of @b core.text::NumberFormat.
        /// @param value the @c double to be converted.
        /// @return a string representation of the argument.
        static String toString(gdouble value);

        /// Returns a hexadecimal string representation of the @c double argument.
        /// All characters mentioned below are ASCII characters.
        /// - If the argument is NaN, the result is the string "@c NaN".
        /// - Otherwise, the result is a string that represents the sign and magnitude (absolute value) of the argument.
        ///    If the sign is negative, the first character of the result is @c '-' (U+002D); if the sign is positive, no sign character appears in the result.
        ///    As for the magnitude <i>m</i>:
        ///     - If <i>m</i> is an infinity, it is represented by the string @c "infinity"; thus, positive infinity produces the result @c "infinity" and negative infinity produces the result @c "-infinity".
        ///     - If <i>m</i> is zero, it is represented by the string @c "0x0.0p0"; thus, negative zero produces the result @c "-0x0.0p0" and positive zero produces the result @c "0x0.0p0".
        ///     - If <i>m</i> is a @c double value with a normalized representation, substrings are used to represent the significand and exponent fields.  The significand is represented by the characters @c "0x1." Followed by a lowercase hexadecimal representation of the rest of the significand as a fraction.
        ///        Trailing zeros in the hexadecimal representation are removed unless all the digits are zero, in which case a single zero is used.
        ///        Next, the exponent is represented by @c "p" followed by a decimal string of the unbiased exponent as if produced by a call to <b>Integer.toString(int)</b> on the exponent value.
        ///     - If <i>m</i> is a @c double value with a subnormal representation, the significand is represented by the characters @c "0x0." Followed by a hexadecimal representation of the rest of the significand as a fraction.
        ///        Trailing zeros in the hexadecimal representation are removed.
        ///        Next, the exponent is represented by @c "p-1022".  Note that there must be at least one nonzero digit in a subnormal significand.
        ///
        /// Example:
        ///     @code
        ///         toString(1.0) returns "0x1.0p0"
        ///         toString(-1.0) returns "-0x1.0p0"
        ///         toString(2.0) returns "0x1.0p1"
        ///         toString(3.0) returns "0x1.8p1"
        ///         toString(0.5) returns "0x1.0p-1"
        ///         toString(0.25) returns "0x1.0p-2"
        ///         toString(Double::MAX_VALUE) returns "0x1.fffffffffffffp1023"
        ///         toString(Double::MIN_NORMAL) returns "0x1.0p-1022"
        ///         toString(Double::MIN_VALUE) returns "0x0.0000000000001p-1022"
        ///     @endcode
        /// @param value the @c double to be converted.
        /// @return a hex string representation of the argument.
        static String toHexString(gdouble value);

        /// Returns a @c Double instance representing the specified @c double value.
        /// @param value a double value.
        /// @return a @c Double instance representing @c value.
        static Double valueOf(gdouble value);

        /// Returns a @c Double object holding the @c double value represented by the argument string @c str.
        /// Leading and trailing whitespace characters in @c str are ignored.
        /// Whitespace is removed as if by the @b String.trim method; that is, both ASCII space and control characters are removed.
        /// The rest of @c str should constitute a <i>FloatValue</i> as described by the lexical syntax rules:
        /// - @b FloatValue:
        ///     - @em Sign <sub>opt</sub> @c NaN
        ///     - @em Sign <sub>opt</sub> @c infinity
        ///     - @em Sign <sub>opt</sub> @em FloatingPointLiteral
        ///     - @em Sign <sub>opt</sub> @em HexFloatingPointLiteral
        ///     - @em SignedInteger
        /// - @b HexFloatingPointLiteral:
        ///     - <em>HexSignificand BinaryExponent FloatTypeSuffix</em><sub>opt</sub>
        /// - @b HexSignificand:
        ///     - <i>HexNumeral</i>
        ///     - <i>HexNumeral</i> @c .
        ///     - @c 0x @em HexDigits <sub>opt</sub> @c . @em HexDigits
        ///     - @c 0X @em HexDigits <sub>opt</sub> @c . @em HexDigits
        /// - @b BinaryExponent:
        ///     - <i>BinaryExponentIndicator SignedInteger</i>
        /// - @b BinaryExponentIndicator:
        ///     - @c p
        ///     - @c P
        ///
        /// where <i>Sign</i>, <i>FloatingPointLiteral</i>, <i>HexNumeral</i>, <i>HexDigits</i>, <i>SignedInteger</i> and <i>FloatTypeSuffix</i> are as defined in the lexical structure sections of <cite>The C++&trade; Language Specification</cite>.
        /// If @c str does not have the form of a <i>FloatValue</i>, then a @c NumberFormatException is thrown.
        /// Otherwise, @c str is regarded as representing an exact decimal value in the usual "computerized scientific notation" or as an exact hexadecimal value; this exact numerical value is then conceptually converted to an "infinitely precise" binary value that is then rounded to type @c double by the usual round-to-nearest rule of IEEE 754 floating-point arithmetic, which includes preserving the sign of a zero value.
        /// Note that the round-to-nearest rule also implies overflow and underflow behavior; if the exact value of @c str is large enough in magnitude (greater than or equal to (@b MAX_VALUE + @b Math.ulp(MAX_VALUE)/2), rounding to @c double will result in an infinity and if the exact value of @c str is small enough in magnitude (less than or equal to @b MIN_VALUE/2), rounding to float will result in a zero.
        /// Finally, after rounding a @c Double object representing this @c double value is returned.
        /// To interpret localized string representations of a floating-point value, use subclasses of @b core.text::NumberFormat.
        /// Note that trailing format specifiers, specifiers that determine the type of floating-point literal (@c 1.0f is a @c double value; @c 1.0d is a @c double value), do <em>not</em> influence the results of this method.
        /// In other words, the numerical value of the input string is converted directly to the target floating-point type.
        /// The two-step sequence of conversions, string to @c float followed by @c float to @c double, is <em>not</em> equivalent to converting a string directly to @c double.
        /// For example, the @c float literal @c 0.1f is equal to the @c double value @c 0.10000000149011612; the @c float literal @c 0.1f represents a different numerical value than the @c double literal @c 0.1.
        /// (The numerical value 0.1 cannot be exactly represented in a binary floating-point number.)
        /// To avoid calling this method on an invalid string and having a @c NumberFormatException be thrown, the regular expression below can be used to screen the input string:
        /// @code
        ///     String const Digits = "(\\p{Digit}+)"_Sl;
        ///     String HexDigits    = "(\\p{XDigit}+)"_Sl;
        ///     // an exponent is 'e' or 'E' followed by an optionally signed decimal integer.
        ///     String Exp              = "[eE][+-]?"_Sl + Digits;
        ///     String fpRegex       = (
        ///                 "[\\x00-\\x20]*" +  // Optional leading "whitespace"
        ///                 "[+-]?(" + // Optional sign character
        ///                 "NaN|" +           // "NaN" string
        ///                 "infinity|" +      // "infinity" string
        ///                 // A decimal floating-point string representing a finite positive
        ///                 // number without a leading sign has at most five basic pieces:
        ///                 // Digits . Digits ExponentPart FloatTypeSuffix
        ///                 //
        ///                 // Since this method allows integer-only strings as input
        ///                 // in addition to strings of floating-point literals, the
        ///                 // two sub-patterns below are simplifications of the grammar productions of
        ///                 // The C++ Language Specification.
        ///
        ///                 //  Digits ._opt Digits_opt ExponentPart_opt FloatTypeSuffix_opt
        ///                 "((("+Digits+"(\\.)?("+Digits+"?)("+Exp+")?)|" +
        ///
        ///                 //  . Digits ExponentPart_opt FloatTypeSuffix_opt
        ///                 "(\\.("+Digits+")("+Exp+")?)|" +
        ///
        ///                 //  Hexadecimal strings
        ///                 "((" +
        ///                 //  0[xX] HexDigits ._opt BinaryExponent FloatTypeSuffix_opt
        ///                 "(0[xX]" + HexDigits + "(\\.)?)|" +
        ///                 // 0[xX] HexDigits_opt. HexDigits BinaryExponent FloatTypeSuffix_opt
        ///                 "(0[xX]" + HexDigits + "?(\\.)" + HexDigits + ")" +
        ///
        ///                 ")[pP][+-]?" + Digits + "))" +
        ///                 "[fFdD]?))" +
        ///                 "[\\x00-\\x20]*"); // Optional trailing "whitespace"
        ///
        ///     if (Pattern.matches(fpRegex, myString))
        ///         Double.valueOf(myString); // Will not throw NumberFormatException
        ///      else {
        ///         // Perform suitable alternative action
        ///      }
        /// @endcode
        ///
        /// @param str the string to be parsed.
        /// @return a @c Double object holding the value represented by the @c String argument.
        /// @throws NumberFormatException  if the string does not contain a parsable number.
        static Double valueOf(const String& str);

        /// Returns a new @c double initialized to the value represented by the specified @c String, as performed by the @c valueOf method of class @c Double.
        /// @param str the string to be parsed.
        /// @return the @c double value represented by the string argument.
        /// @throws NumberFormatException if the string does not contain a parsable @c double.
        /// @see   core.lang::Double.valueOf(String)
        static gdouble parseDouble(const String& str);

        /// Returns @c true if this @c Double value is a Not-a-Number (NaN), @c false otherwise.
        /// @return @c true if the value represented by this object is NaN; @c false otherwise.
        gboolean isNaN() const;

        /// Returns @c true if the specified number is a Not-a-Number (NaN) value, @c false otherwise.
        /// @param value the value to be tested.
        /// @return @c true if the argument is NaN; @c false otherwise.
        static gboolean isNaN(gdouble value);

        /// Returns @c true if this @c Double value is infinitely large in magnitude, @c false otherwise.
        /// @return @c true if the value represented by this object is positive infinity or negative infinity; @c false otherwise.
        gboolean isInfinite() const;

        /// Returns @c true if the specified number is infinitely large in magnitude, @c false otherwise.
        /// @param value the value to be tested.
        /// @return @c true if the argument is positive infinity or negative infinity; @c false otherwise.
        static gboolean isInfinite(gdouble value);

        /// Returns @c true if the argument is a finite floating-point value; returns @c false otherwise (for NaN and infinity
        /// arguments).
        /// @param value the @c double value to be tested
        /// @return @c true if the argument is a finite floating-point value, @c false otherwise.
        static gboolean isFinite(gdouble value);

        /// Returns a hash code for this @c Double object.
        /// The result is the exclusive OR of the two halves of the @c long integer bit representation, exactly as produced by the method @b toLongBits(double), of the primitive @c double value represented by this @c Double object.
        /// That is, the hash code is the value of the expression: @code (int)(v^(v>>>32)) @endcode where @c v is defined by: @code long v = Double.toLongBits(this.doubleValue()); @endcode
        /// @return a @c hash code value for this object.
        gint hash() const override;

        /// Returns a hash code for a @c double value; compatible with @c Double.hash().
        /// @param value the value to hash
        /// @return a hash code value for a @c float value.
        static gint hash(gdouble value);

        /// Compares this object against the specified object.
        /// The result is @c true if and only if the argument is not @c null and is a @c Double object that represents a @c double with the same value as the @c double represented by this object.
        /// For this purpose, two @c double values are considered to be the same if and only if the method @b toLongBits(double) returns the identical @c int value when applied to each.
        /// Note that in most cases, for two instances of class @c Double, @c d1 and @c d2, the value of @c d1.equals(d2) is @c true if and only if @code d1.doubleValue() == d2.doubleValue() @endcode, also has the value @c true. However, there are two exceptions:
        /// - If @c d1 and @c d2 both represent @c Double.NaN, then the @c equals method returns @c true, even though @code Double.NaN==Double.NaN @endcode has the value @c false.
        /// - If @c d1 represents @c +0.0f while @c d2 represents @c -0.0, or vice versa, the @c equal test has the value @c false, even though @code 0.0==-0.0 @endcode has the value @c true.
        ///
        /// This definition allows hash tables to operate properly.
        /// @param other the object to be compared
        /// @return @c true if the objects are the same; @c false otherwise.
        /// @see core.lang::Double.toLongBits(double)
        gboolean equals(const Object& other) const override;

        /// Returns a representation of the specified floating-point value according to the IEEE 754 floating-point "double format" bit layout.
        /// Bit 63 (the bit that is selected by the mask @c 0x8000000000000000L) represents the sign of the floating-point number.
        /// Bits 62-52 (the bits that are selected by the mask @c 0x7ff0000000000000L) represent the exponent.
        /// Bits 51-0 (the bits that are selected by the mask @c 0x000fffffffffffffL) represent the significand (sometimes called the mantissa) of the floating-point number.
        /// If the argument is positive infinity, the result is @c 0x7ff0000000000000L.
        /// If the argument is negative infinity, the result is @c 0xfff0000000000000L.
        /// If the argument is NaN, the result is @c 0x7ff8000000000000L.
        /// In all cases, the result is a @c long integer that, when given to the @b fromLongBits(long) method, will produce a floating-point value the same as the argument to @c toLongBits (except all NaN values are collapsed to a single "canonical" NaN value).
        /// @param value @c double precision floating-point number.
        /// @return the bits that represent the floating-point number.
        static glong toLongBits(gdouble value);

        /// Returns a representation of the specified floating-point value according to the IEEE 754 floating-point "double format" bit layout, preserving Not-a-Number (NaN) values.
        /// Bit 63 (the bit that is selected by the mask @c 0x8000000000000000L) represents the sign of the floating-point number.
        /// Bits 62-52 (the bits that are selected by the mask @c 0x7ff0000000000000L) represent the exponent.
        /// Bits 51-0 (the bits that are selected by the mask @c 0x000fffffffffffffL) represent the significand (sometimes called the mantissa) of the floating-point number.
        /// If the argument is positive infinity, the result is @c 0x7ff0000000000000L.
        /// If the argument is negative infinity, the result is @c 0xfff0000000000000L.
        /// If the argument is NaN, the result is the @c long integer representing the actual NaN value.
        /// Unlike the @c toLongBits method, @c toRawLongBits does not collapse all the bit patterns encoding a NaN to a single "canonical" NaN value.
        /// In all cases, the result is a @c long integer that, when given to the @b fromLongBits(long) method, will produce a floating-point value the same as the argument to @c toLongBits (except all NaN values are collapsed to a single "canonical" NaN value).
        /// @param value @c double precision floating-point number.
        /// @return the bits that represent the floating-point number.
        static glong toRawLongBits(gdouble value);

        /// Returns the @c double value corresponding to a given bit representation.
        /// The argument is considered to be a representation of a floating-point value according to the IEEE 754 floating-point "double format" bit layout.
        /// If the argument is @c 0x7ff0000000000000L, the result is positive infinity.
        /// If the argument is @c 0xfff0000000000000L, the result is negative infinity.
        /// If the argument is any value in the range @c 0x7ff0000000000001L through @c 0x7fffffffffffffffL or in the range @c 0xfff0000000000001L through @c 0xffffffffffffffffL, the result is a NaN.
        /// No IEEE 754 floating-point operation provided by C++ can distinguish between two NaN values of the same type with different bit patterns.
        /// Distinct values of NaN are only distinguishable by use of the @c Double.toRawLongBits method.
        /// In all other cases, let <i>s</i>, <i>e</i>, and <i>m</i> be three values that can be computed from the argument:
        /// @code
        ///     int s = ((bits >> 63) == 0)? 1: -1;
        ///     int e = (int) ((bits >> 52) & 0x7ffL);
        ///     long m = (e == 0)? (bits & 0xfffffffffffffL) << 1: (bits & 0xfffffffffffffL) | 0x10000000000000L;
        /// @endcode
        /// Then the floating-point result equals the value of the mathematical expression <i>s</i>·<i>m</i>·2<sup><i>e</i>-1075</sup>.
        /// Note that this method may not be able to return a @c double NaN with exactly same bit pattern as the @c long argument.
        /// IEEE 754 distinguishes between two kinds of NaNs, quiet NaNs and <i>signaling NaNs</i>.
        /// The differences between the two kinds of NaN are generally not visible in C++.
        /// Arithmetic operations on signaling NaNs turn them into quiet NaNs with a different, but often similar, bit pattern.
        /// However, on some processors merely copying a signaling NaN also performs that conversion.
        /// In particular, copying a signaling NaN to return it to the calling method may perform this conversion.
        /// So @c fromLongBits may not be able to return a @c double with a signaling NaN bit pattern.
        /// Consequently, for some @c long values, @code toRawLongBits(fromLongBits(start)) @endcode may <i>not</i> equal @c start.
        /// Moreover, which particular bit patterns represent signaling NaNs is platform-dependent; although all NaN bit patterns, quiet or signaling, must be in the NaN range identified above.
        /// @param value any @c long integer.
        /// @return the @c double floating-point value with the same bit pattern.
        static gdouble fromLongBits(glong value);

        /// Compares two @c Double objects numerically.
        /// There are two ways in which comparisons performed by this method differ from those performed by the C++ language numerical comparison operators (@code <, <=, ==, >=, > @endcode ) when applied to primitive @c float values:
        /// - @c Double.NaN is considered by this method to be equal to itself and greater than all other @c double values (including @c Double.INF).
        /// - @c 0.0 is considered by this method to be greater than @c -0.0.
        /// This ensures that the <i>natural ordering</i> of @c Double objects imposed by this method is <i>consistent with equals</i>.
        /// @param other the @c Double to be compared.
        /// @return the value @c 0 if @c anotherFloat is numerically equal to this @c Double; a value less than @c 0 if this @c Double is numerically less than @c anotherFloat; and a value greater than @c 0 if this @c Double is numerically greater than @c anotherFloat.
        /// @see Comparable.compareTo(Object)
        gint compareTo(const Double& other) const override;

        /// Compares the two specified @c double values.
        /// The sign of the integer value returned is the same as that of the integer that would be returned by the call: @code new Double(a).compareTo(new Double(b)) @endcode
        /// @param a the first @c double to compare.
        /// @param b the second @c double to compare.
        /// @return the value @c 0 if @c an is numerically equal to @c b; a value less than @c 0 if @c an is numerically less than @c b; and a value greater than @c 0 if @c an is numerically greater than @c b.
        gint compare(gdouble a, gdouble b);

        /// Adds two @c double values together as per the + operator.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        static gdouble sum(gdouble a, gdouble b);

        /// Returns the greater of two @c double values as if by calling <b>Math.max(double, double)</b>.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        /// @see core.function::BinaryOperator
        static gdouble max(gdouble a, gdouble b);

        /// Returns the smaller of two @c double values as if by calling <b>Math.min(double, double)</b>.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        /// @see core.function::BinaryOperator
        static gdouble min(gdouble a, gdouble b);

        CORE_INTRINSIC_ACCESS_DECL(gdouble)

        Double& clone() const override;
    };
} // core

#endif // CORE_LANG_DOUBLE_H
