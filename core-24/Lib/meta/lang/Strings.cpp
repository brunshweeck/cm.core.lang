//
// Created by brunshweeck on 01/05/25.
//

#include "Strings.h"

#include <core/lang/Null.h>
#include <core/lang/OutOfMemoryError.h>

#include "core/lang/AssertionError.h"
#include "core/lang/CharArray.h"
#include "core/lang/IntArray.h"

namespace core::lang
{
    Strings::Bytes Strings::newLatin1Bytes(gint count) {
        try {
            return newBytes(count, LATIN1);
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    Strings::Bytes Strings::copyLatin1Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count) {
        if ((bytes == null) || (dest == null) || (bytes == dest) && (start1 == start2) || count <= 0) return dest;
        if ((bytes == dest) && (start1 < start2) && (start2 - start1 <= count))
            for (int i = count - 1; i >= 0; --i) dest[start2 + i] = bytes[start1 + i];
        else
            for (int i = 0; i < count; ++i) dest[start2 + i] = bytes[start1 + i];
        return dest;
    }

    Strings::Bytes Strings::copyUtf16Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count) {
        Chars input = (Chars)bytes;
        Chars output = (Chars)dest;
        if ((input == null) || (output == null) || (input == output) && (start1 == start2) || count <= 0) return dest;
        if ((input == output) && (start1 < start2) && (start2 - start1 <= count))
            for (int i = count - 1; i >= 0; --i) output[start2 + i] = input[start1 + i];
        else
            for (int i = 0; i < count; ++i) output[start2 + i] = input[start1 + i];
        return dest;
    }

