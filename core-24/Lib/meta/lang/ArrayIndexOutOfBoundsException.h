//
// Created by brunshweeck on 4/30/25.
//

#ifndef CORE_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H
#define CORE_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H

#include <core/lang/IndexOutOfBoundsException.h>

namespace core
{
    /// Thrown to indicate that an array has been accessed with an illegal index.
    /// The index is either negative or greater than or equal to the size of the array.
    class ArrayIndexOutOfBoundsException $final : public IndexOutOfBoundsException
    {
    public:
        /// Constructs an @c ArrayIndexOutOfBoundsException class with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT ArrayIndexOutOfBoundsException(const String &message);

        /// Constructs a new @c ArrayIndexOutOfBoundsException class with an argument indicating the illegal index.
        /// The index is included in this exception's detail message.
        /// The exact presentation format of the detail message is unspecified.
        /// @param index the illegal index.
        CORE_EXPLICIT ArrayIndexOutOfBoundsException(gint index);

        ~ArrayIndexOutOfBoundsException() override = default;

        Exception &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H
