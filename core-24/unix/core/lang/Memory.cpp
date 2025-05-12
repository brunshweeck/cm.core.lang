//
// Created by brunshweeck on 10/05/25.
//

#include "Memory.h"

#include <cstdlib>
#include <core/lang/Null.h>

#include "Intrinsic.h"
#include <core/lang/Integer.h>
#include <core/lang/Long.h>
#include <core/lang/Short.h>


namespace core::lang
{
    glong Memory::allocate(glong sizeInBytes) {
        glong heapSize = alignSizeToHeapWordSize(sizeInBytes);
        if (heapSize == 0) return 0L;
        return allocate(heapSize, HEAP_WORD_SIZE);
    }

    glong Memory::allocate(glong sizeInBytes, glong alignment) {
        return reallocate(0L, -1L, sizeInBytes, alignment);
    }

    glong Memory::reallocate(glong address, glong sizeInBytes) {
        glong heapSize = alignSizeToHeapWordSize(sizeInBytes);
        if (heapSize == 0) {
            deallocate(address);
            return 0L;
        }
        return reallocate(address, -1L, heapSize, HEAP_WORD_SIZE);
    }

    glong Memory::reallocate(glong address, glong sizeInBytes, glong alignment) {
        glong heapSize = alignSizeToHeapWordSize(sizeInBytes);
        if (heapSize == 0) {
            deallocate(address);
            return 0L;
        }
        return reallocate(address, -1L, heapSize, alignment);
    }

    void Memory::deallocate(glong address) {
        if (address >= 0) {
            __address_t target = (__address_t) address;
            free(target[-1]);
        }
    }

    void Memory::fill(glong address, glong sizeInBytes, gbyte value) {
        if (sizeInBytes == 0L) return;
        __builtin_memset((__addr_t) address, value, sizeInBytes);
    }

    void Memory::copy(glong sourceAddress, glong destinationAddress, glong sizeInBytes) {
        if (sizeInBytes == 0L) return;
        __builtin_memcpy((__addr_t) destinationAddress, (__addr_t) sourceAddress, sizeInBytes);
    }

    void Memory::copySwap(glong sourceAddress, glong destinationAddress, glong sizeInBytes, glong elementSize) {
        if (sizeInBytes == 0L) return;
        elementSize = elementSize % 8;
        switch (elementSize) {
            case 2:
                for (glong i = 0; i < sizeInBytes; i += elementSize) {
                    gshort value = Intrinsic::loadShort(sourceAddress, Intrinsic::SEQUENTIAL);
                    Intrinsic::storeShort(destinationAddress, Short::reverseBytes(value), Intrinsic::SEQUENTIAL);
                    sourceAddress += elementSize;
                    destinationAddress += elementSize;
                }
                break;
            case 4:
                for (glong i = 0; i < sizeInBytes; i += elementSize) {
                    gint value = Intrinsic::loadInt(sourceAddress, Intrinsic::SEQUENTIAL);
                    Intrinsic::storeInt(destinationAddress, Integer::reverseBytes(value), Intrinsic::SEQUENTIAL);
                    sourceAddress += elementSize;
                    destinationAddress += elementSize;
                }
                break;
            case 8:
                for (glong i = 0; i < sizeInBytes; i += elementSize) {
                    glong value = Intrinsic::loadLong(sourceAddress, Intrinsic::SEQUENTIAL);
                    Intrinsic::storeLong(destinationAddress, Long::reverseBytes(value), Intrinsic::SEQUENTIAL);
                    sourceAddress += elementSize;
                    destinationAddress += elementSize;
                }
                break;
            default:
                return copy(sourceAddress, destinationAddress, sizeInBytes);
        }
    }

    gint Memory::compare(glong sourceAddress, glong destinationAddress, glong sizeInBytes) {
        if (sizeInBytes == 0L) return 0;
        return __builtin_memcmp((__addr_t) sourceAddress, (__addr_t) destinationAddress, sizeInBytes);
    }

    void Memory::shiftLeft(glong address, glong distanceInBytes, glong sizeInBytes) {
        if (sizeInBytes == 0L) return;
        copy(address, address + distanceInBytes, sizeInBytes);
    }

    glong Memory::alignSizeToHeapWordSize(glong sizeInBytes) {
        if (sizeInBytes >= 0)
            return sizeInBytes + HEAP_WORD_SIZE - 1 & ~(HEAP_WORD_SIZE - 1);
        return 0;
    }

    glong Memory::reallocate(glong address, glong oldSize, glong sizeInBytes, glong alignment) {
        __addr_t old = address == 0L ? null : ((__address_t) address)[-1];
        if (alignment < HEAP_WORD_SIZE) {
            __address_t new_ = (__address_t) realloc(old, sizeInBytes + HEAP_WORD_SIZE);
            if (new_ == null) return 0L;
            if ((__addr_t) new_ == old) return address;
            *new_ = (__addr_t) new_;
            return (glong) (new_ + 1);
        }
        // malloc returns pointers aligned at least at sizeof(SIZE_T) boundaries but usually more (8- or 16-byte boundaries).
        // So we overallocate by alignment-sizeof(SIZE_T) bytes, so we're guaranteed to find somewhere within the first alignment-sizeof(SIZE_T) that is properly aligned.

        // However, we need to store the actual pointer, so we need to actually allocate size + alignment anyway.
        glong offset = address == 0L ? 0L : (Bytes) address - (Bytes) old;
        __addr_t new_ = (__addr_t) realloc(old, sizeInBytes + alignment);
        if (new_ == null) return 0L;
        glong faked = (glong) new_ + alignment;
        faked &= ~(alignment - 1);
        __address_t faked_ = (__address_t) faked;
        if (address != 0L) {
            glong offset2 = (Bytes) faked_ - (Bytes) new_;
            if (offset != offset2)
                __builtin_memcpy(faked_, (Bytes) new_ + offset, oldSize < sizeInBytes ? oldSize : sizeInBytes);
        }

        // now save the value of the real pointer at faked-sizeof(LPVOID)
        // by construction, alignment > sizeof(LPVOID) and is a power of 2, so
        // faked-sizeof(LPVOID) is properly aligned for a pointer
        faked_[-1] = new_;
        return (glong) faked_;
    }
} // lang
// core
