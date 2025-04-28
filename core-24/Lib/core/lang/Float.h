//
// Created by brunshweeck on 4/21/25.
//

#ifndef CORE_LANG_FLOAT_H
#define CORE_LANG_FLOAT_H

#include "Byte.h"
#include "Comparable.h"
#include "Number.h"

namespace core
{
    /// The @c Float class wraps a value of primitive type @c float in an object.
    /// An object of type @c Float contains a single field whose type is @c float.
    /// In addition, this class provides several methods for converting a @c float to a @c String and a @c String to a @c float, as well as other constants and methods useful when dealing with a @c float.
    class Float $final : public lang::Comparable<Float>, public lang::Number
    {
        /// The value of the Float.
        gfloat value;

    public:
        /// A constant holding the largest positive finite value of a type @c float, (2-2<sup>-23</sup>)&middot;2<sup>127</sup>.
        /// It is equal to the hexadecimal floating-point literal @c 0x1.fffffeP+127f and also equal to @c Float.fromIntBits(0x7f7fffff).
        static CORE_FAST gfloat MAX_VALUE = 0x1.FFFFFEp+127f; // 3.4028235e+38f

        /// A constant holding the smallest positive normal value of type @c float, 2<sup>-126</sup>.
        /// It is equal to the hexadecimal floating-point literal @c 0x1.0p-126f and also equal to @c Float.fromIntBits(0x00800000).
        static CORE_FAST gfloat MIN_NORMAL = 0x1.000000p-126f; // 1.17549435E-38f

        /// A constant holding the smallest positive nonzero value of a type @c float, 2<sup>-149</sup>.
        /// It is equal to the hexadecimal floating-point literal @c 0x0.000002P-126f and also equal to @c Float.fromIntBits(0x1).
        static CORE_FAST gfloat MIN_VALUE = 0x0.000002p-126f; // 1.4e-45f

        /// A constant holding the positive infinity of type @c float.
        /// It is equal to the value returned by @c Float.fromIntBits(0x7f800000).
        static CORE_FAST gfloat INF = (gfloat)__builtin_infinity();

        /// A constant holding a Not-a-Number (NaN) value of a type @c float.
        /// It is equivalent to the value returned by @c Float.fromIntBits(0x7fc00000).
        static CORE_FAST gfloat NaN = __builtin_nan();

        /// Maximum exponent a finite @c float variable may have.
        /// It is equal to the value returned by @c Math.getExponent(Float.MAX_VALUE).
        static CORE_FAST gint MAX_EXPONENT = 127;

        /// Minimum exponent a normalized @c float variable may have.
        /// It is equal to the value returned by @c Math.getExponent(Float.MIN_NORMAL).
        static CORE_FAST gint MIN_EXPONENT = -126;

        /// The number of bits used to represent a @c float value.
        static CORE_FAST gint SIZE = 1 << 5;

        /// The number of bytes used to represent a @c float value.
        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        /// Constructs a newly allocated @c Float object that represents the primitive @c float argument.
        /// @param value the value to be represented by the @c Float.
        Float(gfloat value = .0f);

        ~Float() override = default;

        /// Returns the value of this @c Float as a @c byte after a narrowing primitive conversion.
        /// @return the @c float value represented by this object converted to type @c byte
        gbyte byteValue() const override;

        /// Returns the value of this @c Float as a @c short after a narrowing primitive conversion.
        /// @return the @c float value represented by this object converted to type @c short
        gshort shortValue() const override;

        /// Returns the value of this @c Float as an @c int after a narrowing primitive conversion.
        /// @return the @c float value represented by this object converted to type @c int
        gint intValue() const override;

        /// Returns the value of this @c Float as a @c long after a narrowing primitive conversion.
        /// @return the @c float value represented by this object converted to type @c long
        glong longValue() const override;

        /// Returns the @c float value of this @c Float object.
        /// @return the @c float value represented by this object.
        gfloat floatValue() const override;

