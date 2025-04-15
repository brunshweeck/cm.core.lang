//
// Created by brunshweeck on 4/15/25.
//

#ifndef CORE_LANG_COMPARABLE_H
#define CORE_LANG_COMPARABLE_H
#include "Object.h"

namespace core
{
    namespace lang
    {
        /// The class @c Comparable is defined to impose total ordering on the objects of each class that implement it.
        /// This ordering is referred to as the class's @a natural @a ordering, and class's @c Comparable.compareTo method refer to as it <em>natural ordering</em>.
        /// Lists (and arrays) of objects that implements this interface can be sorted automatically by @c core.util::Collection.sort method (and @c core.util::Arrays.sort method).
        /// Objects that implement this interface can be used as keys in the @a sorted @a maps or as element in the @a sorted @a sets, without the need to specify the @a comparator.
        /// The natural ordering for a class @c C is said to be @a consistent @a with @a equals if and only if @code X.compareTo(Y) == 0 @endcode has same boolean value as @c X.equals(Y) for every @c X and @x Y, instance of class @c C.
        /// It is strongly recommended (though not required) that natural orderings be consistent with equals.
        /// This is so because sorted sets (and sorted maps) without explicit comparators behave "strangely" when they are used with elements (or keys) whose natural ordering is inconsistent with equals.
        /// In particular, such a sorted setValue (or sorted map) violates the general contract for setValue (or map), which is defined in terms of the @c equals method.
        /// For example, if one adds two keys @c a and @c b such that @code !a.equals(b) && (a.compareTo(b) == 0) @endcode to a sorted set that does not use an explicit comparator, the second @c add operation return false (and the size of the sorted setValue does not increase) because @c a and @c b are equivalent from the sorted set's perspective.
        /// For the mathematically inclined, the @a relation that defines the natural ordering on a given class C is: for all @c x and @c y, such that @code x.compareTo(y) <= 0 @endcode .
        /// The @a quotient for this total order is: for all @c x and @c y, such that @code x.compareTo(y) == 0 @endcode .
        /// @tparam T The type of objects that this object may be compared to.
        template <class T>
        class Comparable : public virtual Object
        {
        protected:
            Comparable() = default;

        public:
            ~Comparable() override = default;

            /// Compares this object with the specified object for order.
            /// Returns negative integer, zero, or a positive integer as this object is less than, equal to, or greater than the specified object.
            /// The implementor must ensure @a signum: @code Math.signum(x.compareTo(y)) == -Math.signum(y.compare(x)) @endcode for every @c x and @c y.
            /// This implies that @c x.compareTo(y) throw an exception if and only if @c y.compareTo(x) throw an exception.
            /// The implementor must also ensure that the relation is transitive: @code (x.compareTo(y) > 0) && (y.compareTo(z) > 0) @endcode implies @code x.compareTo(z) > 0 @endcode .
            /// Finally, the implementor must ensure that @code x.compareTo(y) == 0 @endcode implies that @code Math.signum(x.compareTo(z)) == Math.signum(y.compareTo(z)) @endcode , for all @c z.
            /// @note It is strongly recommended, but @a not strictly required that @code (x.compareTo(y)==0) == (x.equals(y)) @endcode .
            /// Generally speaking, any class that implements the @c Comparable class and violates this condition should clearly indicate this fact.
            /// The recommended language is "Note: this class has a natural ordering that is inconsistent with equals."
            virtual gint compareTo(T const& other) const = 0;
        };
    } // lang
} // core

#endif // CORE_LANG_COMPARABLE_H
