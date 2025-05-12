//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H
#define CORE_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H

#include <core/lang/IndexOutOfBoundsException.h>

namespace core
{
    /// Thrown by {@code String} methods to indicate that an index is either negative or greater than the size of the string.
    /// For some methods such as the @b charAt method, this exception also is thrown when the index is equal to the size of the string.
    class StringIndexOutOfBoundsException $final : public IndexOutOfBoundsException
    {
    public:
        /// Constructs a @c StringIndexOutOfBoundsException with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT StringIndexOutOfBoundsException(const String &message);

        /// Constructs a new {@code StringIndexOutOfBoundsException} class with an argument indicating the illegal index.
        /// The index is included in this exception's detail message.
        /// The exact presentation format of the detail message is unspecified.
        /// @param index the illegal index.
        CORE_EXPLICIT StringIndexOutOfBoundsException(gint index);

        ~StringIndexOutOfBoundsException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H