        /// Returns the value of this @c Float as a @c double after a widening primitive conversion.
        /// @return the @c float value represented by this object converted to type @c double.
        gdouble doubleValue() const override;

        /// Returns a string representation of this @c Float object.
        /// The primitive @c float value represented by this object is converted to a @c String exactly as if by the method @c toString of one argument.
        /// @return a @c String representation of this object.
        /// @see java.lang.Float#toString(float)
        String toString() const override;

        /// Returns a string representation of the @c float argument.
        /// All characters mentioned below are ASCII characters.
        ///  - If the argument is NaN, the result is the string "@c NaN";
        ///  - Otherwise, the result is a string that represents the sign and magnitude (absolute value) of the argument.
        ///     If the sign is negative, the first character of the result is @c '-' (U+002D); if the sign is positive, no sign character appears in the result.
        ///     As for the magnitude <i>m</i>:
        ///         - If <i>m</i> is an infinity, it is represented by the characters @c "infinity"; thus, positive infinity produces the result @c "infinity", and negative infinity produces the result @c "-infinity".
        ///         - If <i>m</i> is zero, it is represented by the characters @c "0.0"; thus, negative zero produces the result @c "-0.0", and positive zero produces the result @c "0.0".
        ///         - If <i>m</i> is greater than or equal to 10<sup>-3</sup> but less than 10<sup>7</sup>, then it is represented as the integer part of <i>m</i>, in decimal form with no leading zeroes, followed by @c '.' (U+002E), followed by one or more decimal digits representing the fractional part of <i>m</i>.
        ///         - If <i>m</i> is less than 10<sup>-3</sup> or greater than or equal to 10<sup>7</sup>, then it is represented in so-called "computerized scientific notation." Let <i>n</i> be the unique integer such that 10<sup><i>n</i> </sup>&le; <i>m</i> < 10<sup><i>n</i>+1</sup>; then let <i>a</i> be the mathematically exact quotient of <i>m</i> and 10<sup><i>n</i></sup> so that 1 &le; <i>a</i> < 10.
        ///            The magnitude is then represented as the integer part of <i>a</i>, as a single decimal digit, followed by @c '.' (U+002E), followed by decimal digits representing the fractional part of <i>a</i>, followed by the letter @c 'E' (U+0045), followed by a representation of <i>n</i> as a decimal integer, as produced by the method @b Integer.toString(int) .
        ///
        /// How many digits must be printed for the fractional part of <i>m</i> or <i>a</i>? There must be at least one digit to represent the fractional part, and beyond that as many, but only as many, more digits as are needed to uniquely distinguish the argument value from adjacent values of type @c float. That is, suppose that <i>x</i> is the exact mathematical value represented by the decimal representation produced by this method for a finite nonzero argument <i>f</i>.
        /// Then <i>f</i> must be the @c float value nearest to <i>x</i>; or, if two @c float values are equally close to <i>x</i>, then <i>f</i> must be one of them and the least significant bit of the significand of <i>f</i> must be @c 0.
        /// To create localized string representations of a floating-point value, use subclasses of @b core.text::NumberFormat.
        /// @param value the float to be converted.
        /// @return a string representation of the argument.
        static String toString(gfloat value);

