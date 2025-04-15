//
// Created by brunshweeck on 4/15/25.
//

#ifndef CORE_LANG_CHARSEQUENCE_H
#define CORE_LANG_CHARSEQUENCE_H

#include "Object.h"

namespace core
{
    namespace lang
    {
        /// The class @c CharSequence represent the @a readable sequence of characters values. this class provide the uniform read-only access to many different kinds of chars sequences.
        /// A @c char value represents a character in the <em>Basic Multilingual Plane</em> or @a surrogate.
        class CharSequence : public virtual Object
        {
        protected:
            CharSequence() = default;

        public:
            ~CharSequence() override = default;

            /// Returns the length of this character sequence.
            /// The length is the number of 16-bit chars in the sequence.
            /// @return The number of characters in this sequence
            virtual gint length() const = 0;

            /// Returns @c true if this character sequence is empty.
            /// @return The value @c true if @c this.length() return @c 0, otherwise @c false
            virtual gboolean isEmpty() const;

            /// Returns the char value at the specified index.
            /// An index ranges from zero to @c length()-1.
            /// The first character value of the sequence is at index zero, the next at index one, and so on, as for array indexing.
            /// If the character value specified by the index is a @c surrogate, the surrogate value is returned.
            /// @param index The index of character value returned.
            /// @return The specified character value at given index
            /// @throws IndexOutOfBoundsException if the @c index argument is negative or not less than @c length()
            virtual gchar charAt(gint index) const = 0;

            /// Returns a @c CharSequence that is a subsequence of this sequence.
            /// The subsequence starts with the character value at the specified index and ends with the character value at index @c end-1.
            /// The length (in chars) of the returned sequence is @code end - start @endcode , so if @code start == end @endcode then an empty sequence is returned.
            /// @param start The start index, inclusive
            /// @param end The end index, exclusive
            /// @return  the specified subsequence
            /// @throws  IndexOutOfBoundsException if @c start or @c end are negative, if @c end is greater than @c length(), or if @c start is greater than @c end
            virtual CharSequence& subSequence(gint start, gint end) const = 0;
        };
    } // lang
} // core

#endif // CORE_LANG_CHARSEQUENCE_H
