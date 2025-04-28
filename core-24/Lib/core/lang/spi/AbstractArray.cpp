//
// Created by brunshweeck on 4/27/25.
//

#include "AbstractArray.h"

namespace core
{
    namespace lang
    {
        namespace spi
        {
            gint AbstractArray::reservePlaces(gint length)
            {
                count = length;
            }
        } // spi
    } // lang
} // core
