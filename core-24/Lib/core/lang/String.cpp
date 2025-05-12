//
// Created by brunshweeck on 4/17/25.
//

#include "String.h"

#include <meta/lang/Strings.h>

#include "ByteArray.h"
#include "CharArray.h"
#include "Error.h"
#include "Exception.h"
#include "IllegalArgumentException.h"
#include "IndexOutOfBoundsException.h"
#include "IntArray.h"
#include "Null.h"
#include "OutOfMemoryError.h"
#include "Preconditions.h"

namespace core
{
    namespace lang
    {
        static CORE_FAST spi::__int32_t _val = 0x07FF;
        static CORE_FAST spi::__int8_t _val1 = (gbyte) (0xc0 | _val >> 6);
        static CORE_FAST spi::__int8_t _val2 = (gbyte) (0x80 | _val & 0x3f);
        static CORE_FAST const spi::__literal_char8_t *_8 = "\u0080";
        static CORE_FAST const spi::__literal_char16_t *_16 = u"\u07FF";
        static CORE_FAST const spi::__literal_char32_t *_32 = U"\u07FF";
        static CORE_FAST const spi::__literal_varchar_t *_var = L"\u07FF";
    }

    inline namespace literals
    {
        using lang::Strings;

        String operator ""_S(lang::spi::__literal_char8_t const input[], lang::spi::__uint64_t count) {
            try {
                static CORE_FAST gboolean UsingUtf8Decoder = lang::_8[0] != lang::_val1 || lang::_8[1] != lang::_val2;
                if (UsingUtf8Decoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception &ex) { ex.throws($ftrace()); }
            catch (const lang::Error &err) { err.throws($ftrace()); }
        }

        String operator ""_S(lang::spi::__literal_char16_t const input[], lang::spi::__uint64_t count) {
            try {
                static CORE_FAST gboolean UsingUtf16Decoder = lang::_16[0] == lang::_val;
                if (UsingUtf16Decoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception &ex) { ex.throws($ftrace()); }
            catch (const lang::Error &err) { err.throws($ftrace()); }
        }

        String operator ""_S(lang::spi::__literal_char32_t const input[], lang::spi::__uint64_t count) {
            try {
                static CORE_FAST gboolean UsingUtf32Decoder = lang::_32[0] == lang::_val;
                if (UsingUtf32Decoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception &ex) { ex.throws($ftrace()); }
            catch (const lang::Error &err) { err.throws($ftrace()); }
        }

        String operator ""_S(lang::spi::__literal_varchar_t const input[], lang::spi::__uint64_t count) {
            try {
                static CORE_FAST gboolean UsingUnicodeDecoder = lang::_var[0] == lang::_val;
                if (UsingUnicodeDecoder) return operator ""_Su(input, count);
                return operator ""_Sl(input, count);
            }
            catch (const lang::Exception &ex) { ex.throws($ftrace()); }
            catch (const lang::Error &err) { err.throws($ftrace()); }
        }

        String operator ""_Sl(lang::spi::__literal_char8_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            // if (input[count] != 0)
            //     IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                ByteArray bytes = ByteArray(length);
                for (gint i = 0; i < length; ++i) bytes[i] = (gbyte) (input[i] & 0xff);
                return String(bytes, 0, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
        }

        String operator ""_Sl(lang::spi::__literal_char16_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            if (input[count] != 0)
                IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                ByteArray bytes = ByteArray(length);
                for (gint i = 0; i < length; ++i) bytes[i] = (gbyte) (input[i] & 0xff);
                return String(bytes, 0, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
        }

        String operator ""_Sl(lang::spi::__literal_char32_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            if (input[count] != 0)
                IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                ByteArray bytes = ByteArray(length);
                for (gint i = 0; i < length; ++i) bytes[i] = (gbyte) (input[i] & 0xff);
                return String(bytes, 0, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
        }

        String operator ""_Sl(lang::spi::__literal_varchar_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            if (input[count] != 0)
                IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                ByteArray bytes = ByteArray(length);
                for (gint i = 0; i < length; ++i) bytes[i] = (gbyte) (input[i] & 0xff);
                return String(bytes, 0, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
        }

        String operator ""_Su(lang::spi::__literal_char8_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            if (input[count] != 0)
                IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                CharArray chars = CharArray(length);
                length = Strings::decodeUtf8Chars((Strings::Bytes) input, 0, length, chars, 0, length);
                return String(chars, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
            catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        }

        String operator ""_Su(lang::spi::__literal_char16_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            if (input[count] != 0)
                IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                CharArray chars = CharArray(length);
                for (int i = 0; i < length; ++i) chars[i] = input[i];
                return String(chars, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
            catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        }

        String operator ""_Su(lang::spi::__literal_char32_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            if (input[count] != 0)
                IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                IntArray codePoints = IntArray(length);
                for (int i = 0; i < length; ++i) codePoints[i] = input[i];
                return String(codePoints, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
            catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        }

        String operator ""_Su(lang::spi::__literal_varchar_t const input[], lang::spi::__uint64_t count) {
            if (count > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Literal length exceeds implementation limit)).throws($ftrace());
            if (input == null)
                IllegalArgumentException($toString(Literal string is null pointer)).throws($ftrace());
            // if (input[count] != 0)
            //     IllegalArgumentException($toString(Non Literal string)).throws($ftrace());
            if (count == 0L) return String();
            try {
                gint length = (gint) count;
                $alias(Array, Class<CharArray>::IfOrElse<ClassOf(input[0])::SIZE == 2, IntArray>);
                Array data = Array(length);
                for (int i = 0; i < length; ++i) data[i] = input[i];
                return String(data, 0, length);
            }
            catch (const OutOfMemoryError &oome) { oome.throws($ftrace()); }
            catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        }
    }

    String::String(const String &original) {
        count = original.length();
        coder = original.encoding();
        lastHash = original.lastHash;
        zeroHashed = original.zeroHashed;
        if (coder == Latn1)
            value = Strings::copyOfLatn1Bytes(original.value, 0, count, count);
        else
            value = Strings::copyOfUtf16Bytes(original.value, 0, count, count);
    }

    String::String(String &&original) CORE_NOTHROW {
        if (this != &original) {
            Strings::swap(value, original.value);
            Strings::swap(count, original.count);
            Strings::swap(coder, original.coder);
            Strings::swap(lastHash, original.lastHash);
            Strings::swap(zeroHashed, original.zeroHashed);
        }
    }

    String::String(const CharArray &chars) {
        count = chars.length();
        coder = Latn1;
        value = Strings::tryConvertCharsToLatn1(chars, 0, count);
        if (value == null) {
            coder = Utf16;
            value = Strings::convertCharsToUtf16(chars, 0, count);
        }
    }

    String::String(const CharArray &chars, gint offset, gint count) {
        try {
            Preconditions::checkIndexFromSize(offset, count, chars.length());
        }
        catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        String::count = count;
        coder = Latn1;
        value = Strings::tryConvertCharsToLatn1(chars, offset, count);
        if (value == null) {
            coder = Utf16;
            value = Strings::convertCharsToUtf16(chars, offset, count);
        }
    }

    String::String(const IntArray &codePoints, gint offset, gint count) {
        String::count = count;
        coder = Latn1;
        value = Strings::tryConvertCodePointsToLatin1(codePoints, offset, count);
        if (value == null) {
            coder = Utf16;
            gint length = 0;
            for (int i = 0; i < count; ++i) {
                gint chr = codePoints[i];
                length += chr > 0xffff && chr <= 0x10ffff ? 2 : 1;
            }
            if (length < 0)
                OutOfMemoryError($toString(Required string length exceed implementation limit)).throws($ftrace());
            String::count = length;
            CharArray chars = CharArray(length);
            for (int i = 0, j = 0; i < count; ++i) {
                gint chr = codePoints[i];
                if (chr < 0 || chr > 0x10ffff) {
                    chars[j++] = 0xFFFD;
                    continue;
                }
                if (chr > 0xffff) {
                    chars[j++] = (chr >> 10) + 0xD800 - (0x10000 >> 10);
                    chars[j++] = (chr & 0x3ff) + 0xDC00;
                    continue;
                }
                chars[j++] = chr & 0xffff;
            }
            value = Strings::convertCharsToUtf16(chars, 0, length);
        }
    }

    String::String(const ByteArray &ascii, gint hiByte, gint offset, gint count) {
        try {
            Preconditions::checkIndexFromSize(offset, count, ascii.length());
        }
        catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        String::count = count;
        hiByte = hiByte << 8 & 0xff00;
        if (hiByte == 0 && UsingCompactString) {
            coder = Latn1;
            value = Strings::newLatin1Bytes(count);
            for (int i = 0; i < count; ++i) Strings::putLatn1CharAt(value, i, ascii[i + offset] & 0xff, count);
        }
        else {
            coder = Utf16;
            value = Strings::newUtf16Bytes(count);
            for (int i = 0; i < count; ++i) Strings::putUtf16CharAt(value, i, hiByte | ascii[i + offset] & 0xff, count);
        }
    }

    String::String(const ByteArray &ascii, gint hiByte) {
        count = ascii.length();
        hiByte = hiByte << 8 & 0xff00;
        if (hiByte == 0 && UsingCompactString) {
            coder = Latn1;
            value = Strings::newLatin1Bytes(count);
            for (int i = 0; i < count; ++i) Strings::putLatn1CharAt(value, i, ascii[i] & 0xff, count);
        }
        else {
            coder = Utf16;
            value = Strings::newUtf16Bytes(count);
            for (int i = 0; i < count; ++i) Strings::putUtf16CharAt(value, i, hiByte | ascii[i] & 0xff, count);
        }
    }

    String::String(const ByteArray &bytes, gint offset, gint count) {
        gint length = bytes.length();
        try {
            Preconditions::checkIndexFromSize(offset, count, length);
        }
        catch (const IndexOutOfBoundsException &ioobe) { ioobe.throws($ftrace()); }
        // todo: implementer cette method en prenant en charge l'encodage par default pour cette conversion
        CharArray chars = CharArray(count);
        length = Strings::decodeUtf8Chars(bytes, offset, length, chars, 0, count);
        String::count = length;
        coder = Latn1;
        value = Strings::tryConvertCharsToLatn1(chars, 0, length);
        if (value == null) {
            coder = Utf16;
            value = Strings::convertCharsToUtf16(chars, 0, length);
        }
    }

    String::String(const ByteArray &bytes) {
        gint length = bytes.length();
        // todo: implementer cette method en prenant en charge l'encodage par default pour cette conversion
        CharArray chars = CharArray(length);
        length = Strings::decodeUtf8Chars(bytes, 0, length, chars, 0, length);
        count = length;
        coder = Latn1;
        value = Strings::tryConvertCharsToLatn1(chars, 0, length);
        if (value == null) {
            coder = Utf16;
            value = Strings::convertCharsToUtf16(chars, 0, length);
        }
    }

    String::~String() {
        Bytes bytes = value;
        gint length = count;
        count = {};
        coder = {};
        lastHash = {};
        zeroHashed = {};
        value = {};
        if (length > 0 || bytes != null) Strings::deleteBytes(bytes, length);
    }

    String &String::operator=(const String &other) {
        if (this != &other) {
            gint coder = other.encoding();
            gint count = other.length();
            gint hash = other.lastHash;
            Bytes bytes = (coder == Latn1)
                              ? Strings::copyOfLatn1Bytes(other.value, 0, count, count)
                              : Strings::copyOfUtf16Bytes(other.value, 0, count, count);
            String::~String();
            String::count = count;
            String::coder = coder;
            lastHash = hash;
            zeroHashed = hash == 0;
            value = bytes;
        }
        return *this;
    }

    String &String::operator=(String &&other) CORE_NOTHROW {
        if (this != &other) {
            Strings::swap(value, other.value);
            Strings::swap(count, other.count);
            Strings::swap(coder, other.coder);
            Strings::swap(lastHash, other.lastHash);
            Strings::swap(zeroHashed, other.zeroHashed);
        }
        return *this;
    }

    gint String::length() const { return count; }

    gboolean String::isEmpty() const { return length() == 0 || !value; }

    gchar String::charAt(gint index) const {
        Strings::checkIndex(index, count);
        return (coder == Latn1)
                   ? Strings::getLatin1CharAt(value, index, count)
                   : Strings::getUtf16CharAt(value, index, count);
    }

    gint String::codePointAt(gint index) const {
        Strings::checkIndex(index, count);
        return (coder == Latn1)
                   ? Strings::getLatin1CodePointAt(value, index, count)
                   : Strings::getUtf16CodePointAt(value, index, count);
    }

    gint String::codePointCount(gint start, gint end) const {
        Strings::checkIndexFromRange(start, end, count);
        return (coder == Latn1)
                   ? Strings::countLatin1CodePoint(value, 0, count)
                   : Strings::countUtf16CodePoint(value, 0, count);
    }

    void String::toChars(gint start, gint end, CharArray &dest, gint offset) const {
        Strings::checkIndexFromRange(start, end, count);
        Preconditions::checkIndexFromSize(offset, end - start, dest.length());
        if (coder == Latn1)
            for (int i = 0, n = end - start; i < n; ++i)
                dest[i + offset] = Strings::getLatin1CharAt(value, i + start, count);
        else
            for (int i = 0, n = end - start; i < n; ++i)
                dest[i + offset] = Strings::getUtf16CharAt(value, i + start, count);
    }

    void String::toBytes(gint start, gint end, ByteArray &dest, gint offset) const {
        Strings::checkIndexFromRange(start, end, count);
        Preconditions::checkIndexFromSize(offset, end - start, dest.length());
        if (coder == Latn1)
            for (int i = 0, n = end - start; i < n; ++i)
                dest[i + offset] = Strings::getLatin1CharAt(value, i + start, count);
        else
            for (int i = 0, n = end - start; i < n; ++i)
                dest[i + offset] = Strings::getUtf16CharAt(value, i + start, count) & 0xff;
    }

    ByteArray String::toBytes() const {
        return (coder == Latn1)
                   ? Strings::encodeLatn1ToUtf8Bytes(value, 0, count)
                   : Strings::encodeUtf16ToUtf8Bytes(value, 0, count);
    }

    gboolean String::equals(const Object &other) const {
        if (this == &other) return true;
        if (!Class<String>::hasInstance(other)) return false;
        const String &otherString = $cast(const String&, other);
        if (count != otherString.count || coder != otherString.coder) return false;
        gint index = (coder == Latn1)
                         ? Strings::mismatchLatin1Bytes(value, 0, otherString.value, 0, count)
                         : Strings::mismatchUtf16Bytes(value, 0, otherString.value, 0, count);
        return index < 0;
    }

    gboolean String::contentEquals(const CharSequence &csq) const {
        if (this == &csq) return true;
        if (!Class<String>::hasInstance(csq)) {
            gint length = csq.length();
            if (count != length) return false;
            for (int i = 0; i < length; ++i) if (csq.charAt(i) != charAt(i)) return false;
            return true;
        }
        const String &otherString = $cast(const String&, csq);
        if (count != otherString.count || coder != otherString.coder) return false;
        gint index = (coder == Latn1)
                         ? Strings::mismatchLatin1Bytes(value, 0, otherString.value, 0, count)
                         : Strings::mismatchUtf16Bytes(value, 0, otherString.value, 0, count);
        return index < 0;
    }

    gboolean String::equalsIgnoreCase(const String &other) const {
        // todo: implementer cette method apres avoir implementer la classe core::Character
        return equals(other);
    }

    gint String::compareTo(const String &other) const {
        gint meanCount = count < other.count ? count : other.count;
        gint index = (coder == Latn1)
                         ? Strings::mismatchLatin1Bytes(value, 0, other.value, 0, meanCount)
                         : Strings::mismatchUtf16Bytes(value, 0, other.value, 0, meanCount);
        return index < 0 ? count - other.count : charAt(index) - other.charAt(index);
    }

    gint String::compareToIgnoreCase(const String &other) const {
        // todo: implementer cette method apres avoir implementer la classe core::Character
        return compareTo(other);
    }

    gboolean String::startsWith(const String &prefix, gint offset) const {
        // todo: implementer cette method apres avoir implementer la classe core::Character
        if (offset < 0) offset = 0;
        if (offset + prefix.count > count) return false;
        if (coder == prefix.coder) {
            if (coder == Latn1)
                return Strings::findLatin1Bytes(value, offset, offset + prefix.count,
                                                prefix.value, prefix.count, false) == 0;
            return Strings::findUtf16Bytes(value, offset, offset + prefix.count,
                                           prefix.value, prefix.count, false) == 0;
        }
        if (coder == Latn1)
            return false;
        return Strings::findLatin1IntoUtf16Bytes(value, offset, offset + prefix.count,
                                                 prefix.value, prefix.count, false) == 0;
    }

    gboolean String::endsWith(const String &suffix) const {
        return startsWith(suffix, count - suffix.count);
    }

    gint String::hash() const {
        gint hash = lastHash;
        if (hash == 0 && !zeroHashed)
            for (int i = 0; i < count; ++i)
                hash = hash * 31 + charAt(i);
        zeroHashed = (lastHash = hash) == 0;
        return hash;
    }

    gint String::indexOf(gint ch, gint from) const {
        if (ch < 0 || ch > 0x10ffff) return -1;
        if (from < 0) from = 0;
        if (from >= count) return -1;
        return ch > 0xffff
                   ? (coder == Latn1)
                         ? Strings::findLatin1CodePoint(value, from, count, ch, false)
                         : Strings::findUtf16CodePoint(value, from, count, ch, false)
                   : (coder == Latn1)
                         ? Strings::findLatin1Char(value, from, count, ch, false)
                         : Strings::findUtf16Char(value, from, count, ch, false);
    }

    gint String::lastIndexOf(gint ch, gint from) const {
        if (ch < 0 || ch > 0x10ffff) return -1;
        if (from > count) from = count;
        if (from < 0) return -1;
        return ch > 0xffff
                   ? (coder == Latn1)
                         ? Strings::findLatin1CodePoint(value, from, count, ch, true)
                         : Strings::findUtf16CodePoint(value, from, count, ch, true)
                   : (coder == Latn1)
                         ? Strings::findLatin1Char(value, from, count, ch, true)
                         : Strings::findUtf16Char(value, from, count, ch, true);
    }

    gint String::indexOf(const String &str, gint offset) const {
        if (offset < 0) offset = 0;
        if (offset + str.count >= count) return -1;
        if (str.isEmpty()) return offset;
        return (coder == str.coder)
                   ? (coder == Latn1)
                         ? Strings::findLatin1Bytes(value, offset, count, str.value, str.count, false)
                         : Strings::findUtf16Bytes(value, offset, count, str.value, str.count, false)
                   : (coder == Latn1)
                         ? -1
                         : Strings::findLatin1IntoUtf16Bytes(value, offset, count, str.value, str.count, false);
    }

    gint String::lastIndexOf(const String &str, gint offset) const {
        if (offset < 0) return -1;
        if (offset > count) offset = count - 1;
        if (offset - str.count < -1) return -1;
        if (str.isEmpty()) return offset;
        return (coder == str.coder)
                   ? (coder == Latn1)
                         ? Strings::findLatin1Bytes(value, offset, count, str.value, str.count, true)
                         : Strings::findUtf16Bytes(value, offset, count, str.value, str.count, true)
                   : (coder == Latn1)
                         ? -1
                         : Strings::findLatin1IntoUtf16Bytes(value, offset, count, str.value, str.count, true);
    }

    String String::substring(gint start, gint end) const {
        Strings::checkIndexFromRange(start, end, count);
        String output;
        output.coder = coder;
        output.count = end - start;
        if (coder == Latn1)
            output.value = Strings::copyOfLatn1Bytes(value, start, output.count, output.count);
        else {
            output.coder = Latn1;
            output.value = Strings::tryConvertUtf16BytesToLatin1(value, start, output.count);
            if (output.value == null) {
                output.coder = Utf16;
                output.value = Strings::copyOfUtf16Bytes(value, start, output.count, output.count);
            }
        }
        return output;
    }

    String String::substring(gint start) const {
        return substring(start, count);
    }

    lang::CharSequence &String::subSequence(gint start, gint end) const {
        return substring(start, end).clone();
    }

    String String::concat(const String &other) const {
        gint newCount = count + other.count;
        if (newCount < 0)
            OutOfMemoryError($toString(Required length exceed implementation limit)).throws($ftrace());
        String output;
        output.coder = coder | other.coder;
        output.count = newCount;
        if (output.coder == Latn1) {
            output.value = Strings::copyOfLatn1Bytes(value, 0, count, newCount);
            Strings::copyLatin1Bytes(other.value, 0, output.value, count, other.count);
        }
        else {
            output.value = (coder == Latn1)
                               ? Strings::copyOfLatn1Bytes(value, 0, count, newCount)
                               : Strings::copyOfUtf16Bytes(value, 0, count, newCount);
            output.value = (other.coder == Latn1)
                               ? Strings::copyLatin1ToUtf16Bytes(other.value, 0, output.value, count, other.count)
                               : Strings::copyUtf16Bytes(other.value, 0, output.value, count, other.count);
        }
        return output;
    }

    String String::replace(gchar oldCh, gchar newCh) const {
        gint index = 0;
        for (; index < count; ++index) if (oldCh == charAt(index)) break;
        if (index < count) {
            String output;
            output.count = count;
            if (coder == Latn1) {
                if (newCh < 0x80) {
                    output.coder = Latn1;
                    output.value = Strings::copyOfLatn1Bytes(value, 0, count, count);
                    for (; index < output.count; ++index) {
                        gchar ch = Strings::getLatin1CharAt(value, index, count);
                        if (oldCh == ch) Strings::putLatn1CharAt(output.value, index, ch, output.count);
                    }
                }
                else {
                    output.coder = Utf16;
                    output.value = Strings::copyOfLatin1ToUtf16Bytes(value, 0, count, count);
                    for (; index < output.count; ++index) {
                        gchar ch = Strings::getLatin1CharAt(value, index, count);
                        if (oldCh == ch) Strings::putUtf16CharAt(output.value, index, ch, output.count);
                    }
                }
            }
            else {
                output.coder = Utf16;
                output.value = Strings::copyOfUtf16Bytes(value, 0, count, count);
                for (; index < output.count; ++index) {
                    gchar ch = Strings::getUtf16CharAt(value, index, count);
                    if (oldCh == ch) Strings::putUtf16CharAt(output.value, index, ch, output.count);
                }
            }
            return output;
        }
        return *this;
    }

    String String::replace(const CharSequence &target, const CharSequence &replacement) const {
        if (count == 0) return *this;
        gint replCount = replacement.length();
        gint targetCount = target.length();
        if (targetCount == 0) {
            glong newCount = (count + 1LL) * replCount + count;
            if (newCount > Integer::MAX_VALUE)
                OutOfMemoryError($toString(Required length exceed implementation limit)).throws($ftrace());
            // todo: Finish this implementation
        }

        return *this;
    }

    String String::toString() const { return *this; }

    String String::valueOf(const Object &obj) { return obj.toString(); }

    String &String::clone() const { return *new String(*this); }

    gint String::encoding() const { return UsingCompactString ? coder : Utf16; }

    void String::initializeFromPrimalString(glong primalString, glong length, gint coder) {
        if (primalString == 0L || length == -1L)
            IllegalArgumentException($toString(CString is null pointer)).throws($ftrace());
        if (length > Integer::MAX_VALUE || length < 0L)
            OutOfMemoryError($toString(Required length exceed implementation limit)).throws($ftrace());
        if (coder < 0 || coder > 3)
            IllegalArgumentException($toString(Unsupported CString encoding)).throws($ftrace());
        CharArray chars = CharArray(length);
        switch (coder) {
            case 0: // Utf8
                count = Strings::decodeUtf8Chars((Bytes) primalString, 0, length, chars, 0, length);
                String::coder = Latn1;
                value = Strings::tryConvertCharsToLatn1(chars, 0, length);
                if (value == null) {
                    String::coder = Utf16;
                    value = Strings::convertCharsToUtf16(chars, 0, length);
                }
                break;
            case 1: // Utf16
                count = length;
                String::coder = Latn1;
                value = Strings::tryConvertUtf16BytesToLatin1((Bytes) primalString, 0, length);
                if (value == null) {
                    String::coder = Utf16;
                    value = Strings::copyOfUtf16Bytes((Bytes) primalString, 0, length, length);
                }
                break;
            default: // Utf32
                count = length;
                String::coder = Latn1;
                value = Strings::tryConvertUtf32BytesToLatin1((Bytes) primalString, 0, length);
                if (value == null) {
                    chars.~CharArray();
                    glong count = 0;
                    for (int i = 0; i < length; ++i) {
                        gint chr = Strings::getUtf32CharAt((Bytes) primalString, 0, length);
                        count += (chr <= 0xffff || chr > 0x10ffff) ? 1 : 2;
                    }
                    if (count > Integer::MAX_VALUE)
                        OutOfMemoryError($toString(Required length exceed implementation limit)).throws($ftrace());
                    String::coder = Utf16;
                    String::count = (gint) count;
                    value = Strings::copyOfUtf32ToUtf16Bytes((Bytes) primalString, 0, length, count);
                }
                break;
        }
    }
} // core