        /// Returns a hexadecimal string representation of the @c float argument.
        /// All characters mentioned below are ASCII characters.
        /// - If the argument is NaN, the result is the string "@c NaN".
        /// - Otherwise, the result is a string that represents the sign and magnitude (absolute value) of the argument.
        ///    If the sign is negative, the first character of the result is @c '-' (U+002D); if the sign is positive, no sign character appears in the result.
        ///    As for the magnitude <i>m</i>:
        ///     - If <i>m</i> is an infinity, it is represented by the string @c "infinity"; thus, positive infinity produces the result @c "infinity" and negative infinity produces the result @c "-infinity".
        ///     - If <i>m</i> is zero, it is represented by the string @c "0x0.0p0"; thus, negative zero produces the result @c "-0x0.0p0" and positive zero produces the result @c "0x0.0p0".
        ///     - If <i>m</i> is a @c float value with a normalized representation, substrings are used to represent the significand and exponent fields.  The significand is represented by the characters @c "0x1." followed by a lowercase hexadecimal representation of the rest of the significand as a fraction.
        ///        Trailing zeros in the hexadecimal representation are removed unless all the digits are zero, in which case a single zero is used.
        ///        Next, the exponent is represented by @c "p" followed by a decimal string of the unbiased exponent as if produced by a call to @b Integer.toString(int) on the exponent value.
        ///     - If <i>m</i> is a @c float value with a subnormal representation, the significand is represented by the characters @c "0x0." followed by a hexadecimal representation of the rest of the significand as a fraction.
        ///        Trailing zeros in the hexadecimal representation are removed.
        ///        Next, the exponent is represented by @c "p-126".  Note that there must be at least one nonzero digit in a subnormal significand.
        ///
        /// Example:
        ///     @code
        ///         toString(1.0f) returns "0x1.0p0"
        ///         toString(-1.0f) returns "-0x1.0p0"
        ///         toString(2.0f) returns "0x1.0p1"
        ///         toString(3.0f) returns "0x1.8p1"
        ///         toString(0.5f) returns "0x1.0p-1"
        ///         toString(0.25f) returns "0x1.0p-2"
        ///         toString(Float::MAX_VALUE) returns "0x1.fffffep127"
        ///         toString(Float::MIN_NORMAL) returns "0x1.0p-126"
        ///         toString(Float::MIN_VALUE) returns "0x0.000002p-126"
        ///     @endcode
        /// @param value the @c float to be converted.
        /// @return a hex string representation of the argument.
        static String toHexString(gfloat value);

        /// Returns a @c Float instance representing the specified @c float value.
        /// @param value a float value.
        /// @return a @c Float instance representing @c value.
        static Float valueOf(gfloat value);

