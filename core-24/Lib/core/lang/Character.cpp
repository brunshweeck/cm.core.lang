//
// Created by brunshweeck on 4/27/25.
//

#include "Character.h"

#include "CharArray.h"
#include "IllegalArgumentException.h"
#include "Preconditions.h"
#include "String.h"
#include "../misc/VarHandle.h"

namespace core
{
    Character::Character(gchar value): value(value) {
    }

    gchar Character::charValue() const {
        return value;
    }

    String Character::toString() const {
        return toString(value);
    }

    String Character::toString(gchar value) {
        return toString((gint) value);
    }

    String Character::toString(gint value) {
        return String(toChars(value));
    }

    Character Character::valueOf(gchar value) {
        return value;
    }

    gint Character::hash() const {
        return hash(value);
    }

    gint Character::hash(gchar value) {
        return value;
    }

    gboolean Character::equals(const Object &other) const {
        return this == &other || Class<Character>::hasInstance(other) && value == $cast(const Character&, other).value;
    }

    gint Character::compareTo(const Character &other) const {
        return compare(value, other.value);
    }

    gint Character::compare(gchar a, gchar b) {
        return a - b;
    }

    Character &Character::clone() const {
        return VH::newObject<Character>(*this);
    }

    gboolean Character::isValidCodePoint(gint value) {
        return value >= MIN_CODEPOINT && value <= MAX_CODEPOINT;
    }

    gboolean Character::isBmpCodePoint(gint value) {
        return value >= MIN_VALUE && value <= MAX_VALUE;
    }

    gboolean Character::isSupplementary(gint value) {
        return value > MAX_VALUE && value <= MAX_CODEPOINT;
    }

    gboolean Character::isHighSurrogate(gint value) {
        return value >= MIN_HIGH_SURROGATE && value <= MAX_HIGH_SURROGATE;
    }

    gboolean Character::isLowSurrogate(gint value) {
        return value >= MIN_LOW_SURROGATE && value <= MAX_LOW_SURROGATE;
    }

    gboolean Character::isSurrogate(gint value) {
        return value >= MIN_SURROGATE && value <= MAX_SURROGATE;
    }

    gboolean Character::isSurrogatePair(gint high, gint low) {
        return isHighSurrogate(high) && isLowSurrogate(low);
    }

    gint Character::charCount(gint value) {
        if (!isValidCodePoint(value)) return 0;
        return isBmpCodePoint(value) ? 1 : 2;
    }

    gint Character::toCodePoint(gint high, gint low) {
        return ((high - MIN_HIGH_SURROGATE) << 10) + (low - MIN_LOW_SURROGATE) + MIN_SUPPLEMENTARY;
    }

    gint Character::codePointAt(const lang::CharSequence &csq, gint index) {
        gchar ch = csq.charAt(index);
        if (isHighSurrogate(ch) && index + 1 < csq.length()) {
            gchar ch2 = csq.charAt(index + 1);
            if (isLowerCase(ch2))
                return toCodePoint(ch, ch2);
        }
        return ch;
    }

    gint Character::codePointAt(const CharArray &a, gint index) {
        gchar ch = a[index];
        if (isHighSurrogate(ch) && index + 1 < a.length()) {
            gchar ch2 = a[index + 1];
            if (isLowerCase(ch2))
                return toCodePoint(ch, ch2);
        }
        return ch;
    }

    gint Character::codePointAt(const CharArray &a, gint index, gint limit) {
        gchar ch = a[index];
        if (isHighSurrogate(ch) && index + 1 < limit) {
            gchar ch2 = a[index + 1];
            if (isLowerCase(ch2))
                return toCodePoint(ch, ch2);
        }
        return ch;
    }

    gint Character::codePointBefore(const lang::CharSequence &csq, gint index) {
        gchar ch = csq.charAt(--index);
        if (isLowSurrogate(ch) && index > 0) {
            gchar ch2 = csq.charAt(--index);
            if (isHighSurrogate(ch2))
                return toCodePoint(ch2, ch);
        }
        return ch;
    }

    gint Character::codePointBefore(const CharArray &a, gint index) {
        gchar ch = a[--index];
        if (isLowSurrogate(ch) && index > 0) {
            gchar ch2 = a[--index];
            if (isHighSurrogate(ch2))
                return toCodePoint(ch2, ch);
        }
        return ch;
    }

