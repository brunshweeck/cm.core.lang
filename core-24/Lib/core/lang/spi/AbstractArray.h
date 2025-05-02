//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ABSTRACTARRAY_H
#define CORE_LANG_ABSTRACTARRAY_H

#include <initializer_list>
#include <core/lang/Object.h>

namespace core::lang::spi
{
    class AbstractArray : public Object
    {
    protected:
        AbstractArray() = default;

    public:
        ~AbstractArray() override = default;
        CORE_SET_AS_NON_COPYABLE_CLASS(AbstractArray);
        virtual gint length() const = 0;
        virtual gboolean isEmpty() const = 0;
        Object& clone() const override = 0;

    protected:
        class AbstractIteratorStep : public Object
        {
        protected:
            AbstractIteratorStep() = default;

        public:
            ~AbstractIteratorStep() override = default;
            virtual AbstractIteratorStep& next() = 0;
            virtual gboolean isDone() const = 0;
            AbstractIteratorStep& operator++();
            AbstractIteratorStep& clone() const $final;

            gboolean equals(const Object& other) const override;

        private:
            virtual gint position() const = 0;
            virtual const Object& target() const = 0;
        };
    };
} // core::lang::spi

#endif // CORE_LANG_ABSTRACTARRAY_H
