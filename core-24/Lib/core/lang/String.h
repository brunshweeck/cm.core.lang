//
// Created by brunshweeck on 4/17/25.
//

#ifndef CORE_LANG_STRING_H
#define CORE_LANG_STRING_H

#include "CharSequence.h"
#include "Class.h"
#include "Comparable.h"
#include "Integer.h"

namespace core
{
    /// The @c String class represents character strings.
    /// All string literals in C++ programs suffixed by @c _S, @c _Su and @c _Sl, such as @c "abc"_Su, are implemented as instances of this class.
    /// Strings are constant; their values cannot be changed after they are created.
    /// String buffers support mutable strings.
    /// Because String objects are immutable, they can be shared.
    /// For example,
    /// @code
    ///      String str = "abc"_Su;
    /// @endcode
    /// is equivalent to:
    ///  @code
    ///      CharArray data = {'a', 'b', 'c'};
    ///      String str = String(data);
    ///  @endcode
    /// Here are some more examples of how strings can be used:
    /// @code
    ///     Console::out.writeLine("abc"_Su);
    ///     String cde = "cde";
    ///     Console::out.writeLine("abc"_Su + cde);
    ///     String c = "abc".substring(2, 3);
    ///     String d = cde.substring(1, 2);
    /// @endcode
    /// The class @c String includes methods for examining individual characters of the sequence, for comparing strings, for searching strings, for extracting substrings, and for creating a copy of a string with all characters translated to uppercase or to lowercase.
    /// Case mapping is based on the Unicode Standard version specified by the @b core::Character class.
    /// The C++ language provides special support for the string concatenation operator (&nbsp;+&nbsp;), and for conversion of other objects to strings.
    /// For additional information on string concatenation and conversion, see <i>The C++&trade; Language Specification</i>.
    ///
    /// A @c String represents a string in the UTF-16 format in which <em>supplementary characters</em> are represented by <em>surrogate pairs</em> (see the section <a href="Character.html#unicode">Unicode Character Representations</a> in the @c Character class for more information).
    /// Index values refer to @c char code units, so a supplementary character uses two positions in a @c String.
    ///
    /// The @c String class provides methods for dealing with Unicode code points (i.e., characters), in addition to those for dealing with Unicode code units (i.e., @c char values).
    ///
    /// Unless otherwise noted, methods for comparing Strings do not take locale into account.
    /// The @b core.text::Collator class provides methods for finer-grain, locale-sensitive String comparison.
    /// @note The implementation of the string concatenation operator is left to the discretion of a C++ compiler, as long as the compiler ultimately conforms to <i>The Java&trade; Language Specification</i>.
    /// The implementation of string conversion is typically through the method @c toString, defined by @c Object and inherited by all classes in C++.
    /// @see     core::Object.toString()
    /// @see     core::XString
    /// @see     core.charset::Charset
    class String $final : public lang::CharSequence, public lang::Comparable<String>
    {
        $alias(Bytes, Class<gbyte>::Pointer);

        /// The array used to store characters
        Bytes value = {};

        /// The number of Utf-16 characters on string
        gint count = 0;

        /// Cache of hash value for the String
        gint mutable lastHash = 0;

        /// Cache if the hash has been calculated as actually being zero, enabling us to avoid recalculating this.
        gboolean mutable zeroHashed = false;

        ///  If String compaction is disabled, the bytes in @c value field are always encoded in Utf-16.
        static gboolean CORE_FAST UsingCompactString = true;

        static gboolean CORE_FAST UsingStrictCtor = false;

    public:
        ///  Initializes a newly created @c String object so that it represents an empty character sequence.
        ///  Note that use of this constructor is unnecessary since Strings are immutable.
        String() = default;

        /// Initializes a newly created @c String object so that it represents the same sequence of characters as the argument; in other words, the newly created string is a copy of the argument string.
        /// @param original A @c String
        String(const String& original);

        /// Initializes a newly created @c String object so that it represents the same sequence of characters as the argument; in other words, the newly created string is a copy of the argument string.
        /// @param original A @c String
        String(const String&& original) CORE_NOTHROW;

        /// Allocates a new @c String so that it represents the sequence of characters currently contained in the character array argument.
        /// The contents of the character array are copied; subsequent modification of the character array does not affect the newly created string.
        /// @param chars Array that is the source of characters
        CORE_EXPLICIT String(const CharArray& chars);