        /// Returns a @c Float object holding the @c float value represented by the argument string @c str.
        /// Leading and trailing whitespace characters in @c str are ignored.
        /// Whitespace is removed as if by the @b String.trim method; that is, both ASCII space and control characters are removed.
        /// The rest of @c str should constitute a <i>FloatValue</i> as described by the lexical syntax rules:
        /// - @b FloatValue:
        ///     - @em Sign<sub>opt</sub> @c NaN
        ///     - @em Sign<sub>opt</sub> @c infinity
        ///     - @em Sign<sub>opt</sub> @em FloatingPointLiteral
        ///     - @em Sign<sub>opt</sub> @em HexFloatingPointLiteral
        ///     - @em SignedInteger
        /// - @b HexFloatingPointLiteral:
        ///     - <em>HexSignificand BinaryExponent FloatTypeSuffix</em><sub>opt</sub>
        /// - @b HexSignificand:
        ///     - @em HexNumeral
        ///     - @em HexNumeral  @c .
        ///     - @c 0x @em HexDigits<sub>opt</sub> @c . @em  HexDigits
        ///     - @c 0X @em  HexDigits<sub>opt</sub> @c .  @em HexDigits
        /// - @b BinaryExponent:
        ///     - <i>BinaryExponentIndicator SignedInteger</i>
        /// - @b BinaryExponentIndicator:
        ///     - @c p
        ///     - @c P
        ///
        /// where @em Sign, @em FloatingPointLiteral, @em HexNumeral, @em HexDigits, @em SignedInteger and @em FloatTypeSuffix are as defined in the lexical structure sections of <cite>The C++&trade; Language Specification</cite>.
        /// If @c str does not have the form of a @em FloatValue, then a @c NumberFormatException is thrown.
        /// Otherwise, @c str is regarded as representing an exact decimal value in the usual "computerized scientific notation" or as an exact hexadecimal value; this exact numerical value is then conceptually converted to an "infinitely precise" binary value that is then rounded to type @c float by the usual round-to-nearest rule of IEEE 754 floating-point arithmetic, which includes preserving the sign of a zero value.
        /// Note that the round-to-nearest rule also implies overflow and underflow behaviour; if the exact value of @c str is large enough in magnitude (greater than or equal to (@b MAX_VALUE + @b Math.ulp(MAX_VALUE)/2), rounding to @c float will result in an infinity and if the exact value of @c str is small enough in magnitude (less than or equal to @b MIN_VALUE/2), rounding to float will result in a zero.
        /// Finally, after rounding a @c Float object representing this @c float value is returned.
        /// To interpret localized string representations of a floating-point value, use subclasses of @b core.text::NumberFormat.
        /// Note that trailing format specifiers, specifiers that determine the type of floating-point literal (@c 1.0f is a @c float value; @c 1.0d is a @c double value), do <em>not</em> influence the results of this method.
        /// In other words, the numerical value of the input string is converted directly to the target floating-point type.
        /// In general, the two-step sequence of conversions, string to @c double follow by @c double to @c float, is <em>not</em> equivalent to converting a string directly to @c float.
        /// For example, if first converted to an intermediate @c double and then to @c float, the string<br> @c "1.00000017881393421514957253748434595763683319091796875001d"<br> results in the @c float value @c 1.0000002f; if the string is converted directly to @c float, <code>1.000000<b>1</b>f</code> results.
        /// To avoid calling this method on an invalid string and having a @c NumberFormatException be thrown, the documentation for @b Double.valueOf lists a regular expression which can be used to screen the input.
        /// @param str the string to be parsed.
        /// @return a @c Float object holding the value represented by the @c String argument.
        /// @throws NumberFormatException  if the string does not contain a parsable number.
        static Float valueOf(const String& str);

        /// Returns a new @c float initialized to the value represented by the specified @c String, as performed by the @c valueOf method of class @c Float.
        /// @param str the string to be parsed.
        /// @return the @c float value represented by the string argument.
        /// @throws NumberFormatException if the string does not contain a parsable @c float.
        /// @see   java.lang.Float#valueOf(String)
        static gfloat parseFloat(const String& str);

        /// Returns @c true if this @c Float value is a Not-a-Number (NaN), @c false otherwise.
        /// @return @c true if the value represented by this object is NaN; @c false otherwise.
        gboolean isNaN() const;

        /// Returns @c true if the specified number is a Not-a-Number (NaN) value, @c false otherwise.
        /// @param value the value to be tested.
        /// @return @c true if the argument is NaN; @c false otherwise.
        static gboolean isNaN(gfloat value);

        /// Returns @c true if this @c Float value is infinitely large in magnitude, @c false otherwise.
        /// @return @c true if the value represented by this object is positive infinity or negative infinity; @c false otherwise.
        gboolean isInfinite() const;

        /// Returns @c true if the specified number is infinitely large in magnitude, @c false otherwise.
        /// @param value the value to be tested.
        /// @return @c true if the argument is positive infinity or negative infinity; @c false otherwise.
        static gboolean isInfinite(gfloat value);

        /// Returns @c true if the argument is a finite floating-point value; returns @c false otherwise (for NaN and infinity
        /// arguments).
        /// @param value the @c float value to be tested
        /// @return @c true if the argument is a finite floating-point value, @c false otherwise.
        static gboolean isFinite(gfloat value);

        /// Returns a hash code for this @c Float object.
        /// The result is the integer bit representation, exactly as produced by the method @b toIntBits(float), of the primitive @c float value represented by this @c Float object.
        /// @return a hash code value for this object.
        gint hash() const override;

        /// Returns a hash code for a @c float value; compatible with @c Float.hashCode().
        /// @param value the value to hash
        /// @return a hash code value for a @c float value.
        static gint hash(gfloat value);

