//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ABSTRACTARRAY_H
#define CORE_LANG_ABSTRACTARRAY_H

#include "../Object.h"
#include <initializer_list>

namespace core::lang::spi
{
    class AbstractArray : public Object
    {
        gint count;

    protected:
        CORE_EXPLICIT AbstractArray(gint length = 0);

    public:
        ~AbstractArray() override = default;

        CORE_SET_AS_NON_COPYABLE_CLASS(AbstractArray);

        virtual gint length() const = 0;
        virtual gboolean isEmpty() const = 0;
        AbstractArray& clone() const override;

    private:
        virtual gint reservePlaces(gint length);
    };
} // core::lang::spi

#endif // CORE_LANG_ABSTRACTARRAY_H