        /// Allocates a new @c String that contains characters from a subarray of the character array argument.
        /// The @c offset argument is the index of the first character of the subarray, and the @c count argument specifies the length of the subarray.
        /// The contents of the subarray are copied; subsequent modification of the character array does not affect the newly created string.
        /// @param chars Array that is the source of characters
        /// @param offset The Initial offset
        /// @param count The length
        /// @throws  IndexOutOfBoundsException If @c offset is negative, @c count is negative, or @c offset is greater than @code chars.length() - count @endcode
        CORE_EXPLICIT String(const CharArray& chars, gint offset, gint count);

        /// Allocates a new @c String that contains characters from a subarray of the <em>Unicode code point</em> array argument.
        /// The @c offset argument is the index of the first code point of the subarray, and the @c count argument specifies the length of the subarray.
        /// The contents of the subarray are converted to characters; subsequent modification of the int array does not affect the newly created string.
        /// @param codePoints Array that is the source of Unicode code points
        /// @param offset The initial offset
        /// @param count The length
        /// @throws  IllegalArgumentException If any invalid Unicode code point is found in @c codePoints
        /// @throws  IndexOutOfBoundsException If @c offset is negative, @c count is negative, or @c offset is greater than @code codePoints.length() - count @endcode
        CORE_EXPLICIT String(const IntArray& codePoints, gint offset, gint count);

        /// Allocates a new @c String constructed from a subarray of an array of 8-bit integer values.
        /// The @c offset argument is the index of the first byte of the subarray, and the @c count argument specifies the length of the subarray.
        /// Each byte in the subarray is converted to a character as specified in the @code String(ByteArray, gint) @endcode constructor.
        /// @note This method does not properly convert bytes into characters.
        ///     The recommended way to do this is via the @c String constructors that take a @c Charset,  <em>charset name</em>, or that use the <em>default charset</em>.
        ///  @param ascii The bytes to be converted to characters.
        ///  @param hiByte The top 8 bits of each 16-bit Unicode code unit.
        ///  @param offset The initial offset
        ///  @param count The length
        ///  @throws  IndexOutOfBoundsException If @c offset is negative, @c count is negative, or @c offset is greater than @code ascii.length() - count @endcode
        CORE_EXPLICIT String(const ByteArray& ascii, gint hiByte, gint offset, gint count);

        /// Allocates a new @c String containing characters constructed from an array of 8-bit integer values.
        /// Each character @c c in the resulting string is constructed from the corresponding component @c b in the byte array such that: @code c = (hiByte & 0xFF) << 8 | (b & 0xFF)@endcode.
        /// @note This method does not properly convert bytes into characters.
        ///     The recommended way to do this is via the @c String constructors that take a @c Charset, <em>charset name</em>, or that use the <em>default charset</em>.
        ///  @param ascii The bytes to be converted to characters.
        ///  @param hiByte The top 8 bits of each 16-bit Unicode code unit.
        CORE_EXPLICIT String(const ByteArray& ascii, gint hiByte);

        /// Constructs a new @c String by decoding the specified array of bytes using the specified @em charset.
        /// The length of the new @c String is a function of the charset, and hence may not be equal to the length of the byte array.
        /// The behavior of this constructor when the given bytes are not valid in the given charset is unspecified.
        /// The @b core.charset::CharsetDecoder class should be used when more control over the decoding process is required.
        /// The contents of the string are unspecified if the byte array is modified during string construction.
        /// @param bytes The bytes to be decoded into characters
        /// @param charset The name of a supported @em charset
        /// @throws  UnsupportedEncodingException If the named charset is not supported
        CORE_EXPLICIT String(const ByteArray& bytes, const String& charset);

        /// Constructs a new @c String by decoding the specified subarray of bytes using the <em>default charset</em>.
        /// The length of the new @c String is a function of the charset, and hence may not be equal to the length of the subarray.
        /// The behavior of this constructor when the given bytes are not valid in the default charset is unspecified.
        /// The @c core.charset::CharsetDecoder class should be used when more control over the decoding process is required.
        /// The contents of the string are unspecified if the byte array is modified during string construction.
        /// @param bytes The bytes to be decoded into characters
        /// @param offset The index of the first byte to decode
        /// @param count The number of bytes to decode
        /// @throws  IndexOutOfBoundsException If @c offset is negative, @c length is negative, or @c offset is greater than @code bytes.length() - length() @endcode
        CORE_EXPLICIT String(const ByteArray& bytes, gint offset, gint count);

