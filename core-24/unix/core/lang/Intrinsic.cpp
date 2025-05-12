//
// Created by brunshweeck on 10/05/25.
//

#include "Intrinsic.h"

#include "../../../Lib/core/lang/Class.h"


namespace core::lang
{
    $alias(Bytes, Class<gbyte>::Pointer);
    $alias(Shorts, Class<gshort>::Pointer);
    $alias(Ints, Class<gint>::Pointer);
    $alias(Longs, Class<glong>::Pointer);

    static Intrinsic::Mode failureMode(Intrinsic::Mode mode) {
        switch (mode) {
            case Intrinsic::RELEASE: return Intrinsic::RELAXED;
            case Intrinsic::ACQUIRE_AND_RELEASE: return Intrinsic::ACQUIRE;
            case Intrinsic::RELAXED:
            case Intrinsic::CONSUME:
            case Intrinsic::ACQUIRE:
            case Intrinsic::SEQUENTIAL:
            default: return mode;
        }
    }

    gbyte Intrinsic::loadByte(glong address, Mode mode) {
        return __atomic_load_n((Bytes) address, mode);
    }

    gshort Intrinsic::loadShort(glong address, Mode mode) {
        return __atomic_load_n((Shorts) address, mode);
    }

    gint Intrinsic::loadInt(glong address, Mode mode) {
        return __atomic_load_n((Ints) address, mode);
    }

    glong Intrinsic::loadLong(glong address, Mode mode) {
        return __atomic_load_n((Longs) address, mode);
    }

    void Intrinsic::storeByte(glong address, gbyte value, Mode mode) {
        __atomic_store_n((Bytes) address, value, mode);
    }

    void Intrinsic::storeShort(glong address, gshort value, Mode mode) {
        __atomic_store_n((Shorts) address, value, mode);
    }

    void Intrinsic::storeInt(glong address, gint value, Mode mode) {
        __atomic_store_n((Ints) address, value, mode);
    }

    void Intrinsic::storeLong(glong address, glong value, Mode mode) {
        __atomic_store_n((Longs) address, value, mode);
    }

    gbyte Intrinsic::exchangeByte(glong address, gbyte value, Mode mode) {
        return __atomic_exchange_n((Bytes) address, value, mode);
    }

    gshort Intrinsic::exchangeShort(glong address, gshort value, Mode mode) {
        return __atomic_exchange_n((Shorts) address, value, mode);
    }

    gint Intrinsic::exchangeInt(glong address, gint value, Mode mode) {
        return __atomic_exchange_n((Ints) address, value, mode);
    }

    glong Intrinsic::exchangeLong(glong address, glong value, Mode mode) {
        return __atomic_exchange_n((Longs) address, value, mode);
    }

    gboolean Intrinsic::compareAndExchangeByte(glong address, gbyte expected, gbyte desired, gboolean weakly,
                                               Mode mode) {
        return __atomic_compare_exchange_n((Bytes) address, &expected, desired, weakly, mode, failureMode(mode));
    }

    gboolean Intrinsic::compareAndExchangeShort(glong address, gshort expected, gshort desired, gboolean weakly,
                                                Mode mode) {
        return __atomic_compare_exchange_n((Shorts) address, &expected, desired, weakly, mode, failureMode(mode));
    }

    gboolean Intrinsic::compareAndExchangeInt(glong address, int expected, int desired, gboolean weakly, Mode mode) {
        return __atomic_compare_exchange_n((Ints) address, &expected, desired, weakly, mode, failureMode(mode));
    }

    gboolean Intrinsic::compareAndExchangeLong(glong address, long expected, long desired, gboolean weakly, Mode mode) {
        return __atomic_compare_exchange_n((Longs) address, &expected, desired, weakly, mode, failureMode(mode));
    }

    void Intrinsic::threadFence(Mode mode) {
        return __atomic_thread_fence(mode);
    }

    void Intrinsic::signalFence(Mode mode) {
        return __atomic_signal_fence(mode);
    }

    gbyte Intrinsic::loadAndAddByte(glong address, gbyte value, Mode mode) {
        return __atomic_fetch_add((Bytes) address, value, mode);
    }

    gshort Intrinsic::loadAndAddShort(glong address, gshort value, Mode mode) {
        return __atomic_fetch_add((Shorts) address, value, mode);
    }

    gint Intrinsic::loadAndAddInt(glong address, gint value, Mode mode) {
        return __atomic_fetch_add((Ints) address, value, mode);
    }

    glong Intrinsic::loadAndAddLong(glong address, glong value, Mode mode) {
        return __atomic_fetch_add((Longs) address, value, mode);
    }

    gbyte Intrinsic::loadAndBitwiseAndByte(glong address, gbyte value, Mode mode) {
        return __atomic_fetch_and((Bytes) address, value, mode);
    }

    gshort Intrinsic::loadAndBitwiseAndShort(glong address, gshort value, Mode mode) {
        return __atomic_fetch_and((Shorts) address, value, mode);
    }

    gint Intrinsic::loadAndBitwiseAndInt(glong address, gint value, Mode mode) {
        return __atomic_fetch_and((Ints) address, value, mode);
    }

    glong Intrinsic::loadAndBitwiseAndLong(glong address, glong value, Mode mode) {
        return __atomic_fetch_and((Longs) address, value, mode);
    }

    gbyte Intrinsic::loadAndBitwiseOrByte(glong address, gbyte value, Mode mode) {
        return __atomic_fetch_or((Bytes) address, value, mode);
    }

    gshort Intrinsic::loadAndBitwiseOrShort(glong address, gshort value, Mode mode) {
        return __atomic_fetch_or((Shorts) address, value, mode);
    }

    gint Intrinsic::loadAndBitwiseOrInt(glong address, gint value, Mode mode) {
        return __atomic_fetch_or((Ints) address, value, mode);
    }

    glong Intrinsic::loadAndBitwiseOrLong(glong address, glong value, Mode mode) {
        return __atomic_fetch_or((Longs) address, value, mode);
    }

    gbyte Intrinsic::loadAndBitwiseXorByte(glong address, gbyte value, Mode mode) {
        return __atomic_fetch_xor((Bytes) address, value, mode);
    }

    gshort Intrinsic::loadAndBitwiseXorShort(glong address, gshort value, Mode mode) {
        return __atomic_fetch_xor((Shorts) address, value, mode);
    }

    gint Intrinsic::loadAndBitwiseXorInt(glong address, gint value, Mode mode) {
        return __atomic_fetch_xor((Ints) address, value, mode);
    }

    glong Intrinsic::loadAndBitwiseXorLong(glong address, glong value, Mode mode) {
        return __atomic_fetch_xor((Longs) address, value, mode);
    }
} // core::lang
