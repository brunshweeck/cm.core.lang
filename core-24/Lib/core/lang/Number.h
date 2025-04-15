//
// Created by brunshweeck on 4/16/25.
//

#ifndef CORE_LANG_NUMBER_H
#define CORE_LANG_NUMBER_H

#include "Object.h"

namespace core
{
    namespace lang
    {
        ///  The class @c Number is the superclass of platform classes representing numerics values that are convertible to the primitive types @c gbyte, @c gshort, @c gint, @c glong, @c gfloat, @c gdouble.
        ///  For platform classes, the conversion is often analogous to a narrowing primitive conversion or a widening primitive conversion for converting between primitive types.
        ///  Therefore, conversions may lose information about the overall magnitude of a numeric value, may lose precision, and may even return a result of a different sign than the input.
        class Number : public virtual Object
        {
        protected:
            Number() = default;

        public:
            ~Number() override = default;

            /// Returns the value of the specified number as an @c int.
            /// @return The numeric value represented by this object after conversion to type @c gint
            virtual gint intValue() const = 0;

            /// Returns the value of the specified number as a @c long.
            /// @return The numeric value represented by this object after conversion to type @c glong
            virtual glong longValue() const = 0;

            /// Returns the value of the specified number as a @c float.
            /// @return The numeric value represented by this object after conversion to type @c gfloat
            virtual gfloat floatValue() const = 0;

            /// Returns the value of the specified number as a @c double.
            /// @return The numeric value represented by this object after conversion to type @c gdouble
            virtual gdouble doubleValue() const = 0;

            /// Returns the value of the specified number as a @c byte.
            /// @return The numeric value represented by this object after conversion to type @c gbyte
            virtual gbyte byteValue() const;

            /// Returns the value of the specified number as a @c short.
            /// @return The numeric value represented by this object after conversion to type @c gshort
            virtual gshort shortValue() const;
        };
    } // lang
} // core

#endif // CORE_LANG_NUMBER_H