        /// Constructs a new @c String by decoding the specified array of bytes using the <em>default charset</em>.
        /// The length of the new @c String is a function of the charset, and hence may not be equal to the length of the byte array.
        /// The behavior of this constructor when the given bytes are not valid in the default charset is unspecified.
        /// The @c core.charset::CharsetDecoder class should be used when more control over the decoding process is required.
        /// The contents of the string are unspecified if the byte array is modified during string construction.
        /// @param bytes The bytes to be decoded into characters
        CORE_EXPLICIT String(const ByteArray& bytes);

        ///
        /// @tparam T The type of input string
        /// @param value The primitive string value
        /// @throws IllegalArgumentException
        template <class T, ClassOf(true)::OnlyIf<Class<T>::isString()>  = true>
        String(const T& value)
        {
            if (Class<T>::isArray())
            {
                $alias(charT, typename Class<T>::NoArray);
                static CORE_FAST gint coder = Class<charT>::SIZE >> 1;
                glong length = Class<charT>::COUNT;
                if (length > 0 && value && value[length - 1] == 0) length -= 1L;
                initializeFromPrimalString((glong)value, length * coder, coder);
            }
            else if (Class<T>::isPointer())
            {
                $alias(charT, typename Class<T>::NoPointer);
                static CORE_FAST gint coder = Class<charT>::SIZE >> 1;
                glong length = -1;
                if (value) while (value[++length] != 0) length += 1L;
                initializeFromPrimalString((glong)value, length * coder, coder);
            }
        }

        ~String() override;

        /// Replace the character sequence of this string with a character sequence of @c other string.
        /// The contents of the string are unspecified if the other string is modified during string construction.
        /// @param other A String
        /// @return itself
        String& operator=(const String& other);

        /// Replace the character sequence of this string with a character sequence of @c other string.
        /// The contents of the string are unspecified if the other string is modified during string construction.
        /// @param other A String
        /// @return itself
        String& operator=(String&& other) CORE_NOTHROW;

        /// Return the length of this string.
        /// The length is equal to the number of Unicode code units in this string.
        /// @return The length of character sequence represented by this string
        gint length() const override;

        /// Return @c true if the value returned by @c this.length is zero.
        /// @return The value @c true if the @c length of this string is zero.
        gboolean isEmpty() const override;

        /// Returns the character value at the specified index.
        /// An index ranges from @c 0 to @code length() - 1 @endcode . The first @c char value of the sequence is at index @c 0, the next at index @c 1, and so on, as for array indexing.
        /// If the @c char value specified by the index is a @a surrogate, the surrogate value is returned.
        /// @param index the index of the character value.
        /// @return The character value at the specified index.
        /// @throw IndexOutOfBoundsException If the @c index argument is negative or not less than the length of this string.
        gchar charAt(gint index) const override;

        /// Returns the character (Unicode code point) at the specified index.
        /// The index refers to character values (Unicode code units) and ranges from @c 0 to @code length() - 1 @endcode .
        /// If the character value specified at the given index is in the high-surrogate range, the following index is less than the length of this @c String, and the character value at the following index is in the low-surrogate range, then the supplementary code point corresponding to this surrogate pair is returned.
        /// Otherwise, the character value at the given index is returned.
        /// @param index The index of index to the character values
        /// @return The code point value of the character at the @c index
        /// @throws IndexOutOfBoundsException If the @c index argument is negative or not less than the length of this string.
        gint codePointAt(gint index) const;

        /// Returns the number of Unicode code points in the specified text range of this @c String.
        /// The text range begins at the specified @c start index and extends to the @c char at index @code end - 1 @endcode .
        /// Thus, the length (in @c chars) of the text range is @code end - start@endcode.
        /// Unpaired surrogates within the text range count as one code point each.
        /// @param start The index to the first @c char of the text range.
        /// @param end The index after the last @c char of the text range.
        /// @return The number of Unicode code points in the specified text range.
        gint codePointCount(gint start, gint end) const;