    Strings::Bytes Strings::copyOfLatin1Bytes(Bytes bytes, gint start, gint count, gint newCount) {
        try {
            Bytes copy = newLatin1Bytes(newCount);
            if (newCount < count) count = newCount;
            return copyLatin1Bytes(bytes, start, copy, 0, count);
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    Strings::Bytes Strings::copyOfUtf16Bytes(Bytes bytes, gint start, gint count, gint newCount) {
        try {
            Bytes copy = newUtf16Bytes(newCount);
            if (newCount < count) count = newCount;
            return copyUtf16Bytes(bytes, start, copy, 0, count);
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    gchar Strings::getLatin1CharAt(Bytes bytes, gint index, gint count) {
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return (gchar)(bytes[index] & 0xff);
    }

    gchar Strings::getUtf16CharAt(Bytes bytes, gint index, gint count) {
        Chars input = (Chars)bytes;
        if (input == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return input[index];
    }

    gint Strings::getLatin1CodePointAt(Bytes bytes, gint index, gint count) {
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return bytes[index] & 0xff;
    }

    gint Strings::getUtf16CodePointAt(Bytes bytes, gint index, gint count) {
        Chars input = (Chars)bytes;
        if (input == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        gchar chr = input[index];
        if (0xD800 <= chr && chr <= 0xDBFF && index + 1 < count) {
            gchar chr2 = input[index + 1];
            if (0xDC00 <= chr2 && chr2 <= 0xDFFF)
                return ((chr - 0xD800) << 10) + (chr2 - 0xDC00) + 0x10000;
        }
        return chr;
    }

    Strings::Bytes Strings::fillLatin1Bytes(Bytes bytes, gint start, gbyte value, gint count) {
        if ((bytes == null) || (start < 0) || (count <= 0)) return bytes;
        for (int i = 0; i < count; ++i) bytes[start + i] = value;
        return bytes;
    }

    Strings::Bytes Strings::fillUtf16Bytes(Bytes bytes, gint start, gchar value, gint count) {
        Chars input = (Chars)bytes;
        if ((input == null) || (start < 0) || (count <= 0)) return bytes;
        for (int i = 0; i < count; ++i) input[start + i] = value;
        return bytes;
    }

    Strings::Bytes Strings::tryConvertUtf16BytesToLatin1(Bytes bytes, gint start, gint count) {
        if ((bytes == null) || (start < 0) || (count <= 0)) return null;
        try {
            Bytes copy = newLatin1Bytes(count);
            for (int i = 0; i < count; ++i) {
                gchar chr = getUtf16CharAt(bytes, start + i, count);
                if (chr > 0xff) {
                    deleteBytes(copy, count);
                    return null;
                }
                copy[i] = (gbyte)chr;
            }
            return copy;
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    Strings::Bytes Strings::tryConvertCharsToLatin1(const CharArray& chars, gint start, gint count) {
        if (start < 0 || count <= 0) return null;
        try {
            Bytes copy = newLatin1Bytes(count);
            for (int i = 0; i < count; ++i) {
                gchar chr = chars[start + i];
                if (chr > 0xff) {
                    deleteBytes(copy, count);
                    return null;
                }
                copy[i] = (gbyte)chr;
            }
            return copy;
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    Strings::Bytes Strings::tryConvertCodePointsToLatin1(const IntArray& codePoints, gint start, gint count) {
        if (start < 0 || count <= 0) return null;
        try {
            Bytes copy = newLatin1Bytes(count);
            for (int i = 0; i < count; ++i) {
                gint chr = codePoints[start + i];
                if (chr > 0xff || chr < 0) {
                    deleteBytes(copy, count);
                    return null;
                }
                copy[i] = (gbyte)chr;
            }
            return copy;
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    gint Strings::putLatin1CharAt(Bytes bytes, gint index, gchar value, gint count) {
        if ((bytes == null) || index < 0 || count <= 0 || index >= count) return -1;
        bytes[index] = (gbyte)value;
        return 1;
    }

    gint Strings::putUtf16CharAt(Bytes bytes, gint index, gchar value, gint count) {
        Chars input = (Chars)bytes;
        if ((input == null) || index < 0 || count <= 0 || index >= count) return -1;
        input[index] = value;
        return 2;
    }

    gint Strings::putLatin1CodePoint(Bytes bytes, gint index, gint value, gint count) {
        if ((bytes == null) || index < 0 || count <= 0 || index >= count) return -1;
        if (value < 0 || value > 0x10ffff) value = 0x3f;
        bytes[index] = (gbyte)value;
        return 1;
    }

    gint Strings::putUtf16CodePoint(Bytes bytes, gint index, gint value, gint count) {
        Chars input = (Chars)bytes;
        if ((bytes == null) || index < 0 || count <= 0 || index >= count) return -1;
        if (value < 0 || value > 0x10ffff) value = 0x3f;
        if (0xD800 <= value && value <= 0xDFFF) {
            if (index + 1 >= count) return -1;
            gchar chr1 = (value >> 10) + 0xD800 - (0x10000 >> 10);
            gchar chr2 = (value & 0x3ff) + 0xDC00;
            input[index] = chr1;
            input[index + 1] = chr2;
            return 4;
        }
        input[index] = value;
        return 2;
    }

    gint Strings::findLatin1Char(Bytes bytes, gint start, gint count, gchar value, gboolean reversedSearch) {
        if (bytes == null || count <= 0 || value > 0xff) return -1;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= 0; --i) {
                gchar chr = bytes[i] & 0xff;
                if (value == chr) return i;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count; ++i) {
                gchar chr = bytes[i] & 0xff;
                if (value == chr) return i;
            }
        }
        return -1;
    }

    gint Strings::findUtf16Char(Bytes bytes, gint start, gint count, gchar value, gboolean reversedSearch) {
        Chars input = (Chars)bytes;
        if (input == null || count <= 0) return -1;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= 0; --i) {
                gchar chr = input[i];
                if (value == chr) return i;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count; ++i) {
                gchar chr = input[i];
                if (value == chr) return i;
            }
        }
        return -1;
    }

    gint Strings::findLatin1CodePoint(Bytes bytes, gint start, gint count, gint value, gboolean reversedSearch) {
        if (bytes == null || count <= 0 || value < 0 || value > 0xff) return -1;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= 0; --i) {
                gchar chr = bytes[i] & 0xff;
                if (value == chr) return i;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count; ++i) {
                gchar chr = bytes[i] & 0xff;
                if (value == chr) return i;
            }
        }
        return -1;
    }

    gint Strings::findUtf16CodePoint(Bytes bytes, gint start, gint count, gint value, gboolean reversedSearch) {
        Chars input = (Chars)bytes;
        if (value <= 0xffff) return findUtf16Char(bytes, start, count, value, reversedSearch);
        if (input == null || count <= 0 || value > 0x10ffff) return -1;
        gchar chr1 = (value >> 10) + 0xD800 - (0x10000 >> 10);
        gchar chr2 = (value & 0x3ff) + 0xDC00;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= 0; --i) {
                gchar chr = input[i];
                if (chr2 == chr && i > 0 && chr1 == input[i - 1]) return i - 1;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count; ++i) {
                gchar chr = input[i];
                if (chr1 == chr && i + 1 < count && chr2 == input[i + 1]) return i;
            }
        }
        return -1;
    }

    gint Strings::findLatin1Bytes(Bytes bytes, gint start, gint count, Bytes bytes2, gint count2,
                                  gboolean reversedSearch) {
        if (bytes == null || bytes2 == null || count <= 0 || count2 <= 0 || count2 > count) return -1;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= count2; --i) {
                gchar chr = bytes2[count2 - 1] & 0xff;
                gint k = findLatin1Char(bytes, i, count, chr, reversedSearch);
                if (k < count2) break;
                i = k + 1;
                for (int j = count2 - 2; j >= 0; --j)
                    if (bytes2[j] != bytes[--k])
                        break;
                if (i - k == count2) return k;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count - count2; ++i) {
                gchar chr = bytes2[0] & 0xff;
                gint k = findLatin1Char(bytes, i, count, chr, reversedSearch);
                if (k < 0 || k > count - count2) return -1;
                i = k - 1;
                for (int j = 1; j < count2; ++j)
                    if (bytes2[j] != bytes[++k])
                        break;
                if (k - i == count2) return k;
            }
        }
        return -1;
    }

    gint Strings::findUtf16Bytes(Bytes bytes, gint start, gint count, Bytes bytes2, gint count2,
                                 gboolean reversedSearch) {
        Chars input = (Chars)bytes;
        Chars input2 = (Chars)bytes2;
        if (input == null || input2 == null || count <= 0 || count2 <= 0 || count2 > count) return -1;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= count2; --i) {
                gchar chr = input2[count2 - 1];
                gint k = findUtf16Char(bytes, i, count, chr, reversedSearch);
                if (k < count2) break;
                i = k + 1;
                for (int j = count2 - 2; j >= 0; --j)
                    if (input2[j] != input[--k])
                        break;
                if (i - k == count2) return k;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count - count2; ++i) {
                gchar chr = input2[0];
                gint k = findUtf16Char(bytes, i, count, chr, reversedSearch);
                if (k < 0 || k > count - count2) return -1;
                i = k - 1;
                for (int j = 1; j < count2; ++j)
                    if (input2[j] != input[++k])
                        break;
                if (k - i == count2) return k;
            }
        }
        return -1;
    }

