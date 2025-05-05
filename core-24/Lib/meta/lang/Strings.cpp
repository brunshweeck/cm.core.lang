//
// Created by brunshweeck on 01/05/25.
//

#include "Strings.h"

#include <core/lang/Null.h>
#include <core/lang/OutOfMemoryError.h>

#include "StringIndexOutOfBoundsException.h"
#include "core/lang/AssertionError.h"
#include "core/lang/ByteArray.h"
#include "core/lang/CharArray.h"
#include "core/lang/IntArray.h"

namespace core::lang
{
    gint Strings::checkIndex(gint index, gint length) {
        if ((index | length) < 0 || index >= length)
            StringIndexOutOfBoundsException(
                u"Index "_Su + index + u" out of bounds for length "_Su + length
            ).throws($ftrace());
        return index;
    }

    gint Strings::checkIndexFromRange(gint start, gint end, gint length) {
        if ((start | end | length) < 0 || end < start || length < end)
            StringIndexOutOfBoundsException(
                u"Range ["_Su + start + u" ... "_Su + end + u") out of bounds for length "_Su + length
            ).throws($ftrace());
        return start;
    }

    gint Strings::checkIndexFromSize(gint start, gint size, gint length) {
        if ((start | size | length) < 0 || length < size + start) {
            if (size < 0) {
                size = -size;
                StringIndexOutOfBoundsException(
                    u"Range ["_Su + start + u" ... "_Su + start + u" - "_Su
                    + size + u") out of bounds for length "_Su + length
                ).throws($ftrace());
            }
            else
                StringIndexOutOfBoundsException(
                    u"Range ["_Su + start + u" ... "_Su + start + u" - "_Su
                    + size + u") out of bounds for length "_Su + length
                ).throws($ftrace());
        }
        return start;
    }

    gint Strings::checkIndexForAdding(gint index, gint length) {
        if (index < 0 || index > length)
            StringIndexOutOfBoundsException(
                u"Index "_Su + index + u" out of adding bounds for length "_Su + length
            ).throws($ftrace());
        return index;
    }

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

