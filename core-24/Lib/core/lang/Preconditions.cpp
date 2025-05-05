//
// Created by brunshweeck on 03/05/25.
//

#include "Preconditions.h"

#include "IndexOutOfBoundsException.h"

namespace core
{
    gint Preconditions::checkIndex(gint index, gint length) {
        if ((index | length) < 0 || index >= length)
            IndexOutOfBoundsException(
                u"Index "_Su + index + u" out of bounds for length "_Su + length
            ).throws($ftrace());
        return index;
    }

    gint Preconditions::checkIndexFromRange(gint start, gint end, gint length) {
        if ((start | end | length) < 0 || end < start || length < end)
            IndexOutOfBoundsException(
                u"Range ["_Su + start + u" ... "_Su + end + u") out of bounds for length "_Su + length
            ).throws($ftrace());
        return start;
    }

    gint Preconditions::checkIndexFromSize(gint start, gint size, gint length) {
        if ((start | size | length) < 0 || length < size + start) {
            if (size < 0) {
                size = -size;
                IndexOutOfBoundsException(
                    u"Range ["_Su + start + u" ... "_Su + start + u" - "_Su
                    + size + u") out of bounds for length "_Su + length
                ).throws($ftrace());
            }
            else
                IndexOutOfBoundsException(
                    u"Range ["_Su + start + u" ... "_Su + start + u" - "_Su
                    + size + u") out of bounds for length "_Su + length
                ).throws($ftrace());
        }
        return start;
    }

    gint Preconditions::checkIndexForAdding(gint index, gint length) {
        if (index < 0 || index > length)
            IndexOutOfBoundsException(
                u"Index "_Su + index + u" out of adding bounds for length "_Su + length
            ).throws($ftrace());
        return index;
    }
} // core