    gint Strings::countLatin1Chars(Bytes bytes, gint start, gint count) {
        if (bytes == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        return count - start;
    }

    gint Strings::countUtf16Chars(Bytes bytes, gint start, gint count) {
        Chars input = (Chars)bytes;
        if (input == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        return count - start;
    }

    gint Strings::countLatin1CodePoint(Bytes bytes, gint start, gint count) {
        if (bytes == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        return count - start;
    }

    gint Strings::countUtf16CodePoint(Bytes bytes, gint start, gint count) {
        Chars input = (Chars)bytes;
        if (input == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        gint counter = 0;
        for (int i = start; i < count; ++i) {
            gchar chr = input[i];
            if (0xD800 <= chr && chr <= 0xDBFF && i + 1 < count) {
                gchar chr2 = input[i + 1];
                if (0xDC00 <= chr2 && chr2 <= 0xDFFF) {
                    ++counter;
                    ++i;
                }
            }
            ++counter;
        }
        return counter;
    }

    gint Strings::hashLatin1Bytes(Bytes bytes, gint start, gint count) {
        if (bytes == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        gint hash = 0;
        for (int i = start; i < count; ++i)
            hash = hash * 31 + (bytes[i] & 0xff);
        return hash;
    }

    gint Strings::hashUtf16Bytes(Bytes bytes, gint start, gint count) {
        Chars input = (Chars)bytes;
        if (input == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        gint hash = 0;
        for (int i = start; i < count; ++i)
            hash = hash * 31 + input[i];
        return hash;
    }

    gint Strings::shiftLatin1Bytes(Bytes bytes, gint start, gint count, gint shift) {
        if (bytes == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        copyLatin1Bytes(bytes, start, bytes, start + shift, count);
        return shift;
    }

    gint Strings::shiftUtf16Bytes(Bytes bytes, gint start, gint count, gint shift) {
        Chars input = (Chars)bytes;
        if (input == null || count <= 0 || start >= count) return 0;
        if (start < 0) start = 0;
        copyUtf16Bytes(bytes, start, bytes, start + shift, count);
        return shift;
    }

    gint Strings::mismatchLatin1Bytes(Bytes bytes1, gint start1, Bytes bytes2, gint start2, gint count) {
        gint index = 0;
        bytes1 += start1;
        bytes2 += start2;
        if (count > 7) {
            for (gint end = count >> 3; index < end; ++index) {
                glong v1 = getLong(bytes1, index << 3, count);
                glong v2 = getLong(bytes2, index << 3, count);
                if (v1 != v2) break;
            }
            index = index << 3;
        }
        if (count - index > 3) {
            index = index >> 2;
            for (gint end = count >> 2; index < end; ++index) {
                gint v1 = getInt(bytes1, (index << 2), count);
                gint v2 = getInt(bytes2, (index << 2), count);
                if (v1 != v2) break;
            }
            index = index << 2;
        }
        for (gint end = count; index < end; ++index) {
            gbyte v1 = getByte(bytes1, index, count);
            gbyte v2 = getByte(bytes2, index, count);
            if (v1 != v2) return index;
        }
        return -1;
    }

    gint Strings::mismatchUtf16Bytes(Bytes bytes1, gint start1, Bytes bytes2, gint start2, gint count) {
        Chars input1 = (Chars)bytes1;
        Chars input2 = (Chars)bytes2;
        gint index = 0;
        input1 += start1;
        input2 += start2;
        if (count > 3) {
            for (gint end = count >> 2; index < end; ++index) {
                glong v1 = getLong(input1, index << 2, count);
                glong v2 = getLong(input2, index << 2, count);
                if (v1 != v2) break;
            }
            index = index << 2;
        }
        for (gint end = count; index < end; ++index) {
            gchar v1 = getChar(input1, index, count);
            gchar v2 = getChar(input2, index, count);
            if (v1 != v2) return index;
        }
        return -1;
    }

    Strings::Bytes Strings::copyLatin1ToUtf16Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count) {
        Chars output = (Chars)dest;
        if (bytes == null || output == null || count <= 0) return dest;
        if (start1 < 0) start1 = 0;
        if (start2 < 0) start2 = 0;
        for (int i = 0; i < count; ++i) output[i + start2] = bytes[i + start1] & 0xff;
        return dest;
    }

    Strings::Bytes Strings::copyOfLatin1ToUtf16Bytes(Bytes bytes, gint start, gint count, gint newCount) {
        try {
            Bytes output = newUtf16Bytes(newCount);
            if (newCount < count) count = newCount;
            copyLatin1ToUtf16Bytes(bytes, start, output, 0, count);
            return output;
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    gint Strings::findLatin1IntoUtf16Bytes(Bytes bytes, gint start, gint count, Bytes bytes2, gint count2,
                                           gboolean reversedSearch) {
        Chars input = (Chars)bytes;
        if (input == null || bytes2 == null || count <= 0 || count2 <= 0 || count2 > count) return -1;
        if (reversedSearch) {
            if (start > count) start = count;
            for (int i = start - 1; i >= count2; --i) {
                gchar chr = bytes2[count2 - 1] & 0xff;
                gint k = findUtf16Char(bytes, i, count, chr, reversedSearch);
                if (k < count2) break;
                i = k + 1;
                for (int j = count2 - 2; j >= 0; --j)
                    if (bytes2[j] & 0xff != input[--k])
                        break;
                if (i - k == count2) return k;
            }
        }
        else {
            if (start < 0) start = 0;
            for (int i = start; i < count - count2; ++i) {
                gchar chr = bytes2[0] & 0xff;
                gint k = findUtf16Char(bytes, i, count, chr, reversedSearch);
                if (k < 0 || k > count - count2) return -1;
                i = k - 1;
                for (int j = 1; j < count2; ++j)
                    if (bytes2[j] & 0xff != input[++k])
                        break;
                if (k - i == count2) return k;
            }
        }
        return -1;
    }

    gint Strings::mismatchLatin1AndUtf16Bytes(Bytes bytes1, gint start1, Bytes bytes2, gint start2, gint count) {
        Chars input = (Chars)bytes1;
        for (int i = 0; i < count; ++i) if (input[i + start1] != bytes2[i + start2] & 0xff) return i;
        return -1;
    }

    Strings::Bytes Strings::newUtf16Bytes(gint count) {
        try {
            return newBytes(count, UTF16);
        }
        catch (const OutOfMemoryError& oome) { oome.throws($ftrace()); }
    }

    void Strings::deleteBytes(Bytes bytes, gint count) {
        if (bytes == null || count <= 0) return;
        delete []bytes;
    }

    Strings::Bytes Strings::newBytes(gint count, gint coder) {
        if (count <= 0)
            return null;
        try {
            glong requiredSpace = (glong)(1LL + count) << coder;
            if (requiredSpace <= 0)
                return null;
            Bytes bytes = new gbyte[requiredSpace];
            for (glong i = 0; i < requiredSpace; i += 1) bytes[i] = 0;
            return bytes;
        }
        catch (const std::exception&) {
            OutOfMemoryError($toString(Memory allocation failed)).throws($ftrace());
        }
    }

    gbyte Strings::getByte(Bytes bytes, gint index, gint count) {
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return bytes[index];
    }

    gchar Strings::getChar(Bytes bytes, gint index, gint count) {
        count >>= 1;
        index >>= 1;
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return ((Chars)bytes)[index];
    }

    gchar Strings::getChar(Chars chars, gint index, gint count) {
        if (chars == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return chars[index];
    }

    gint Strings::getInt(Bytes bytes, gint index, gint count) {
        count >>= 2;
        index >>= 2;
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return ((Ints)bytes)[index];
    }

    gint Strings::getInt(Chars chars, gint index, gint count) {
        index >>= 1;
        count >>= 1;
        if (chars == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return ((Ints)chars)[index];
    }

    glong Strings::getLong(Bytes bytes, gint index, gint count) {
        count >>= 3;
        index >>= 3;
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return ((Longs)bytes)[index];
    }

    glong Strings::getLong(Chars chars, gint index, gint count) {
        index >>= 2;
        count >>= 2;
        if (chars == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        return ((Longs)chars)[index];
    }

    void Strings::putByte(Bytes bytes, gint index, gbyte value, gint count) {
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        bytes[index] = value;
    }

    void Strings::putChar(Bytes bytes, gint index, gchar value, gint count) {
        count >>= 1;
        index >>= 1;
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        ((Chars)bytes)[index] = value;
    }

    void Strings::putInt(Bytes bytes, gint index, gint value, gint count) {
        count >>= 2;
        index >>= 2;
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        ((Ints)bytes)[index] = value;
    }

    void Strings::putLong(Bytes bytes, gint index, glong value, gint count) {
        count >>= 3;
        index >>= 3;
        if (bytes == null || index < 0 || count <= 0 || index >= count)
            AssertionError(false).throws($ftrace());
        ((Longs)bytes)[index] = value;
    }
}
