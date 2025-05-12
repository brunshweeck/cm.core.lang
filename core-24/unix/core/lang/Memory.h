//
// Created by brunshweeck on 10/05/25.
//

#ifndef CORE_LANG_MEMORY_H
#define CORE_LANG_MEMORY_H

#include <core/lang/Class.h>
#include <core/lang/Object.h>

namespace core::lang
{
    class Memory : public Object
    {
        $alias(__addr_t, Class<void>::Pointer);
        $alias(__address_t, Class<__addr_t>::Pointer);
        $alias(Bytes, Class<gbyte>::Pointer);
        $alias(Shorts, Class<gshort>::VolatilePointer);
        $alias(Ints, Class<gint>::VolatilePointer);
        $alias(Longs, Class<glong>::VolatilePointer);

        Memory() = default;

    public:
        ~Memory() override = default;

        static CORE_FAST glong HEAP_WORD_SIZE = CORE_PROCESSOR_WORDSIZE;

        static CORE_FASTCALL glong allocate(glong sizeInBytes);

        static CORE_FASTCALL glong allocate(glong sizeInBytes, glong alignment);

        static CORE_FASTCALL glong reallocate(glong address, glong sizeInBytes);

        static CORE_FASTCALL glong reallocate(glong address, glong sizeInBytes, glong alignment);

        static CORE_FASTCALL void deallocate(glong address);

        static CORE_FASTCALL void fill(glong address, glong sizeInBytes, gbyte value);

        static CORE_FASTCALL void copy(glong sourceAddress, glong destinationAddress, glong sizeInBytes);

        static CORE_FASTCALL void copySwap(glong sourceAddress, glong destinationAddress, glong sizeInBytes,
                                           glong elementSize);

        static CORE_FASTCALL gint compare(glong sourceAddress, glong destinationAddress, glong sizeInBytes);

        static CORE_FASTCALL void shiftLeft(glong address, glong distanceInBytes, glong sizeInBytes);

    private:
        static CORE_FASTCALL glong alignSizeToHeapWordSize(glong sizeInBytes);

        static CORE_FASTCALL glong reallocate(glong address, glong oldSize, glong sizeInBytes, glong alignment);
    };
} // core::lang

#endif // CORE_LANG_MEMORY_H
