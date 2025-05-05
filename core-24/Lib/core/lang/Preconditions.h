//
// Created by brunshweeck on 03/05/25.
//

#ifndef CORE_LANG_PRECONDITIONS_H
#define CORE_LANG_PRECONDITIONS_H
#include "Object.h"

namespace core
{
    /// The class @c Precondition contains utility methods to check if state or arguments are correct.
    class Preconditions $final : public Object
    {
        Preconditions() = default;

    public:
        ~Preconditions() override = default;

        static gint checkIndex(gint index, gint length);
        static gint checkIndexFromRange(gint start, gint end, gint length);
        static gint checkIndexFromSize(gint start, gint size, gint length);
        static gint checkIndexForAdding(gint index, gint length);
    };
} // core

#endif // CORE_LANG_PRECONDITIONS_H