    gint Character::codePointBefore(const CharArray &a, gint index, gint start) {
        gchar ch = a[--index];
        if (isLowSurrogate(ch) && index > start) {
            gchar ch2 = a[--index];
            if (isHighSurrogate(ch2))
                return toCodePoint(ch2, ch);
        }
        return ch;
    }

    gint Character::highSurrogate(gint value) {
        return (value >> 10) + MIN_HIGH_SURROGATE - (MIN_SUPPLEMENTARY >> 10);
    }

    gint Character::lowSurrogate(gint value) {
        return (value & 0x3ff) + MIN_LOW_SURROGATE;
    }

    gint Character::toChars(gint value, CharArray &dst, gint offset) {
        if (isBmpCodePoint(value)) {
            dst[offset] = (gchar) value;
            return 1;
        }
        if (isValidCodePoint(value)) {
            dst[offset] = highSurrogate(value);
            dst[offset + 1] = lowSurrogate(value);
            return 2;
        }
        IllegalArgumentException($toString(Invalid unicode code point)).throws($ftrace());
    }

    CharArray Character::toChars(gint value) {
        if (isBmpCodePoint(value))
            return CharArray::of((gchar) value);
        if (isValidCodePoint(value))
            return CharArray::of(highSurrogate(value), lowSurrogate(value));
        IllegalArgumentException($toString(Invalid unicode code point)).throws($ftrace());
    }

    gint Character::codePointCount(const lang::CharSequence &csq, gint start, gint end) {
        Preconditions::checkIndexFromRange(start, end, csq.length());
        int n = end - start;
        for (int i = start; i < end;)
            if (isHighSurrogate(csq.charAt(i++)) && i < end && isLowSurrogate(csq.charAt(i))) {
                n--;
                i++;
            }
        return n;
    }

    gint Character::codePointCount(const CharArray &a, gint offset, gint count) {
        Preconditions::checkIndexFromSize(offset, count, a.length());
        int end = offset + count;
        int n = count;
        for (int i = offset; i < end;)
            if (isHighSurrogate(a[i++]) && i < end && isLowSurrogate(a[i])) {
                n--;
                i++;
            }
        return n;
    }

    gint Character::offsetByCodePoint(const lang::CharSequence &csq, gint index, gint valueOffset) {
        return 0;
    }

    gint Character::offsetByCodePoint(const CharArray &a, gint start, gint count, gint index, gint valueOffset) {
        return 0;
    }

    gboolean Character::isLowerCase(gint value) {
        return false;
    }

    gboolean Character::isUpperCase(gint value) {
        return false;
    }

    gboolean Character::isTitleCase(gint value) {
        return false;
    }

    gboolean Character::isDigit(gint value) {
        return false;
    }

    gboolean Character::isDefined(gint value) {
        return false;
    }

    gboolean Character::isLetter(gint value) {
        return false;
    }

    gboolean Character::isLetterOrDigit(gint value) {
        return false;
    }

    gboolean Character::isAlphabetic(gint value) {
        return false;
    }

    gboolean Character::isIdeographic(gint value) {
        return false;
    }

    gboolean Character::isEmoji(gint value) {
        return false;
    }

    gboolean Character::isEmojiPresentation(gint value) {
        return false;
    }

    gboolean Character::isEmojiModifier(gint value) {
        return false;
    }

    gboolean Character::isEmojiModifierBase(gint value) {
        return false;
    }

    gboolean Character::isEmojiComponent(gint value) {
        return false;
    }

    gboolean Character::isExtendedPictographic(gint value) {
        return false;
    }

    gboolean Character::isWhiteSpace(gint value) {
        return false;
    }

    gboolean Character::isUnicodeSpace(gint value) {
        return false;
    }

    gboolean Character::isISOControl(gint value) {
        return false;
    }

    gboolean Character::isMirrored(gint value) {
        return false;
    }

    gint Character::toLowerCase(gint value) {
        return 0;
    }

    gint Character::toUpperCase(gint value) {
        return 0;
    }

    gint Character::toTitleCase(gint value) {
        return 0;
    }

    gint Character::toDigit(gint value, gint radix) {
        return 0;
    }

    gint Character::toNumber(gint value) {
        return 0;
    }

    gint Character::fromDigit(gint value, gint radix) {
        return 0;
    }

    Character::Category Character::getCategory(gint value) {
        return {};
    }

    Character::Directionality Character::getDirectionality(gint value) {
        return {};
    }

    String Character::getName(gint value) {
        return {};
    }

    gint Character::forName(const String &name) {
        return 0;
    }

    gchar Character::reverseBytes(gchar value) {
        return 0;
    }
} // core