        /// Compares this object against the specified object.
        /// The result is @c true if and only if the argument is not @c null and is a @c Float object that represents a @c float with the same value as the @c float represented by this object.
        /// For this purpose, two @c float values are considered to be the same if and only if the method @b toIntBits(float) returns the identical @c int value when applied to each.
        /// Note that in most cases, for two instances of class @c Float, @c f1 and @c f2, the value of @c f1.equals(f2) is @c true if and only if @code f1.floatValue() == f2.floatValue()@endcode, also has the value @c true. However, there are two exceptions:
        /// - If @c f1 and @c f2 both represent @c Float.NaN, then the @c equals method returns @c true, even though @code Float.NaN==Float.NaN @endcode has the value @c false.
        /// - If @c f1 represents @c +0.0f while @c f2 represents @c -0.0f, or vice versa, the @c equal test has the value @c false; even though @code 0.0f==-0.0f @endcode has the value @c true.
        ///
        /// This definition allows hash tables to operate properly.
        /// @param other the object to be compared
        /// @return @c true if the objects are the same; @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Returns a representation of the specified floating-point value according to the IEEE 754 floating-point "single format" bit layout.
        /// Bit 31 (the bit that is selected by the mask @c 0x80000000) represents the sign of the floating-point number.
        /// Bits 30-23 (the bits that are selected by the mask @c 0x7f800000) represent the exponent.
        /// Bits 22-0 (the bits that are selected by the mask @c 0x007fffff) represent the significand (sometimes called the mantissa) of the floating-point number.
        /// If the argument is positive infinity, the result is @c 0x7f800000.
        /// If the argument is negative infinity, the result is @c 0xff800000.
        /// If the argument is NaN, the result is @c 0x7fc00000.
        /// In all cases, the result is an integer that, when given to the @b fromIntBits(int) method, will produce a floating-point value the same as the argument to @c toIntBits (except all NaN values are collapsed to a single "canonical" NaN value).
        /// @param value a floating-point number.
        /// @return the bits that represent the floating-point number.
        static gint toIntBits(gfloat value);

        /// Returns a representation of the specified floating-point value according to the IEEE 754 floating-point "single format" bit layout, preserving Not-a-Number (NaN) values.
        /// Bit 31 (the bit that is selected by the mask @c 0x80000000) represents the sign of the floating-point number.
        /// Bits 30-23 (the bits that are selected by the mask @c 0x7f800000) represent the exponent.
        /// Bits 22-0 (the bits that are selected by the mask @c 0x007fffff) represent the significand (sometimes called the mantissa) of the floating-point number.
        /// If the argument is positive infinity, the result is @c 0x7f800000.
        /// If the argument is negative infinity, the result is @c 0xff800000.
        /// If the argument is NaN, the result is the integer representing the actual NaN value.  Unlike the @c toIntBits method, @c toRawIntBits does not collapse all the bit patterns encoding a NaN to a single "canonical" NaN value.
        /// In all cases, the result is an integer that, when given to the @b fromIntBits(int) method, will produce a floating-point value the same as the argument to @c toRawIntBits.
        /// @param value a floating-point number.
        /// @return the bits that represent the floating-point number.
        static gint toRawIntBits(gfloat value);