        ///  Copies characters from this string into the destination character array.
        ///  The first character to be copied is at index @c start index; the last character to be copied is at index @code end -1 @endcode (thus the total number of characters to be copied is @code end - start@endcode).
        ///  The characters are copied into the subarray of @c dest starting at index @c offset and ending at index: @code offset + (end - start) - 1 @endcode
        /// @param start The index of the first character in the string to copy.
        /// @param end The index after the last character in the string to copy.
        /// @param dest The destination array.
        /// @param offset The start offset in the destination array.
        /// @throws IndexOutOfBoundsException If any of the following is true:
        ///                 - The @c start index is negative;
        ///                 - The @c start index is greater than the @c end index;
        ///                 - The @c end index is greater than the @c length of this string;
        ///                 - The @c offset is negative;
        ///                 - The @code offset + (end - start) @endcode is larger than of @c dest.length() .
        void toChars(gint start, gint end, CharArray& dest, gint offset) const;

        ///  Copies characters from this string into the destination byte array.
        ///  Each byte receives the 8 low-order bits of the corresponding character.
        ///  The eight high-order bits of each character are not copied and do not participate in the transfer in any way.
        ///  The first character to be copied is at index @c start index; the last character to be copied is at index @code end - 1 @endcode .
        ///  The total number of characters to be copied is @code end - start@endcode.
        ///  The characters, converted to bytes, are copied into the subarray of @c dest starting at index @c offset and ending at index @code offset + (end - start) -1@endcode.
        ///  @note This method does not properly convert characters into bytes.
        ///         The recommended way to do this is via the @c toBytes() method, which uses the default charset.
        /// @param start The index of the first character in the string to copy.
        /// @param end The index after the last character in the string to copy.
        /// @param dest The destination array.
        /// @param offset The start offset in the destination array.
        /// @throws IndexOutOfBoundsException If any of the following is true:
        ///                 - The @c start index is negative;
        ///                 - The @c start index is greater than the @c end index;
        ///                 - The @c end index is greater than the @c length of this string;
        ///                 - The @c offset is negative;
        ///                 - The @code offset + (end - start) @endcode is larger than of @c dest.length() .
        void toBytes(gint start, gint end, ByteArray& dest, gint offset) const;

        /// Encodes this @c String into a sequence of bytes using the named charset, storing the result into a new byte array.
        /// The behavior of this method when this string cannot be encoded in the given charset is unspecified.
        /// The @c core.charset::CharsetEncoder class should be used when more control over the encoding process is required.
        /// @param charset The name of a supported @em charset.
        /// @return The resultant byte array.
        /// @throws  UnsupportedEncodingException If the named charset is not supported
        ByteArray toBytes(const String& charset) const;

        /// Encodes this @c String into a sequence of bytes using the <em> default charset</em>, storing the result into a new byte array.
        /// The behavior of this method when this string cannot be encoded in the default charset is unspecified.
        /// The @b core.charset::CharsetEncoder class should be used when more control over the encoding process is required.
        /// @return The resultant byte array
        ByteArray toBytes() const;

        /// Compares this string to the specified object.
        /// The result is @c true if and only if the argument is not @c null and is a @c String object that represents the same sequence of characters as this object.
        /// For finer-grained String comparison, refer to @c core.text::Collator.
        /// @param other The object to compare this @c String against.
        /// @return The value @c true if the given object represents a @c String equivalent to this string, @c false otherwise.
        gboolean equals(const Object& other) const override;

        /// Compares this string to the specified @c CharSequence.
        /// The result is @c true if and only if this @c String represents the same sequence of char values as the specified sequence.
        /// For finer-grained String comparison, refer to @c core.text::Collator.
        /// @param csq The sequence to compare this @c String against
        /// @return The value @c true if this @c String represents the same sequence of char values as the specified sequence, @c false otherwise.
        gboolean contentEquals(const CharSequence& csq) const;

        /// Compares this @c String to another @c String, ignoring case considerations.
        /// Two strings are considered equal ignoring case if they are of the same length, and corresponding Unicode code points in the two strings are equal ignoring case.
        /// Two Unicode code points are considered the same ignoring case if at least one of the following is true:
        /// - The two Unicode code points are the same (as compared by the @c == operator);
        /// - Calling @code Character::toLowerCase(Character::toUpperCase(gint)) @endcode on each Unicode code point produces the same result.
        /// Note that this method does <em>not</em> take locale into account, and will result in unsatisfactory results for certain locales.
        /// The @c core.text::Collator class provides locale-sensitive comparison.
        /// @param other The @c String to compare this @c String against
        /// @return The value @c true if the argument represents an equivalent @c String ignoring case; @c false otherwise
        gboolean equalsIgnoreCase(const String& other) const;