    Strings::Bytes Strings::copyOfLatn1Bytes(Bytes bytes, gint start, gint count, gint newCount) {
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

    gint Strings::getUtf32CharAt(Bytes bytes, gint index, gint count) {
        Ints input = (Ints)bytes;
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

    Strings::Bytes Strings::tryConvertUtf32BytesToLatin1(Bytes bytes, gint start, gint count) {
        if ((bytes == null) || (start < 0) || (count <= 0)) return null;
        try {
            Bytes copy = newLatin1Bytes(count);
            for (int i = 0; i < count; ++i) {
                gint chr = getUtf32CharAt(bytes, start + i, count);
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

    Strings::Bytes Strings::tryConvertCharsToLatn1(const CharArray& chars, gint start, gint count) {
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

    Strings::Bytes Strings::convertCharsToUtf16(const CharArray& chars, gint start, gint count) {
        if (start < 0 || count <= 0) return null;
        try {
            Bytes copy = newUtf16Bytes(count);
            Chars output = (Chars)copy;
            for (int i = 0; i < count; ++i) output[i] = chars[start + i];
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

    gint Strings::putLatn1CharAt(Bytes bytes, gint index, gchar value, gint count) {
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

    Strings::Bytes Strings::copyUtf32ToUtf16Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count,
                                                  gint count2) {
        Chars output = (Chars)dest;
        Ints input = (Ints)bytes;
        if (bytes == null || output == null || count <= 0) return dest;
        if (start1 < 0) start1 = 0;
        if (start2 < 0) start2 = 0;
        for (int i = 0, j = 0; i < count; ++i) {
            gint chr = input[i + start1];
            if (chr < 0 || chr > 0x10ffff) {
                if (j > count2) break;
                output[j++] = 0x3f;
                continue;
            }
            if (chr > 0xffff) {
                gchar chr1 = (chr >> 10) + 0xD800 - (0x10000 >> 10);
                gchar chr2 = (chr & 0x3ff) + 0xDC00;
                if (j + 2 > count2) break;
                output[j++] = chr1;
                output[j++] = chr2;
                continue;
            }
            if (j > count2) break;
            output[j++] = (gchar)chr;
        }
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

    Strings::Bytes Strings::copyOfUtf32ToUtf16Bytes(Bytes bytes, gint start, gint count, gint newCount) {
        try {
            Bytes output = newUtf16Bytes(newCount);
            copyUtf32ToUtf16Bytes(bytes, start, output, 0, count, newCount);
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
        for (int i = count - 1; i >= 0; --i) bytes[i] = 0;
        delete []bytes;
    }

    gint Strings::decodeUtf8Chars(Bytes bytes, gint start, gint count, CharArray& dest, gint start2, gint count2) {
        if (bytes == null || count <= 0) return 0;
        if (start < 0) start = 0;
        if (start2 < 0) start2 = 0;
        CORE_FAST static gchar Repl = 0xfffd;
        gint index = start;
        gint index2 = start2;
        for (; index < count && start2 < count2; ++index) {
            gchar chr = bytes[index] & 0xff;
            if (chr > 0x7f) break;
            dest[index2++] = chr;
        }
        while (index < count) {
            gint b1 = bytes[index];
            if (b1 > 0) {
                // 1 byte, 7 bits: 0xxxxxxx
                if (start2 >= count2) break; // Overflow
                dest[index2++] = b1 & 0xff;
                ++index;
                continue;
            }
            if ((b1 >> 5) == -2 && (b1 & 0x1e) != 0) {
                // 2 bytes, 11 bits: 110xxxxx 10xxxxxx
                //                          [C2..DF] [80..BF]
                if (start2 >= count2) break; // Overflow
                gint b2 = count - index < 2 ? 0 : bytes[index + 1];
                if ((b2 & 0xc0) != 0x80) {
                    // Malformed (number of bytes require is insufficient)
                    dest[index2++] = Repl;
                    ++index;
                    continue;
                }
                dest[index2++] = (gchar)(b1 << 6 ^ b2 ^ ((gbyte)0xC0 << 6 ^ (gbyte)0x80 << 0));
                ++++index;
                continue;
            }
            if ((b1 >> 4) == -2) {
                // 3 bytes, 16 bits: 1110xxxx 10xxxxxx 10xxxxxx
                if (start2 >= count2) break; // Overflow
                gint remaining = count - index;
                gint b2 = remaining < 2 ? 0 : bytes[index + 1];
                gint b3 = remaining < 3 ? 0 : bytes[index + 2];
                if (remaining < 3) {
                    // Malformed
                    dest[index2++] = Repl;
                    ++index;
                    if (remaining > 1 && ((b1 == (gbyte)0xe0 && (b2 & 0xe0) == 0x80) || (b2 & 0xc0) != 0x80)) ++index;
                    continue;
                }
                if ((b1 == (gbyte)0xe0 && (b2 & 0xe0) == 0x80) || (b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80) {
                    // Malformed
                    dest[index2++] = Repl;
                    ++++++index;
                    continue;
                }
                dest[index2++] = b1 << 12 ^ b2 << 6 ^ (b3 ^ ((gbyte)0xE0 << 12 ^ (gbyte)0x80 << 6 ^ (gbyte)0x80 << 0));
                ++++++index;
                continue;
            }
            if ((b1 >> 3) == -2) {
                // 4 bytes, 21 bits: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                if (count2 - start2 < 2) break; // Overflow
                gint remaining = count - index;
                gint b2 = remaining < 2 ? 0 : bytes[index + 1];
                gint b3 = remaining < 3 ? 0 : bytes[index + 2];
                gint b4 = remaining < 4 ? 0 : bytes[index + 3];
                if (remaining < 4) {
                    dest[index2++] = Repl;
                    ++index;
                    b1 = b1 & 0xff;
                    if (b1 > 0xf4 || remaining > 1 && ((b1 == 0xf0 && (b2 < 0x90 || b2 > 0xbf))
                        || (b1 == 0xf4 && (b2 & 0xf0) != 0x80) || (b2 & 0xc0) != 0x80))
                        ++index;
                    if (remaining > 2 && ((b3 & 0xc0) != 0x80)) ++++index;
                }
                if ((b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80 || (b4 & 0xc0) != 0x80) {
                    dest[index2++] = Repl;
                    ++++++++index;
                    continue;
                }
                gint chr = b1 << 18 ^ b2 << 12 ^ b3 << 6 ^ (b4 ^
                    ((gbyte)0xF0 << 18 ^ (gbyte)0x80 << 12 ^ (gbyte)0x80 << 6 ^ (gbyte)0x80));
                dest[index2++] = (chr >> 10) + 0xD800 - (0x10000 >> 10);
                dest[index2++] = (chr & 0x3ff) + 0xDC00;
                ++++++++index;
                continue;
            }
            // Malformed
            if (start2 >= count2) break; // Overflow
            dest[index2++] = Repl;
            ++index;
        }
        return index2 - start2;
    }

    gint Strings::decodeUtf8Chars(const ByteArray& bytes, gint start, gint count, CharArray& dest, gint start2,
                                  gint count2) {
        if (bytes == null || count <= 0) return 0;
        if (start < 0) start = 0;
        if (start2 < 0) start2 = 0;
        CORE_FAST static gchar Repl = 0xfffd;
        gint index = start;
        gint index2 = start2;
        for (; index < count && start2 < count2; ++index) {
            gchar chr = bytes[index] & 0xff;
            if (chr > 0x7f) break;
            dest[index2++] = chr;
        }
        while (index < count) {
            gint b1 = bytes[index];
            if (b1 > 0) {
                // 1 byte, 7 bits: 0xxxxxxx
                if (start2 >= count2) break; // Overflow
                dest[index2++] = b1 & 0xff;
                ++index;
                continue;
            }
            if ((b1 >> 5) == -2 && (b1 & 0x1e) != 0) {
                // 2 bytes, 11 bits: 110xxxxx 10xxxxxx
                //                          [C2..DF] [80..BF]
                if (start2 >= count2) break; // Overflow
                gint b2 = count - index < 2 ? 0 : bytes[index + 1];
                if ((b2 & 0xc0) != 0x80) {
                    // Malformed (number of bytes require is insufficient)
                    dest[index2++] = Repl;
                    ++index;
                    continue;
                }
                dest[index2++] = (gchar)(b1 << 6 ^ b2 ^ ((gbyte)0xC0 << 6 ^ (gbyte)0x80 << 0));
                ++++index;
                continue;
            }
            if ((b1 >> 4) == -2) {
                // 3 bytes, 16 bits: 1110xxxx 10xxxxxx 10xxxxxx
                if (start2 >= count2) break; // Overflow
                gint remaining = count - index;
                gint b2 = remaining < 2 ? 0 : bytes[index + 1];
                gint b3 = remaining < 3 ? 0 : bytes[index + 2];
                if (remaining < 3) {
                    // Malformed
                    dest[index2++] = Repl;
                    ++index;
                    if (remaining > 1 && ((b1 == (gbyte)0xe0 && (b2 & 0xe0) == 0x80) || (b2 & 0xc0) != 0x80)) ++index;
                    continue;
                }
                if ((b1 == (gbyte)0xe0 && (b2 & 0xe0) == 0x80) || (b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80) {
                    // Malformed
                    dest[index2++] = Repl;
                    ++++++index;
                    continue;
                }
                dest[index2++] = b1 << 12 ^ b2 << 6 ^ (b3 ^ ((gbyte)0xE0 << 12 ^ (gbyte)0x80 << 6 ^ (gbyte)0x80 << 0));
                ++++++index;
                continue;
            }
            if ((b1 >> 3) == -2) {
                // 4 bytes, 21 bits: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                if (count2 - start2 < 2) break; // Overflow
                gint remaining = count - index;
                gint b2 = remaining < 2 ? 0 : bytes[index + 1];
                gint b3 = remaining < 3 ? 0 : bytes[index + 2];
                gint b4 = remaining < 4 ? 0 : bytes[index + 3];
                if (remaining < 4) {
                    dest[index2++] = Repl;
                    ++index;
                    b1 = b1 & 0xff;
                    if (b1 > 0xf4 || remaining > 1 && ((b1 == 0xf0 && (b2 < 0x90 || b2 > 0xbf))
                        || (b1 == 0xf4 && (b2 & 0xf0) != 0x80) || (b2 & 0xc0) != 0x80))
                        ++index;
                    if (remaining > 2 && ((b3 & 0xc0) != 0x80)) ++++index;
                }
                if ((b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80 || (b4 & 0xc0) != 0x80) {
                    dest[index2++] = Repl;
                    ++++++++index;
                    continue;
                }
                gint chr = b1 << 18 ^ b2 << 12 ^ b3 << 6 ^ (b4 ^
                    ((gbyte)0xF0 << 18 ^ (gbyte)0x80 << 12 ^ (gbyte)0x80 << 6 ^ (gbyte)0x80));
                dest[index2++] = (chr >> 10) + 0xD800 - (0x10000 >> 10);
                dest[index2++] = (chr & 0x3ff) + 0xDC00;
                ++++++++index;
                continue;
            }
            // Malformed
            if (start2 >= count2) break; // Overflow
            dest[index2++] = Repl;
            ++index;
        }
        return index2 - start2;
    }

    ByteArray Strings::encodeLatn1ToUtf8Bytes(Bytes bytes, gint start, gint end) {
        if (start < 0) start = 0;
        if (end < 0) end = 0;
        glong count = (end - start);
        if (count < 0 || bytes == null) return ByteArray();
        count = (glong)(count * 1.5f);
        if (count > Integer::MAX_VALUE)
            count = Integer::MAX_VALUE;
        ByteArray output = ByteArray(count);
        gint index = 0;
        gint overflow = false;
        while (start < end) {
            gbyte b = bytes[start];
            if (b < 0) goto Encoding;
            output[index++] = b;
            ++start;
        }
        goto Ending;
    Overflow:
        if (overflow) {
            glong newCount = count + ((count >> 1) < 8 ? 8 : count >> 1);
            if (newCount > Integer::MAX_VALUE)
                newCount = count + ((count >> 1) >= 8 ? count >> 1 : 8);
            if (newCount >= Integer::MAX_VALUE)
                OutOfMemoryError($toString(Required length exceed implementation limit)).throws($ftrace());
            count = newCount;
            output = copyOfArray(output, newCount);
        }
    Encoding:
        while (start < end) {
            gchar chr = bytes[start] & 0xff;
            if (chr < 0x80) {
                if ((overflow = (index >= count))) goto Overflow;
                output[index++] = (gbyte)chr;
                ++start;
                continue;
            }
            if ((overflow = (count - index < 2))) goto Overflow;
            output[index++] = (gbyte)(0xc0 | chr >> 6);
            output[index++] = (gbyte)(0x80 | chr & 0x3f);
            ++start;
        }
    Ending:
        return copyOfArray(output, index);
    }

    ByteArray Strings::encodeUtf16ToUtf8Bytes(Bytes bytes, gint start, gint end) {
        if (start < 0) start = 0;
        if (end < 0) end = 0;
        glong count = (end - start);
        if (count < 0 || bytes == null) return ByteArray();
        count = (glong)(count * 1.5f);
        if (count > Integer::MAX_VALUE)
            count = Integer::MAX_VALUE;
        ByteArray output = ByteArray(count);
        gint index = 0;
        gint overflow = false;
        while (start < end) {
            gchar chr = getUtf16CharAt(bytes, start, end);
            if (chr > 0x7f) goto Encoding;
            output[index++] = (gbyte)chr;
            ++start;
        }
        goto Ending;
    Overflow:
        if (overflow) {
            glong newCount = count + ((count >> 1) < 8 ? 8 : count >> 1);
            if (newCount > Integer::MAX_VALUE)
                newCount = count + ((count >> 1) >= 8 ? count >> 1 : 8);
            if (newCount >= Integer::MAX_VALUE)
                OutOfMemoryError($toString(Required length exceed implementation limit)).throws($ftrace());
            count = newCount;
            output = copyOfArray(output, newCount);
        }
    Encoding:
        while (start < end) {
            gchar chr = getUtf16CharAt(bytes, start, end);
            if (chr < 0x80) {
                if ((overflow = (index >= count))) goto Overflow;
                output[index++] = (gbyte)chr;
                ++start;
                continue;
            }
            if (chr < 0x800) {
                // 2 bytes, 11 bits
                if ((overflow = (count - index < 2))) goto Overflow;
                output[index++] = (gbyte)(0xc0 | chr >> 6);
                output[index++] = (gbyte)(0x80 | chr & 0x3f);
                ++start;
                continue;
            }
            if (0xD800 <= chr && chr <= 0xDFFF) {
                // Surrogate
                gchar chr1 = chr;
                gint ch = -1;
                if (chr1 < 0xDC00) // High Surrogate
                    if (end - start >= 2) {
                        gchar chr2 = getUtf16CharAt(bytes, start + 1, end);
                        if (0xDC00 <= chr2 && chr2 <= 0xDFFF)
                            ch = ((chr1 - 0xD800) << 10) + (chr2 - 0xDC00) + 0x10000;
                    }
                if (ch < 0) {
                    if ((overflow = (index >= count))) goto Overflow;
                    output[index++] = 0x63;
                    ++start;
                    continue;
                }
                if ((overflow = (count - index < 4))) goto Overflow;
                output[index++] = (gbyte)(0xf0 | ch >> 18);
                output[index++] = (gbyte)(0x80 | ch >> 12 & 0x3f);
                output[index++] = (gbyte)(0x80 | ch >> 6 & 0x3f);
                output[index++] = (gbyte)(0x80 | ch & 0x3f);
                ++++start;
                continue;
            }
            // 3 bytes, 16 bits
            if ((overflow = (count - index < 3))) goto Overflow;
            output[index++] = (gbyte)(0xe0 | chr >> 12);
            output[index++] = (gbyte)(0x80 | chr >> 6 & 0x3f);
            output[index++] = (gbyte)(0x80 | chr & 0x3f);
            ++start;
        }
    Ending:
        return copyOfArray(output, index);
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
        if (bytes == null || index < 0 || count <= 0 || index >= count) return;
        bytes[index] = value;
    }

    void Strings::putChar(Bytes bytes, gint index, gchar value, gint count) {
        count >>= 1;
        index >>= 1;
        if (bytes == null || index < 0 || count <= 0 || index >= count) return;
        ((Chars)bytes)[index] = value;
    }

    void Strings::putInt(Bytes bytes, gint index, gint value, gint count) {
        count >>= 2;
        index >>= 2;
        if (bytes == null || index < 0 || count <= 0 || index >= count) return;
        ((Ints)bytes)[index] = value;
    }

    void Strings::putLong(Bytes bytes, gint index, glong value, gint count) {
        count >>= 3;
        index >>= 3;
        if (bytes == null || index < 0 || count <= 0 || index >= count) return;
        ((Longs)bytes)[index] = value;
    }

    ByteArray Strings::copyOfArray(const ByteArray& input, gint newCount) {
        gint count = input.length();
        if (newCount == count) return input;
        if (count > newCount) count = newCount;
        ByteArray output = ByteArray(newCount);
        for (int i = 0; i < count; ++i) output[i] = input[i];
        return output;
    }
}
