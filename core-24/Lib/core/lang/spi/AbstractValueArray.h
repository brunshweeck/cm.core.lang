//
// Created by brunshweeck on 4/28/25.
//

#ifndef CORE_LANG_ABSTRACTVALUEARRAY_H
#define CORE_LANG_ABSTRACTVALUEARRAY_H
#include "AbstractArray.h"

namespace core
{
    namespace lang
    {
        namespace spi
        {
            template <class Element, class ValueArray>
            class AbstractValueArray : public AbstractArray
            {
                friend ValueArray;
                $alias(Values, typename Class<Element>::Pointer);

                Values values;

            protected:
                AbstractValueArray() = default;

            public:
                ~AbstractValueArray() override = default;
                gint length() const override;
                gboolean isEmpty() const override;
                virtual Element& get(gint index) = 0;
                virtual const Element& get(gint index) const;
                virtual void set(gint index, const Element &value);

            };
        } // spi
    } // lang
} // core

#endif // CORE_LANG_ABSTRACTVALUEARRAY_H