        /// Compares two strings lexicographically.
        /// The comparison is based on the Unicode value of each character in the strings.
        /// The character sequence represented by this @c String object is compared lexicographically to the character sequence represented by the argument string.
        /// The result is a negative integer if this @c String object lexicographically precedes the argument string. The result is a positive integer if this @c String object lexicographically follows the argument string.
        /// The result is zero if the strings are equal; @c compareTo returns @c 0 exactly when the @c equals(Object) method would return @c true.
        /// This is the definition of lexicographic ordering.
        /// If two strings are different, then either they have different characters at some index that is a valid index for both strings, or their lengths are different, or both.
        /// If they have different characters at one or more index positions, let @a k be the smallest such index; then the string whose character at position @a k has the smaller value, as determined by using the @c < operator, lexicographically precedes the other string.
        /// In this case, @c compareTo returns the difference of the two character values at position @c k in the two strings -- that is, the value: @code this.charAt(k) - other.charAt(k)@endcode.
        /// If there is no index position at which they differ, then the shorter string lexicographically precedes the longer string. In this case, @c compareTo returns the difference of the lengths of the strings -- that is, the value: @code this.length() - other.length() @endcode
        /// For finer-grained String comparison, refer to @c core.text::Collator.
        /// @param other the @c String to be compared.
        /// @return Value @c 0 if the argument string is equal to this string; a value less than @c 0 if this string is lexicographically less than the string argument; and a value greater than @c 0 if this string is lexicographically greater than the string argument.
        gint compareTo(const String& other) const override;

        /// Compares two strings lexicographically, ignoring case differences.
        /// This method returns an integer whose sign is that of calling @c compareTo with case folded versions of the strings where case differences have been eliminated by calling @code Character::toLowerCase(Character::toUpperCase(int)) @endcode on each Unicode code point.
        /// Note that this method does <em>not</em> take locale into account, and will result in an unsatisfactory ordering for certain locales.
        /// The @c core.text::Collator class provides locale-sensitive comparison.
        /// @param other the @c String to be compared.
        /// @return A negative integer, zero, or a positive integer as the specified String is greater than, equal to, or less than this String, ignoring case considerations.
        gint compareToIgnoreCase(const String& other) const;

        /// Tests if the substring of this string beginning at the specified index starts with the specified prefix.
        /// @param prefix The prefix
        /// @param offset The index where to begin looking in this string. By default, it is equals to zero
        /// @return The value @c true if the character sequence represented by the argument is a prefix of the substring of this object starting at index @c offset; @c false otherwise.
        ///                The result is @c false if @c offset is  negative or greater than the length of this @c String object; otherwise the result is the same as the result of the expression @code this.substring(offset).startsWith(prefix)@endcode .
        gboolean startsWith(const String& prefix, gint offset = 0) const;

        /// Tests if this string ends with the specified suffix.
        /// @param suffix The suffix
        /// @return The value @c true if the character sequence represented by the argument is a suffix of the character sequence represented by this object; @c false otherwise.
        ///                 Note that the result will be @c true if the argument is the empty string or is equal to this @c String object as determined by the @c equals(Object) method.
        gboolean endsWith(const String& suffix) const;

        /// Returns a hash code for this string.
        /// The hash code for a @c String object is computed as @code s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1] @endcode using @c int arithmetic, where @code s[k] @endcode is the @em k th character of the string, @c n is the length of he strings, and @c ^ indicates exponentiation.
        /// @note The hash value of the empty string is zero.
        /// @return a hash code value for this object.
        gint hash() const override;

        /// Returns the index within this string of the first occurrence of the specified character, starting the search at the specified index.
        /// If a character with value @c ch occurs in the character sequence represented by this @c String object at an index no smaller than @c from index, then the index of the first such occurrence is returned.
        /// For values of @c ch in the range from 0 to 0xFFFF (inclusive), this is the smallest value @em k such that: @code (this.charAt(k) == ch) && (k >= from) @endcode is true.
        /// For other values of @c ch, it is the smallest value @em k such that: @code (this.codePointAt(k) == ch) && (k >= from) @endcode is true.
        /// In either case, if no such character occurs in this string at or after position @c from, then @c -1 is returned.
        /// There is no restriction on the value of @c from. If it is negative, it has the same effect as if it were zero: this entire string may be searched.
        /// If it is greater than the length of this string, it has the same effect as if it were equal to the length of this string: @c -1 is returned.
        /// All indices are specified in characters values (Unicode code units).
        /// @param ch A character (Unicode code point).
        /// @param from The index to start the search from. By default, it is equals to zero
        /// @return The index of the first occurrence of the character in the character sequence represented by this object that is greater than or equal to @c from, or @c -1 if the character does not occur.
        gint indexOf(gint ch, gint from = 0) const;

