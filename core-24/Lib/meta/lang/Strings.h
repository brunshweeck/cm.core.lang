//
// Created by brunshweeck on 01/05/25.
//

#ifndef CORE_LANG_STRINGS_H
#define CORE_LANG_STRINGS_H

#include <core/lang/String.h>

namespace core::lang
{
    class Strings $final : public Object
    {
        Strings() = default;

    public:
        ~Strings() override = default;

        $alias(Bytes, Class<gbyte>::Pointer);
        $alias(Chars, Class<gchar>::Pointer);
        $alias(Ints, Class<gint>::Pointer);
        $alias(Longs, Class<glong>::Pointer);

        enum Coder: gbyte { LATIN1 = 0, UTF16 = 1 };

        static Bytes newLatin1Bytes(gint count);
        static Bytes newUtf16Bytes(gint count);

        static Bytes copyLatin1Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count);
        static Bytes copyUtf16Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count);

        static Bytes copyOfLatin1Bytes(Bytes bytes, gint start, gint count, gint newCount);
        static Bytes copyOfUtf16Bytes(Bytes bytes, gint start, gint count, gint newCount);

        static gchar getLatin1CharAt(Bytes bytes, gint index, gint count);
        static gchar getUtf16CharAt(Bytes bytes, gint index, gint count);

        static gint getLatin1CodePointAt(Bytes bytes, gint index, gint count);
        static gint getUtf16CodePointAt(Bytes bytes, gint index, gint count);

        static Bytes fillLatin1Bytes(Bytes bytes, gint start, gbyte value, gint count);
        static Bytes fillUtf16Bytes(Bytes bytes, gint start, gchar value, gint count);

        static Bytes tryConvertUtf16BytesToLatin1(Bytes bytes, gint start, gint count);

        static Bytes tryConvertCharsToLatin1(const CharArray& chars, gint start, gint count);

        static Bytes tryConvertCodePointsToLatin1(const IntArray& codePoints, gint start, gint count);

        static gint putLatin1CharAt(Bytes bytes, gint index, gchar value, gint count);
        static gint putUtf16CharAt(Bytes bytes, gint index, gchar value, gint count);

        static gint putLatin1CodePoint(Bytes bytes, gint index, gint value, gint count);
        static gint putUtf16CodePoint(Bytes bytes, gint index, gint value, gint count);

        static gint findLatin1Char(Bytes bytes, gint start, gint count, gchar value, gboolean reversedSearch);
        static gint findUtf16Char(Bytes bytes, gint start, gint count, gchar value, gboolean reversedSearch);

        static gint findLatin1CodePoint(Bytes bytes, gint start, gint count, gint value, gboolean reversedSearch);
        static gint findUtf16CodePoint(Bytes bytes, gint start, gint count, gint value, gboolean reversedSearch);

        static gint findLatin1Bytes(Bytes bytes, gint start, gint count,Bytes bytes2, gint count2, gboolean reversedSearch);
        static gint findUtf16Bytes(Bytes bytes, gint start, gint count,Bytes bytes2, gint count2, gboolean reversedSearch);

        static gint countLatin1Chars(Bytes bytes, gint start, gint count);
        static gint countUtf16Chars(Bytes bytes, gint start, gint count);

        static gint countLatin1CodePoint(Bytes bytes, gint start, gint count);
        static gint countUtf16CodePoint(Bytes bytes, gint start, gint count);

        static gint hashLatin1Bytes(Bytes bytes, gint start, gint count);
        static gint hashUtf16Bytes(Bytes bytes, gint start, gint count);

        static gint shiftLatin1Bytes(Bytes bytes, gint start, gint count, gint shift);
        static gint shiftUtf16Bytes(Bytes bytes, gint start, gint count, gint shift);

        static gint mismatchLatin1Bytes(Bytes bytes1, gint start1, Bytes bytes2, gint start2, gint count);
        static gint mismatchUtf16Bytes(Bytes bytes1, gint start1, Bytes bytes2, gint start2, gint count);

        // Latn1 -- Utf-16
        static Bytes copyLatin1ToUtf16Bytes(Bytes bytes, gint start1, Bytes dest, gint start2, gint count);
        static Bytes copyOfLatin1ToUtf16Bytes(Bytes bytes, gint start, gint count, gint newCount);
        static gint findLatin1IntoUtf16Bytes(Bytes bytes, gint start, gint count,Bytes bytes2, gint count2, gboolean reversedSearch);
        static gint mismatchLatin1AndUtf16Bytes(Bytes bytes1, gint start1, Bytes bytes2, gint start2, gint count);

        // Any
        static void deleteBytes(Bytes bytes, gint count);

    private:
        static Bytes newBytes(gint count, gint coder);

        static gbyte getByte(Bytes bytes, gint index, gint count);

        static gchar getChar(Bytes bytes, gint index, gint count);
        static gchar getChar(Chars chars, gint index, gint count);

        static gint getInt(Bytes bytes, gint index, gint count);
        static gint getInt(Chars chars, gint index, gint count);

        static glong getLong(Bytes bytes, gint index, gint count);
        static glong getLong(Chars chars, gint index, gint count);

        static void putByte(Bytes bytes, gint index, gbyte value, gint count);
        static void putChar(Bytes bytes, gint index, gchar value, gint count);
        static void putInt(Bytes bytes, gint index, gint value, gint count);
        static void putLong(Bytes bytes, gint index, glong value, gint count);
    };
}

#endif // CORE_LANG_STRINGS_H
