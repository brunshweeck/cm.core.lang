//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ABSTRACTPRIMITIVEARRAY_H
#define CORE_LANG_ABSTRACTPRIMITIVEARRAY_H
#include "AbstractArray.h"
#include "AbstractValueArray.h"
#include <core/lang/Class.h>

namespace core::lang::spi
{
    template <class Element, class Array>
    class AbstractPrimitiveArray : public AbstractArray
    {
        friend Array;
        $alias(Value, typename Class<Element>::Primitive);
        $alias(Values, typename Class<Value>::Pointer);
        $alias(VarArgs, std::initializer_list<Value>);
        CORE_FAST_ASSERT(Class<Element>::isSlimmed());
        CORE_FAST_ASSERT(Class<Object>::isBaseOf<Element>());
        CORE_FAST_ASSERT(Class<Value>::isPrimitive());

        Values values = {};
        gint length = {};

    protected:
        AbstractPrimitiveArray() = default;

    public:
        ~AbstractPrimitiveArray() override = default;
        virtual Value& get(gint index) = 0;
        virtual const Value& get(gint index) const = 0;
        virtual Value set(gint index, Value newValue) = 0;
        Object& clone() const override = 0;

        template <class Matrix2D>
        class AbstractMatrix2D : public AbstractValueArray<Array, Matrix2D>
        {
            friend Matrix2D;

        protected:
            AbstractMatrix2D() = default;

        public:
            ~AbstractMatrix2D() override = default;
            gint length() const override = 0;
            gboolean isEmpty() const override = 0;
            Array& get(gint index) override = 0;
            const Array& get(gint index) const override = 0;
            void set(gint index, const Array& value) override = 0;
            virtual Value& get(gint xIndex, gint yIndex) = 0;
            virtual const Value& get(gint xIndex, gint yIndex) const = 0;
            virtual Value set(gint xIndex, gint yIndex, const Value& value) = 0;

            template <class Matrix3D>
            class AbstractMatrix3D : public AbstractValueArray<Matrix2D, Matrix3D>
            {
                friend Matrix3D;

            protected:
                AbstractMatrix3D() = default;

            public:
                ~AbstractMatrix3D() override = default;
                gint length() const override = 0;
                gboolean isEmpty() const override = 0;
                Matrix2D& get(gint index) override = 0;
                const Matrix2D& get(gint index) const override = 0;
                void set(gint index, const Matrix2D& value) override = 0;
                virtual Array& get(gint xIndex, gint yIndex) = 0;
                virtual const Array& get(gint xIndex, gint yIndex) const = 0;
                virtual void set(gint xIndex, gint yIndex, const Array& value) = 0;
                virtual Value& get(gint xIndex, gint yIndex, gint zIndex) = 0;
                virtual const Value& get(gint xIndex, gint yIndex, gint zIndex) const = 0;
                virtual Value set(gint xIndex, gint yIndex, gint zIndex, Value value) = 0;
            };
        };

    private:
        class AbstractStep : public AbstractIteratorStep
        {
        protected:
            AbstractStep() = default;

        public:
            ~AbstractStep() override = default;
            virtual Value& get() = 0;
            AbstractStep& next() override = 0;
            gboolean isDone() const override = 0;
            Value& operator*() const { return get(); }

        private:
            gint position() const override = 0;
            const Object& target() const override = 0;
        };

        class AbstractConstantStep : public AbstractIteratorStep
        {
        protected:
            AbstractConstantStep() = default;

        public:
            ~AbstractConstantStep() override = default;
            virtual const Value& get() = 0;
            AbstractConstantStep& next() override = 0;
            gboolean isDone() const override = 0;
            const Value& operator*() const { return get(); }

        private:
            gint position() const override = 0;
            const Object& target() const override = 0;
        };
    };
} // core::lang::spi

#endif // CORE_LANG_ABSTRACTPRIMITIVEARRAY_H