        /// Returns the index within this string of the last occurrence of the specified character, searching backward starting at the specified index.
        /// For values of @c ch in the range from 0 to 0xFFFF (inclusive), the index returned is the largest value @em k such that @code (this.charAt(k) == ch) && (k <= from) @endcode is true.
        /// For other values of @c ch, it is the largest value @em k such that @code (this.codePointAt(k) == ch) && (k <= from) @endcode is true.
        /// In either case, if no such character occurs in this string at or before position @c from, then @c -1 is returned.
        /// All indices are specified in character values (Unicode code units).
        /// @param ch A character (Unicode code point).
        /// @param from the index to start the search from (by default is equals to last character index).
        ///               There is no restriction on the value of @c from.
        ///               If it is greater than or equal to the length of this string, it has the same effect as if it were equal to one less than the length of this string: this entire string may be searched.
        ///               If it is negative, it has the same effect as if it were -1, -1 is returned.
        /// @return The index of the last occurrence of the character in the character sequence represented by this object that is less than or equal to @c fromIndex, or @c -1 if the character does not occur before that point.
        gint lastIndexOf(gint ch, gint from = Integer::MAX_VALUE) const;

        /// Returns the index within this string of the first occurrence of the specified substring, starting at the specified index.
        /// The returned index is the smallest value @c k for which @code k >= Math.min(from, this.length()) && this.startsWith(str, k)@endcode .
        /// If no such value of @c k exists, then @c -1 is returned.
        /// @param str The substring to search for.
        /// @param offset the index from which to start the search. By default, is equals to zero
        /// @return The index of the first occurrence of the specified substring, starting at the specified index, or @c -1 if there is no such occurrence.
        gint indexOf(const String& str, gint offset = 0) const;

        /// Returns the index within this string of the last occurrence of the specified substring, searching backward starting at the specified index.
        /// The returned index is the largest value @c k for which @code k <= Math.min(from, this.length()) && this.startsWith(str, Math.min(from, this.length()) - str.length()) @endcode .
        /// If no such value of @c k exists, then @c -1 is returned.
        /// @param str The substring to search for.
        /// @param offset The index to start the search from. By default, is equals to last character index.
        /// @return The index of the last occurrence of the specified substring,
        gint lastIndexOf(const String& str, gint offset = Integer::MAX_VALUE) const;

        /// Returns a string that is a substring of this string.
        /// The substring begins at the specified @c start index and extends to the character at index @code end - 1 @endcode .
        /// Thus, the length of the substring is @code end - start @endcode .
        /// Examples:
        ///     @code
        ///         "Hamburger"_Sl.substring(4, 8) returns "urge"
        ///         "Smiles"_Sl.substring(1, 5) returns "mile"
        ///     @endcode
        /// @param start The beginning index, inclusive.
        /// @param end The ending index, exclusive.
        /// @return The specified substring.
        /// @throws IndexOutOfBoundsException  if the @c start index is negative, or @c end index is larger than the length of this @c String object, or @c start index is larger than @c end index.
        String substring(gint start, gint end) const;

        /// Returns a string that is a substring of this string.
        /// The substring begins at the specified @c start index and extends to the end of this string.
        /// Examples:
        ///     @code
        ///         "Hamburger"_Sl.substring(4) returns "urger"_Sl
        ///         "Smiles"_Sl.substring(1) returns "miles"_Sl
        ///         "Emptiness"_Sl.substring(9) returns ""_Sl (empty string)
        ///     @endcode
        /// @param start The beginning index, inclusive.
        /// @return The specified substring.
        /// @throws IndexOutOfBoundsException  if the @c start index is negative or larger than the length of this @c String object.
        String substring(gint start) const;

