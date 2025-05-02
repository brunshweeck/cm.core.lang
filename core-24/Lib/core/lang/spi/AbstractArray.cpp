//
// Created by brunshweeck on 4/27/25.
//

#include "AbstractArray.h"

#include <core/lang/CloneNotSupportedException.h>

namespace core::lang::spi
{
    AbstractArray::AbstractIteratorStep& AbstractArray::AbstractIteratorStep::operator++() { return next(); }

    AbstractArray::AbstractIteratorStep& AbstractArray::AbstractIteratorStep::clone() const {
        CloneNotSupportedException($toString()).throws($ftrace());
    }

    gboolean AbstractArray::AbstractIteratorStep::equals(const Object& other) const {
        if (this == &other)
            return true;
        const AbstractIteratorStep& otherStep = $cast(const AbstractIteratorStep&, other);
        if (isDone()) return otherStep.isDone();
        return &target() == &otherStep.target() && position() == otherStep.position();
    }
}
