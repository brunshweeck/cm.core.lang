//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
#define CORE_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
#include "IllegalArgumentException.h"

namespace core
{
    /// Thrown to indicate that an index of some sort (such as to an array, to a string, or to a vector) is out of range.
    /// Applications can subclass this class to indicate similar exceptions.
    class IndexOutOfBoundsException : public IllegalArgumentException
    {
    public:
        /// Constructs an @c IndexOutOfBoundsException with the specified detail message.
        /// @param message the detail message
        CORE_EXPLICIT IndexOutOfBoundsException(const String &message);

        /// Constructs a new {@code IndexOutOfBoundsException} class with an argument indicating the illegal index.
        /// The index is included in this exception's detail message.
        /// The exact presentation format of the detail message is unspecified.
        /// @param index the illegal index.
        CORE_EXPLICIT IndexOutOfBoundsException(glong index);

        ~IndexOutOfBoundsException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