        /// Returns a character sequence that is a subsequence of this sequence.
        /// An invocation of this method of the form @code str.subSequence(start, end) @endcode behaves in exactly the same way as the invocation @code str.substring(start, end) @endcode
        /// @note This method is defined so that the @c String class can implement the @c CharSequence interface.
        /// @param start The beginning index, inclusive.
        /// @param end The end index, exclusive.
        /// @return The specified subsequence.
        /// @throws  IndexOutOfBoundsException If @c beginIndex or @c endIndex is negative, if @c endIndex is greater than @c length(), or if @c beginIndex is greater than @c endIndex
        CharSequence& subSequence(gint start, gint end) const override;

        /// Concatenates the specified string to the end of this string.
        /// If the length of the argument string is @c 0, then this @c String object is returned.
        /// Otherwise, a @c String object is returned that represents a character sequence that is the concatenation of the character sequence represented by this @c String object and the character sequence represented by the argument string.
        /// Examples:
        ///     @code
        ///         "Cares"_Sl.concat("s") returns "Caress"
        ///         "To"_Sl.concat("get").concat("her") returns "Together"
        ///     @endcode
        /// @param other
        /// @return
        String concat(const String& other) const;

        ///  Returns a string resulting from replacing all occurrences of @c oldCh in this string with @c newCh.
        ///  If the character @c oldCh does not occur in the character sequence represented by this @c String object, then a reference to this @c String object is returned.
        ///  Otherwise, a @c String object is returned that represents a character sequence identical to the character sequence represented by this @c String object, except that every occurrence of @c oldCh is replaced by an occurrence of @c newCh.
        ///  Examples:
        ///         @code
        ///             "Mesquite in your cellar"_Sl.replace('e', 'o') returns "Mosquito in your collar"
        ///             "The war of baronets"_Sl.replace('r', 'y') returns "The way of bayonets"
        ///             "Sparring with a purple porpoise"_Sl.replace('p', 't') returns "Starring with a turtle tortoise"
        ///             "JonL"_Sl.replace('q', 'x') returns "JonL" // (no change)
        ///         @endcode
        /// @param oldCh The old character
        /// @param newCh The new character
        /// @return A string derived from this string by replacing every occurrence of @c oldCh with @c newCh.
        String replace(gchar oldCh, gchar newCh) const;

        ///  Replaces each substring of this string that matches the literal target sequence with the specified literal replacement sequence.
        ///  The replacement proceeds from the beginning of the string to the end, for example, replacing "aa" with "b" in the string "aaa" will result in "ba" rather than "ab".
        /// @param target The sequence of char values to be replaced
        /// @param replacement The replacement sequence of char values
        /// @return The resulting string
        String replace(const CharSequence& target, const CharSequence& replacement) const;

        /// This object (which is already a string!) is itself returned.
        /// @return itself
        String toString() const override;

        /// Returns the string representation of the @c Object argument.
        /// @param obj An object
        /// @return if the argument is @c null, then a string equal to @c "null"; otherwise, the value of @c obj.toString() is returned.
        static String valueOf(const Object& obj);

        Object& clone() const override;

    private:
        /// Initialise this string with primal string (pointer).
        /// The @c coder value is used to decode the input string.
        ///  - If coder == 1, the primal string is considered as string encoded to Utf-8
        ///  - If coder == 2, the primal string is considered as string encoded to Utf-16
        ///  - If coder == 4, the primal string is considered as string encoded to Utf-32
        /// @param primalString The address of primalString
        /// @param length The length in bytes of input string
        /// @param coder The value that indicate the @c log2 of size of one character in input
        /// @throws IllegalArgumentException If the address of primal string invalid or null
        void initializeFromPrimalString(glong primalString, glong length, gint coder);

        static Object& newFormatter();
        static String doFormatting(Object& formatter);
        static gint addFormatterArg(Object& formatter, const Object& arg);
        static gint addFormatterArg(Object& formatter, gboolean arg);
        static gint addFormatterArg(Object& formatter, gbyte arg);
        static gint addFormatterArg(Object& formatter, gshort arg);
        static gint addFormatterArg(Object& formatter, gint arg);
        static gint addFormatterArg(Object& formatter, glong arg);
        static gint addFormatterArg(Object& formatter, gfloat arg);
        static gint addFormatterArg(Object& formatter, gdouble arg);
    };
} // core

#endif // CORE_LANG_STRING_H
