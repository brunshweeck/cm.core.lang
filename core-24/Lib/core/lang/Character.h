//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_CHARACTER_H
#define CORE_LANG_CHARACTER_H
#include "Byte.h"
#include "Comparable.h"

namespace core
{
    class Character $final : public lang::Comparable<Character>
    {
        gchar value;

    public:
        static CORE_FAST gint MAX_RADIX = 36;
        static CORE_FAST gint MIN_RADIX = 2;
        static CORE_FAST gchar MAX_VALUE = 0xFFFF;
        static CORE_FAST gchar MIN_VALUE = 0x0000;
        static CORE_FAST gchar MAX_HIGH_SURROGATE = 0xDBFF;
        static CORE_FAST gchar MIN_HIGH_SURROGATE = 0xD800;
        static CORE_FAST gchar MAX_LOW_SURROGATE = 0xDFFF;
        static CORE_FAST gchar MIN_LOW_SURROGATE = 0xDC00;
        static CORE_FAST gchar MAX_SURROGATE = MAX_LOW_SURROGATE;
        static CORE_FAST gchar MIN_SURROGATE = MIN_HIGH_SURROGATE;
        static CORE_FAST gint MIN_SUPPLEMENTARY = 0x10000;
        static CORE_FAST gint MAX_CODEPOINT = 0x0010FFFF;
        static CORE_FAST gint MIN_CODEPOINT = 0x00000000;
        static CORE_FAST gint SIZE = 1 << 4;
        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        enum Category: gbyte
        {
        };

        enum Directionality: gbyte
        {
        };

        Character(gchar value = u'\0');

        ~Character() override = default;

        gchar charValue() const;

        String toString() const override;

        static String toString(gchar value);

        static String toString(gint value);

        static Character valueOf(gchar value);

        gint hash() const override;

        static gint hash(gchar value);

        gboolean equals(const Object &other) const override;

        gint compareTo(const Character &other) const override;

        static gint compare(gchar a, gchar b);

        Character &clone() const override;

        static gboolean isValidCodePoint(gint value);

        static gboolean isBmpCodePoint(gint value);

        static gboolean isSupplementary(gint value);

        static gboolean isHighSurrogate(gint value);

        static gboolean isLowSurrogate(gint value);

        static gboolean isSurrogate(gint value);

        static gboolean isSurrogatePair(gint high, gint low);

        static gint charCount(gint value);

        static gint toCodePoint(gint high, gint low);

        static gint codePointAt(const lang::CharSequence &csq, gint index);

        static gint codePointAt(const CharArray &a, gint index);

        static gint codePointAt(const CharArray &a, gint index, gint limit);

        static gint codePointBefore(const lang::CharSequence &csq, gint index);

        static gint codePointBefore(const CharArray &a, gint index);

        static gint codePointBefore(const CharArray &a, gint index, gint start);

        static gint highSurrogate(gint value);

        static gint lowSurrogate(gint value);

        static gint toChars(gint value, CharArray &dst, gint offset);

        static CharArray toChars(gint value);

        static gint codePointCount(const lang::CharSequence &csq, gint start, gint end);

        static gint codePointCount(const CharArray &a, gint offset, gint count);

        static gint offsetByCodePoint(const lang::CharSequence &csq, gint index, gint valueOffset);

        static gint offsetByCodePoint(const CharArray &a, gint start, gint count, gint index, gint valueOffset);

        static gboolean isLowerCase(gint value);

        static gboolean isUpperCase(gint value);

        static gboolean isTitleCase(gint value);

        static gboolean isDigit(gint value);

        static gboolean isDefined(gint value);

        static gboolean isLetter(gint value);

        static gboolean isLetterOrDigit(gint value);

        static gboolean isAlphabetic(gint value);

        static gboolean isIdeographic(gint value);

        static gboolean isEmoji(gint value);

        static gboolean isEmojiPresentation(gint value);

        static gboolean isEmojiModifier(gint value);

        static gboolean isEmojiModifierBase(gint value);

        static gboolean isEmojiComponent(gint value);

        static gboolean isExtendedPictographic(gint value);

        static gboolean isWhiteSpace(gint value);

        static gboolean isUnicodeSpace(gint value);

        static gboolean isISOControl(gint value);

        static gboolean isMirrored(gint value);

        static gint toLowerCase(gint value);

        static gint toUpperCase(gint value);

        static gint toTitleCase(gint value);

        static gint toDigit(gint value, gint radix = 10);

        static gint toNumber(gint value);

        static gint fromDigit(gint value, gint radix = 10);

        static Category getCategory(gint value);

        static Directionality getDirectionality(gint value);

        static String getName(gint value);

        static gint forName(const String &name);

        static gchar reverseBytes(gchar value);
    };
} // core

#endif // CORE_LANG_CHARACTER_H
