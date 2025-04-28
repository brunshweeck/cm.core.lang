//
// Created by brunshweeck on 4/27/25.
//

#ifndef CORE_LANG_ABSTRACTOBJECTARRAY_H
#define CORE_LANG_ABSTRACTOBJECTARRAY_H
#include "AbstractArray.h"
#include "../Class.h"

namespace core::lang::spi
{
    class AbstractObjectArray : public AbstractArray
    {
        $alias(Values, Class<Object>::Pointer);

        Values mutable values;

    protected:
        CORE_EXPLICIT AbstractObjectArray(gint length = 0);
        Object& getObject(gint index);
        const Object& getObject(gint index) const;
        gboolean checkObject(gint index) const;
        Object& setObject(gint index, Object& newObject);
        void setAll(const AbstractObjectArray& newArray);
        void swapContents(AbstractObjectArray& newArray);

    public:
        ~AbstractObjectArray() override;
        CORE_SET_AS_NON_COPYABLE_CLASS(AbstractObjectArray)
        gint length() const override;
        gboolean isEmpty() const override;
        gboolean equals(const Object& other) const override;
        gint hash() const override;
        String toString() const override;
        AbstractObjectArray& clone() const override;

    private:
        gint reservePlaces(gint length) $final;
    };
} // core::lang::spi

#endif // CORE_LANG_ABSTRACTOBJECTARRAY_H