        /// Returns the @c float value corresponding to a given bit representation.
        /// The argument is considered to be a representation of a floating-point value according to the IEEE 754 floating-point "single format" bit layout.
        /// If the argument is @c 0x7f800000, the result is positive infinity.
        /// If the argument is @c 0xff800000, the result is negative infinity.
        /// If the argument is any value in the range @c 0x7f800001 through @c 0x7fffffff or in the range @c 0xff800001 through @c 0xffffffff, the result is a NaN.
        /// No IEEE 754 floating-point operation provided by C++ can distinguish between two NaN values of the same type with different bit patterns.
        /// Distinct values of NaN are only distinguishable by use of the @c Float.toRawIntBits method.
        /// In all other cases, let @em s, @em e, and @em m be three values that can be computed from the argument:
        /// @code
        ///     int s = ((bits >> 31) == 0)? 1: -1;
        ///     int e = ((bits >> 23) & 0xff);
        ///     int m = (e == 0)? (bits & 0x7fffff) << 1: (bits & 0x7fffff) | 0x800000;
        /// @endcode
        /// Then the floating-point result equals the value of the mathematical expression <i>s</i>&middot;<i>m</i>&middot;2<sup><i>e</i>-150</sup>.
        /// Note that this method may not be able to return a @c float NaN with the exactly same bit pattern as the @c int argument.
        /// IEEE 754 distinguishes between two kinds of NaNs, quiet NaNs and <i>signaling NaNs</i>.
        /// The differences between the two kinds of NaN are generally not visible in C++.
        /// Arithmetic operations on signaling NaNs turn them into quiet NaNs with a different, but often similar, bit pattern.
        /// However, on some processors merely copying a signaling NaN also performs that conversion.
        /// In particular, copying a signaling NaN to return it to the calling method may perform this conversion.
        /// So @c fromIntBits may not be able to return a @c float with a signaling NaN bit pattern.
        /// Consequently, for some @c int values, @code toRawIntBits(fromIntBits(start)) @endcode may <i>not</i> equal @c start.
        /// Moreover, which particular bit patterns represent signaling NaNs is platform-dependent; although all NaN bit patterns, quiet or signaling, must be in the NaN range identified above.
        /// @param value an integer.
        /// @return the @c float floating-point value with the same bit pattern.
        static gfloat fromIntBits(gint value);

        /// Compares two @c Float objects numerically.
        /// There are two ways in which comparisons performed by this method differ from those performed by the C++ language numerical comparison operators (@code <, <=, ==, >=, > @endcode ) when applied to primitive @c float values:
        /// - @c Float.NaN is considered by this method to be equal to itself and greater than all other @c float values (including @c Float.INF).
        /// - @c 0.0f is considered by this method to be greater than @c -0.0f.
        /// This ensures that the <i>natural ordering</i> of @c Float objects imposed by this method is <i>consistent with equals</i>.
        /// @param other the @c Float to be compared.
        /// @return the value @c 0 if @c anotherFloat is numerically equal to this @c Float; a value less than @c 0 if this @c Float is numerically less than @c anotherFloat; and a value greater than @c 0 if this @c Float is numerically greater than @c anotherFloat.
        /// @see Comparable#compareTo(Object)
        gint compareTo(const Float& other) const override;

        /// Compares the two specified @c float values.
        /// The sign of the integer value returned is the same as that of the integer that would be returned by the call: @code new Float(a).compareTo(new Float(b)) @endcode
        /// @param a the first @c float to compare.
        /// @param b the second @c float to compare.
        /// @return the value @c 0 if @c a is numerically equal to @c b; a value less than @c 0 if @c a is numerically less than @c b; and a value greater than @c 0 if @c a is numerically greater than @c b.
        gint compare(gfloat a, gfloat b);

        /// Adds two @c float values together as per the + operator.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        static gfloat sum(gfloat a, gfloat b);

        /// Returns the greater of two @c float values as if by calling <b>Math.max(float, float)</b>.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        /// @see core.function::BinaryOperator
        static gfloat max(gfloat a, gfloat b);

        /// Returns the smaller of two @c float values as if by calling <b>Math.min(float, float)</b>.
        /// @param a the first operand
        /// @param b the second operand
        /// @return the sum of @c a and @c b
        /// @see core.function::BinaryOperator
        static gfloat min(gfloat a, gfloat b);

        CORE_INTRINSIC_ACCESS_DECL(gfloat)

        Float& clone() const override;
    };
} // core

#endif // CORE_LANG_FLOAT_H
