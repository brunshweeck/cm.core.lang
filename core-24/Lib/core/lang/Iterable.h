//
// Created by brunshweeck on 4/16/25.
//

#ifndef CORE_LANG_ITERABLE_H
#define CORE_LANG_ITERABLE_H

#include "Class.h"

namespace core
{
    namespace lang
    {
        /// Implementing this interface allows an object to be the target of the enhanced @c for statement (sometimes called the "for-each loop" statement).
        /// @tparam T The type of elements returned by the iterator.
        template <class T>
        class Iterable : public virtual Object
        {
            class ForLoopIterator $final : public Object
            {
                Iterable& iterable;
                gint index = -1;
                gboolean closed = false;
                // todo: add internal iterator field

                CORE_FAST CORE_EXPLICIT ForLoopIterator(Iterable& iterable): iterable(iterable)
                {
                    // todo: complete this constructor, while initialize internal iterator fields
                }

                CORE_FAST CORE_EXPLICIT ForLoopIterator(Iterable& iterable, gint index): iterable(iterable),
                    index(index), closed(index == -1)
                {
                }

            public:
                ForLoopIterator& operator++()
                {
                    index++;
                    // todo: complete this content of this method
                    return *this;
                }

                T& operator*() const { CORE_UNREACHABLE(); }

                gboolean equals(const Object& other) const override
                {
                    if (this == &other)
                        return true;
                    if (!Class<ForLoopIterator>::hasInstance(other))
                        return false;
                    ForLoopIterator const& otherIter = $cast(ForLoopIterator const&, other);
                    if (&iterable != &otherIter)
                        return false;
                    if (closed)
                        return otherIter.closed;
                    return index == otherIter.index;
                }
            };

        protected:
            Iterable() = default;

        public:
            ~Iterable() override = default;

            ForLoopIterator begin() { return ForLoopIterator(*this); }
            ForLoopIterator end() { return ForLoopIterator(*this, -1); }
            // todo: adjust the code to const version support for method begin()
            // todo: adjust the code to const version support for method end()

            Iterable& clone() const override;
        };
    } // lang
} // core

#endif // CORE_LANG_ITERABLE_H
