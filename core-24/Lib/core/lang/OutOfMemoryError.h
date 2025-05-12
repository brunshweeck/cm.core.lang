//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_OUTOFMEMORYERROR_H
#define CORE_LANG_OUTOFMEMORYERROR_H
#include "Error.h"

namespace core
{
    /// Thrown when cannot allocate an object because it is out of memory, and no more memory could be made available by the garbage collector.
    class OutOfMemoryError $final : public lang::Error
    {
    public:
        /// Constructs an @c OutOfMemoryError with the specified detail message.
        /// @param message the detail message.
        CORE_EXPLICIT OutOfMemoryError(const String &message);

        ~OutOfMemoryError() override = default;

        Error &clone() const override;

    private:
        void selfThrow() const override;
    };
} // core

#endif // CORE_LANG_OUTOFMEMORYERROR_H
