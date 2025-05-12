//
// Created by brunshweeck on 10/05/25.
//

#include "VarHandle.h"

#include <core/lang/ByteArray.h>
#include <core/lang/Cache.h>
#include <core/lang/Character.h>
#include <core/lang/Double.h>
#include <core/lang/Float.h>
#include <core/lang/IllegalArgumentException.h>
#include <core/lang/Intrinsic.h>
#include <core/lang/Long.h>
#include <core/lang/Memory.h>
#include <core/lang/OutOfMemoryError.h>
#include <core/lang/Short.h>
#include <core/lang/spi/AbstractObjectArray.h>


namespace core::misc
{
    $alias(Address, Class<Object>::Pointer);
    $alias(Address2D, Class<Address>::Pointer);
    using spi::AbstractArray;
    using spi::AbstractObjectArray;

    gboolean VarHandle::getBoolean(const Object &object, glong offset) {
        return getByte(object, offset) != 0;
    }

    gbyte VarHandle::getByte(const Object &object, glong offset) {
        return Intrinsic::loadByte(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gshort VarHandle::getShort(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gchar VarHandle::getChar(const Object &object, glong offset) {
        return (gchar) Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gint VarHandle::getInt(const Object &object, glong offset) {
        return Intrinsic::loadInt(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE_AND_RELEASE);
    }

    glong VarHandle::getLong(const Object &object, glong offset) {
        return Intrinsic::loadLong(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gfloat VarHandle::getFloat(const Object &object, glong offset) {
        return Float::fromIntBits(getInt(object, offset));
    }

    gdouble VarHandle::getDouble(const Object &object, glong offset) {
        return Double::fromLongBits(getLong(object, offset));
    }

    void VarHandle::set(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        set(object, offset, value);
    }

    void VarHandle::set(const Object &object, glong offset, gbyte newValue) {
        Intrinsic::storeByte(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    void VarHandle::set(const Object &object, glong offset, gshort newValue) {
        Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    void VarHandle::set(const Object &object, glong offset, gchar newValue) {
        Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), (gshort) newValue,
                              Intrinsic::ACQUIRE_AND_RELEASE);
    }

    void VarHandle::set(const Object &object, glong offset, gint newValue) {
        Intrinsic::storeInt(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    void VarHandle::set(const Object &object, glong offset, glong newValue) {
        Intrinsic::storeLong(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    void VarHandle::set(const Object &object, glong offset, gfloat newValue) {
        set(object, offset, Float::toRawIntBits(newValue));
    }

    void VarHandle::set(const Object &object, glong offset, gdouble newValue) {
        set(object, offset, Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::getBooleanVolatile(const Object &object, glong offset) {
        return getByteVolatile(object, offset) != 0;
    }

    gbyte VarHandle::getByteVolatile(const Object &object, glong offset) {
        return Intrinsic::loadByte(StaticCache::resolveOffset(object, offset), Intrinsic::SEQUENTIAL);
    }

    gshort VarHandle::getShortVolatile(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::SEQUENTIAL);
    }

    gchar VarHandle::getCharVolatile(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::SEQUENTIAL);
    }

    gint VarHandle::getIntVolatile(const Object &object, glong offset) {
        return Intrinsic::loadInt(StaticCache::resolveOffset(object, offset), Intrinsic::SEQUENTIAL);
    }

    glong VarHandle::getLongVolatile(const Object &object, glong offset) {
        return Intrinsic::loadLong(StaticCache::resolveOffset(object, offset), Intrinsic::SEQUENTIAL);
    }

    gfloat VarHandle::getFloatVolatile(const Object &object, glong offset) {
        return Float::fromIntBits(getIntVolatile(object, offset));
    }

    gdouble VarHandle::getDoubleVolatile(const Object &object, glong offset) {
        return Double::fromLongBits(getLongVolatile(object, offset));
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        setVolatile(object, offset, value);
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gbyte newValue) {
        return Intrinsic::storeByte(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::SEQUENTIAL);
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gshort newValue) {
        return Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::SEQUENTIAL);
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gchar newValue) {
        return Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), (gshort) newValue,
                                     Intrinsic::SEQUENTIAL);
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gint newValue) {
        return Intrinsic::storeInt(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::SEQUENTIAL);
    }

    void VarHandle::setVolatile(const Object &object, glong offset, glong newValue) {
        return Intrinsic::storeLong(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::SEQUENTIAL);
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gfloat newValue) {
        setVolatile(object, offset, Float::toRawIntBits(newValue));
    }

    void VarHandle::setVolatile(const Object &object, glong offset, gdouble newValue) {
        setVolatile(object, offset, Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::getBooleanOpaque(const Object &object, glong offset) {
        return getByteOpaque(object, offset) != 0;
    }

    gbyte VarHandle::getByteOpaque(const Object &object, glong offset) {
        return Intrinsic::loadByte(StaticCache::resolveOffset(object, offset), Intrinsic::RELAXED);
    }

    gshort VarHandle::getShortOpaque(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::RELAXED);
    }

    gchar VarHandle::getCharOpaque(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::RELAXED);
    }

    gint VarHandle::getIntOpaque(const Object &object, glong offset) {
        return Intrinsic::loadInt(StaticCache::resolveOffset(object, offset), Intrinsic::RELAXED);
    }

    glong VarHandle::getLongOpaque(const Object &object, glong offset) {
        return Intrinsic::loadLong(StaticCache::resolveOffset(object, offset), Intrinsic::RELAXED);
    }

    gfloat VarHandle::getFloatOpaque(const Object &object, glong offset) {
        return Float::fromIntBits(getIntOpaque(object, offset));
    }

    gdouble VarHandle::getDoubleOpaque(const Object &object, glong offset) {
        return Double::fromLongBits(getLongOpaque(object, offset));
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        setOpaque(object, offset, value);
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gbyte newValue) {
        Intrinsic::storeByte(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELAXED);
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gshort newValue) {
        Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELAXED);
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gchar newValue) {
        Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), (gshort) newValue, Intrinsic::RELAXED);
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gint newValue) {
        Intrinsic::storeInt(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELAXED);
    }

    void VarHandle::setOpaque(const Object &object, glong offset, glong newValue) {
        Intrinsic::storeLong(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELAXED);
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gfloat newValue) {
        setOpaque(object, offset, Float::toRawIntBits(newValue));
    }

    void VarHandle::setOpaque(const Object &object, glong offset, gdouble newValue) {
        setOpaque(object, offset, Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::getBooleanAcquire(const Object &object, glong offset) {
        return getByteAcquire(object, offset) != 0;
    }

    gbyte VarHandle::getByteAcquire(const Object &object, glong offset) {
        return Intrinsic::loadByte(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE);
    }

    gshort VarHandle::getShortAcquire(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE);
    }

    gchar VarHandle::getCharAcquire(const Object &object, glong offset) {
        return Intrinsic::loadShort(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE);
    }

    gint VarHandle::getIntAcquire(const Object &object, glong offset) {
        return Intrinsic::loadInt(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE);
    }

    glong VarHandle::getLongAcquire(const Object &object, glong offset) {
        return Intrinsic::loadLong(StaticCache::resolveOffset(object, offset), Intrinsic::ACQUIRE);
    }

    gfloat VarHandle::getFloatAcquire(const Object &object, glong offset) {
        return Float::fromIntBits(getIntAcquire(object, offset));
    }

    gdouble VarHandle::getDoubleAcquire(const Object &object, glong offset) {
        return Double::fromLongBits(getLongAcquire(object, offset));
    }

    void VarHandle::setRelease(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        setRelease(object, offset, value);
    }

    void VarHandle::setRelease(const Object &object, glong offset, gbyte newValue) {
        return Intrinsic::storeByte(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELEASE);
    }

    void VarHandle::setRelease(const Object &object, glong offset, gshort newValue) {
        return Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELEASE);
    }

    void VarHandle::setRelease(const Object &object, glong offset, gchar newValue) {
        return Intrinsic::storeShort(StaticCache::resolveOffset(object, offset), (gshort) newValue, Intrinsic::RELEASE);
    }

    void VarHandle::setRelease(const Object &object, glong offset, gint newValue) {
        return Intrinsic::storeInt(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELEASE);
    }

    void VarHandle::setRelease(const Object &object, glong offset, glong newValue) {
        return Intrinsic::storeLong(StaticCache::resolveOffset(object, offset), newValue, Intrinsic::RELEASE);
    }

    void VarHandle::setRelease(const Object &object, glong offset, gfloat newValue) {
        setRelease(object, offset, Float::toRawIntBits(newValue));
    }

    void VarHandle::setRelease(const Object &object, glong offset, gdouble newValue) {
        setRelease(object, offset, Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gboolean expectedValue, gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return compareAndSet(object, offset, expected, value);
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gbyte expectedValue, gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 false, Intrinsic::RELAXED);
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gshort expectedValue, gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  false, Intrinsic::RELAXED);
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gchar expectedValue, gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, false, Intrinsic::RELAXED);
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gint expectedValue, gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                false, Intrinsic::RELAXED);
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, glong expectedValue, glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 false, Intrinsic::RELAXED);
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gfloat expectedValue, gfloat newValue) {
        return compareAndSet(object, offset, Float::toRawIntBits(expectedValue), Float::toRawIntBits(newValue));
    }

    gboolean VarHandle::compareAndSet(const Object &object, glong offset, gdouble expectedValue, gdouble newValue) {
        return compareAndSet(object, offset, Double::toRawLongBits(expectedValue), Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::compareAndExchange(const Object &object, glong offset, gboolean expectedValue,
                                           gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return compareAndExchange(object, offset, expected, value);
    }

    gbyte VarHandle::compareAndExchange(const Object &object, glong offset, gbyte expectedValue, gbyte newValue) {
        return compareAndSet(object, offset, expectedValue, newValue) ? expectedValue : newValue;
    }

    gshort VarHandle::compareAndExchange(const Object &object, glong offset, gshort expectedValue, gshort newValue) {
        return compareAndSet(object, offset, expectedValue, newValue) ? expectedValue : newValue;
    }

    gchar VarHandle::compareAndExchange(const Object &object, glong offset, gchar expectedValue, gchar newValue) {
        return compareAndSet(object, offset, expectedValue, newValue) ? expectedValue : newValue;
    }

    gint VarHandle::compareAndExchange(const Object &object, glong offset, gint expectedValue, gint newValue) {
        return compareAndSet(object, offset, expectedValue, newValue) ? expectedValue : newValue;
    }

    glong VarHandle::compareAndExchange(const Object &object, glong offset, glong expectedValue, glong newValue) {
        return compareAndSet(object, offset, expectedValue, newValue) ? expectedValue : newValue;
    }

    gfloat VarHandle::compareAndExchange(const Object &object, glong offset, gfloat expectedValue, gfloat newValue) {
        return Float::fromIntBits(compareAndExchange(object, offset, Float::toRawIntBits(expectedValue),
                                                     Float::toRawIntBits(newValue)));
    }

    gdouble VarHandle::compareAndExchange(const Object &object, glong offset, gdouble expectedValue, gdouble newValue) {
        return Double::fromLongBits(compareAndSet(object, offset, Double::toRawLongBits(expectedValue),
                                                  Double::toRawLongBits(newValue)));
    }

    gboolean VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gboolean expectedValue,
                                                  gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return compareAndExchangeAcquire(object, offset, expected, value);
    }

    gbyte VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gbyte expectedValue,
                                               gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 false, Intrinsic::ACQUIRE)
                   ? expectedValue
                   : newValue;
    }

    gshort VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gshort expectedValue,
                                                gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  false, Intrinsic::ACQUIRE)
                   ? expectedValue
                   : newValue;
    }

    gchar VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gchar expectedValue,
                                               gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, false, Intrinsic::ACQUIRE)
                   ? expectedValue
                   : newValue;
    }

    gint VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gint expectedValue, gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                false, Intrinsic::ACQUIRE)
                   ? expectedValue
                   : newValue;
    }

    glong VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, glong expectedValue,
                                               glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 false, Intrinsic::ACQUIRE)
                   ? expectedValue
                   : newValue;
    }

    gfloat VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gfloat expectedValue,
                                                gfloat newValue) {
        return Float::fromIntBits(compareAndExchangeAcquire(object, offset, Float::toRawIntBits(expectedValue),
                                                            Float::toRawIntBits(newValue)));
    }

    gdouble VarHandle::compareAndExchangeAcquire(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue) {
        return Double::fromLongBits(compareAndExchangeAcquire(object, offset, Double::toRawLongBits(expectedValue),
                                                              Double::toRawLongBits(newValue)));
    }

    gboolean VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gboolean expectedValue,
                                                  gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return compareAndExchangeRelease(object, offset, expected, value);
    }

    gbyte VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gbyte expectedValue,
                                               gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 false, Intrinsic::RELEASE)
                   ? expectedValue
                   : newValue;
    }

    gshort VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gshort expectedValue,
                                                gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  false, Intrinsic::RELEASE)
                   ? expectedValue
                   : newValue;
    }

    gchar VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gchar expectedValue,
                                               gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, false, Intrinsic::RELEASE)
                   ? expectedValue
                   : newValue;
    }

    gint VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gint expectedValue, gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                false, Intrinsic::RELEASE)
                   ? expectedValue
                   : newValue;
    }

    glong VarHandle::compareAndExchangeRelease(const Object &object, glong offset, glong expectedValue,
                                               glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 false, Intrinsic::RELEASE)
                   ? expectedValue
                   : newValue;
    }

    gfloat VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gfloat expectedValue,
                                                gfloat newValue) {
        return Float::fromIntBits(compareAndExchangeRelease(object, offset, Float::toRawIntBits(expectedValue),
                                                            Float::toRawIntBits(newValue)));
    }

    gdouble VarHandle::compareAndExchangeRelease(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue) {
        return Double::fromLongBits(compareAndExchangeRelease(object, offset, Double::toRawLongBits(expectedValue),
                                                              Double::toRawLongBits(newValue)));
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gboolean expectedValue,
                                               gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return weakCompareAndSetPlain(object, offset, expected, value);
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gbyte expectedValue,
                                               gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gshort expectedValue,
                                               gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  true, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gchar expectedValue,
                                               gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, true, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gint expectedValue, gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                true, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, glong expectedValue,
                                               glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::ACQUIRE_AND_RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gfloat expectedValue,
                                               gfloat newValue) {
        return weakCompareAndSetPlain(object, offset, Float::toRawIntBits(expectedValue),
                                      Float::toRawIntBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSetPlain(const Object &object, glong offset, gdouble expectedValue,
                                               gdouble newValue) {
        return weakCompareAndSetPlain(object, offset, Double::toRawLongBits(expectedValue),
                                      Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gboolean expectedValue,
                                          gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return weakCompareAndSet(object, offset, expected, value);
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gbyte expectedValue, gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gshort expectedValue, gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  true, Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gchar expectedValue, gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, true, Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gint expectedValue, gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                true, Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, glong expectedValue, glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gfloat expectedValue, gfloat newValue) {
        return weakCompareAndSet(object, offset, Float::toRawIntBits(expectedValue), Float::toRawIntBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSet(const Object &object, glong offset, gdouble expectedValue, gdouble newValue) {
        return weakCompareAndSet(object, offset, Double::toRawLongBits(expectedValue), Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gboolean expectedValue,
                                                 gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return weakCompareAndSetAcquire(object, offset, expected, value);
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gbyte expectedValue,
                                                 gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gshort expectedValue,
                                                 gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  true, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gchar expectedValue,
                                                 gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, true, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gint expectedValue,
                                                 gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                true, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, glong expectedValue,
                                                 glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gfloat expectedValue,
                                                 gfloat newValue) {
        return weakCompareAndSetAcquire(object, offset, Float::toRawIntBits(expectedValue),
                                        Float::toRawIntBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSetAcquire(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue) {
        return weakCompareAndSetAcquire(object, offset, Double::toRawLongBits(expectedValue),
                                        Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gboolean expectedValue,
                                                 gboolean newValue) {
        gbyte expected = expectedValue ? 1 : 0;
        gbyte value = newValue ? 1 : 0;
        return weakCompareAndSetRelease(object, offset, expected, value);
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gbyte expectedValue,
                                                 gbyte newValue) {
        return Intrinsic::compareAndExchangeByte(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gshort expectedValue,
                                                 gshort newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                  true, Intrinsic::RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gchar expectedValue,
                                                 gchar newValue) {
        return Intrinsic::compareAndExchangeShort(StaticCache::resolveOffset(object, offset), (gshort) expectedValue,
                                                  (gshort) newValue, true, Intrinsic::RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gint expectedValue,
                                                 gint newValue) {
        return Intrinsic::compareAndExchangeInt(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                true, Intrinsic::RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, glong expectedValue,
                                                 glong newValue) {
        return Intrinsic::compareAndExchangeLong(StaticCache::resolveOffset(object, offset), expectedValue, newValue,
                                                 true, Intrinsic::RELEASE);
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gfloat expectedValue,
                                                 gfloat newValue) {
        return weakCompareAndSetRelease(object, offset, Float::toRawIntBits(expectedValue),
                                        Float::toRawIntBits(newValue));
    }

    gboolean VarHandle::weakCompareAndSetRelease(const Object &object, glong offset, gdouble expectedValue,
                                                 gdouble newValue) {
        return weakCompareAndSetRelease(object, offset, Double::toRawLongBits(expectedValue),
                                        Double::toRawLongBits(newValue));
    }

    gboolean VarHandle::getAndSet(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        return getAndSet(object, offset, value);
    }

#define loadAndStore(resultType, initializer, valueType, getSuffix, weakCompareSuffix) \
    resultType value = initializer; \
    do { \
        value = get ## valueType ## getSuffix (object, offset);\
    } while (!weakCompareAndSet(object, offset, value, newValue)); \
    return value

    gbyte VarHandle::getAndSet(const Object &object, glong offset, gbyte newValue) {
        loadAndStore(gbyte, 0, Byte, Volatile,);
    }


    gshort VarHandle::getAndSet(const Object &object, glong offset, gshort newValue) {
        loadAndStore(gshort, 0, Short, Volatile,);
    }

    gchar VarHandle::getAndSet(const Object &object, glong offset, gchar newValue) {
        loadAndStore(gchar, 0, Char, Volatile,);
    }

    gint VarHandle::getAndSet(const Object &object, glong offset, gint newValue) {
        loadAndStore(gint, 0, Int, Volatile,);
    }

    glong VarHandle::getAndSet(const Object &object, glong offset, glong newValue) {
        loadAndStore(glong, 0, Long, Volatile,);
    }

    gfloat VarHandle::getAndSet(const Object &object, glong offset, gfloat newValue) {
        return Float::fromIntBits(getAndSet(object, offset, Float::toRawIntBits(newValue)));
    }

    gdouble VarHandle::getAndSet(const Object &object, glong offset, gdouble newValue) {
        return Double::fromLongBits(getAndSet(object, offset, Double::toRawLongBits(newValue)));
    }

    gboolean VarHandle::getAndSetAcquire(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        return getAndSetAcquire(object, offset, value);
    }

    gbyte VarHandle::getAndSetAcquire(const Object &object, glong offset, gbyte newValue) {
        loadAndStore(gbyte, 0, Byte, Acquire, Acquire);
    }

    gshort VarHandle::getAndSetAcquire(const Object &object, glong offset, gshort newValue) {
        loadAndStore(gshort, 0, Short, Acquire, Acquire);
    }

    gchar VarHandle::getAndSetAcquire(const Object &object, glong offset, gchar newValue) {
        loadAndStore(gchar, 0, Char, Acquire, Acquire);
    }

    gint VarHandle::getAndSetAcquire(const Object &object, glong offset, gint newValue) {
        loadAndStore(gint, 0, Int, Acquire, Acquire);
    }

    glong VarHandle::getAndSetAcquire(const Object &object, glong offset, glong newValue) {
        loadAndStore(glong, 0, Long, Acquire, Acquire);
    }

    gfloat VarHandle::getAndSetAcquire(const Object &object, glong offset, gfloat newValue) {
        return Float::fromIntBits(getAndSetAcquire(object, offset, Float::toRawIntBits(newValue)));
    }

    gdouble VarHandle::getAndSetAcquire(const Object &object, glong offset, gdouble newValue) {
        return Double::fromLongBits(getAndSetAcquire(object, offset, Double::toRawLongBits(newValue)));
    }

    gboolean VarHandle::getAndSetRelease(const Object &object, glong offset, gboolean newValue) {
        gbyte value = newValue ? 1 : 0;
        return getAndSetRelease(object, offset, value);
    }

    gbyte VarHandle::getAndSetRelease(const Object &object, glong offset, gbyte newValue) {
        loadAndStore(gbyte, 0, Byte, , Release);
    }

    gshort VarHandle::getAndSetRelease(const Object &object, glong offset, gshort newValue) {
        loadAndStore(gshort, 0, Short, , Release);
    }

    gchar VarHandle::getAndSetRelease(const Object &object, glong offset, gchar newValue) {
        loadAndStore(gchar, 0, Char, , Release);
    }

    gint VarHandle::getAndSetRelease(const Object &object, glong offset, gint newValue) {
        loadAndStore(gint, 0, Int, , Release);
    }

    glong VarHandle::getAndSetRelease(const Object &object, glong offset, glong newValue) {
        loadAndStore(glong, 0L, Long, , Release);
    }

    gfloat VarHandle::getAndSetRelease(const Object &object, glong offset, gfloat newValue) {
        return Float::fromIntBits(getAndSetRelease(object, offset, Float::toRawIntBits(newValue)));
    }

    gdouble VarHandle::getAndSetRelease(const Object &object, glong offset, gdouble newValue) {
        return Double::fromLongBits(getAndSetRelease(object, offset, Double::toRawLongBits(newValue)));
    }

    gbyte VarHandle::getAndAdd(const Object &object, glong offset, gbyte value) {
        return Intrinsic::loadAndAddByte(StaticCache::resolveOffset(object, offset), value, Intrinsic::SEQUENTIAL);
    }

    gshort VarHandle::getAndAdd(const Object &object, glong offset, gshort value) {
        return Intrinsic::loadAndAddShort(StaticCache::resolveOffset(object, offset), value, Intrinsic::SEQUENTIAL);
    }

    gchar VarHandle::getAndAdd(const Object &object, glong offset, gchar value) {
        return Intrinsic::loadAndAddShort(StaticCache::resolveOffset(object, offset), (gshort) value,
                                          Intrinsic::SEQUENTIAL);
    }

    gint VarHandle::getAndAdd(const Object &object, glong offset, gint value) {
        return Intrinsic::loadAndAddInt(StaticCache::resolveOffset(object, offset), value, Intrinsic::SEQUENTIAL);
    }

    glong VarHandle::getAndAdd(const Object &object, glong offset, glong value) {
        return Intrinsic::loadAndAddLong(StaticCache::resolveOffset(object, offset), value, Intrinsic::SEQUENTIAL);
    }

    gfloat VarHandle::getAndAdd(const Object &object, glong offset, gfloat value) {
        gint bits = 0;
        gfloat result = 0.0f;
        do {
            // Load and CAS with the raw bits to avoid issues with NaNs and
            // possible bit conversion from signaling NaNs to quiet NaNs that
            // may result in the loop not terminating.
            bits = getIntVolatile(object, offset);
            result = Float::fromIntBits(bits);
        }
        while (!weakCompareAndSet(object, offset, bits, Float::toRawIntBits(result + value)));
        return result;
    }

    gdouble VarHandle::getAndAdd(const Object &object, glong offset, gdouble value) {
        glong bits = 0;
        gdouble result = 0.0;
        do {
            // Load and CAS with the raw bits to avoid issues with NaNs and
            // possible bit conversion from signaling NaNs to quiet NaNs that
            // may result in the loop not terminating.
            bits = getLongVolatile(object, offset);
            result = Double::fromLongBits(bits);
        }
        while (!weakCompareAndSet(object, offset, bits, Double::toRawLongBits(result + value)));
        return result;
    }

    gbyte VarHandle::getAndAddAcquire(const Object &object, glong offset, gbyte value) {
        return Intrinsic::loadAndAddByte(StaticCache::resolveOffset(object, offset), value, Intrinsic::ACQUIRE);
    }

    gshort VarHandle::getAndAddAcquire(const Object &object, glong offset, gshort value) {
        return Intrinsic::loadAndAddShort(StaticCache::resolveOffset(object, offset), value, Intrinsic::ACQUIRE);
    }

    gchar VarHandle::getAndAddAcquire(const Object &object, glong offset, gchar value) {
        return Intrinsic::loadAndAddShort(StaticCache::resolveOffset(object, offset), (gshort) value,
                                          Intrinsic::ACQUIRE);
    }

    gint VarHandle::getAndAddAcquire(const Object &object, glong offset, gint value) {
        return Intrinsic::loadAndAddInt(StaticCache::resolveOffset(object, offset), value, Intrinsic::ACQUIRE);
    }

    glong VarHandle::getAndAddAcquire(const Object &object, glong offset, glong value) {
        return Intrinsic::loadAndAddLong(StaticCache::resolveOffset(object, offset), value, Intrinsic::ACQUIRE);
    }

    gfloat VarHandle::getAndAddAcquire(const Object &object, glong offset, gfloat value) {
        gint bits = 0;
        gfloat result = 0.0f;
        do {
            // Load and CAS with the raw bits to avoid issues with NaNs and
            // possible bit conversion from signaling NaNs to quiet NaNs that
            // may result in the loop not terminating.
            bits = getIntAcquire(object, offset);
            result = Float::fromIntBits(bits);
        }
        while (!weakCompareAndSet(object, offset, bits, Float::toRawIntBits(result + value)));
        return result;
    }

    gdouble VarHandle::getAndAddAcquire(const Object &object, glong offset, gdouble value) {
        glong bits = 0;
        gdouble result = 0.0;
        do {
            // Load and CAS with the raw bits to avoid issues with NaNs and
            // possible bit conversion from signaling NaNs to quiet NaNs that
            // may result in the loop not terminating.
            bits = getLongAcquire(object, offset);
            result = Double::fromLongBits(bits);
        }
        while (!weakCompareAndSet(object, offset, bits, Double::toRawLongBits(result + value)));
        return result;
    }

    gbyte VarHandle::getAndAddRelease(const Object &object, glong offset, gbyte value) {
        return Intrinsic::loadAndAddByte(StaticCache::resolveOffset(object, offset), value, Intrinsic::RELEASE);
    }

    gshort VarHandle::getAndAddRelease(const Object &object, glong offset, gshort value) {
        return Intrinsic::loadAndAddShort(StaticCache::resolveOffset(object, offset), value, Intrinsic::RELEASE);
    }

    gchar VarHandle::getAndAddRelease(const Object &object, glong offset, gchar value) {
        return Intrinsic::loadAndAddShort(StaticCache::resolveOffset(object, offset), (gshort) value,
                                          Intrinsic::RELEASE);
    }

    gint VarHandle::getAndAddRelease(const Object &object, glong offset, gint value) {
        return Intrinsic::loadAndAddInt(StaticCache::resolveOffset(object, offset), value, Intrinsic::RELEASE);
    }

    glong VarHandle::getAndAddRelease(const Object &object, glong offset, glong value) {
        return Intrinsic::loadAndAddLong(StaticCache::resolveOffset(object, offset), value, Intrinsic::RELEASE);
    }

    gfloat VarHandle::getAndAddRelease(const Object &object, glong offset, gfloat value) {
        gint bits = 0;
        gfloat result = 0.0f;
        do {
            // Load and CAS with the raw bits to avoid issues with NaNs and
            // possible bit conversion from signaling NaNs to quiet NaNs that
            // may result in the loop not terminating.
            bits = getInt(object, offset);
            result = Float::fromIntBits(bits);
        }
        while (!weakCompareAndSetRelease(object, offset, bits, Float::toRawIntBits(result + value)));
        return result;
    }

    gdouble VarHandle::getAndAddRelease(const Object &object, glong offset, gdouble value) {
        glong bits = 0;
        gdouble result = 0.0;
        do {
            // Load and CAS with the raw bits to avoid issues with NaNs and
            // possible bit conversion from signaling NaNs to quiet NaNs that
            // may result in the loop not terminating.
            bits = getLong(object, offset);
            result = Double::fromLongBits(bits);
        }
        while (!weakCompareAndSetRelease(object, offset, bits, Double::toRawLongBits(result + value)));
        return result;
    }

    gboolean VarHandle::getAndBitwiseOr(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseOr(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseOr(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseOrByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::SEQUENTIAL);
    }

    gshort VarHandle::getAndBitwiseOr(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseOrShort(StaticCache::resolveOffset(object, offset), mask,
                                                Intrinsic::SEQUENTIAL);
    }

    gchar VarHandle::getAndBitwiseOr(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseOrShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                Intrinsic::SEQUENTIAL);
    }

    gint VarHandle::getAndBitwiseOr(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseOrInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::SEQUENTIAL);
    }

    glong VarHandle::getAndBitwiseOr(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseOrLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::getAndBitwiseOrAcquire(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseOrAcquire(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseOrAcquire(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseOrByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gshort VarHandle::getAndBitwiseOrAcquire(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseOrShort(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gchar VarHandle::getAndBitwiseOrAcquire(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseOrShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                Intrinsic::ACQUIRE);
    }

    gint VarHandle::getAndBitwiseOrAcquire(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseOrInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    glong VarHandle::getAndBitwiseOrAcquire(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseOrLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::getAndBitwiseOrRelease(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseOrRelease(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseOrRelease(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseOrByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gshort VarHandle::getAndBitwiseOrRelease(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseOrShort(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gchar VarHandle::getAndBitwiseOrRelease(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseOrShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                Intrinsic::RELEASE);
    }

    gint VarHandle::getAndBitwiseOrRelease(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseOrInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    glong VarHandle::getAndBitwiseOrRelease(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseOrLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gboolean VarHandle::getAndBitwiseAnd(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseAnd(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseAnd(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseAndByte(StaticCache::resolveOffset(object, offset), mask,
                                                Intrinsic::SEQUENTIAL);
    }

    gshort VarHandle::getAndBitwiseAnd(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseAndShort(StaticCache::resolveOffset(object, offset), mask,
                                                 Intrinsic::SEQUENTIAL);
    }

    gchar VarHandle::getAndBitwiseAnd(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseAndShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                 Intrinsic::SEQUENTIAL);
    }

    gint VarHandle::getAndBitwiseAnd(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseAndInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::SEQUENTIAL);
    }

    glong VarHandle::getAndBitwiseAnd(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseAndLong(StaticCache::resolveOffset(object, offset), mask,
                                                Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::getAndBitwiseAndAcquire(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseAndAcquire(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseAndAcquire(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseAndByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gshort VarHandle::getAndBitwiseAndAcquire(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseAndShort(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gchar VarHandle::getAndBitwiseAndAcquire(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseAndShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                 Intrinsic::ACQUIRE);
    }

    gint VarHandle::getAndBitwiseAndAcquire(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseAndInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    glong VarHandle::getAndBitwiseAndAcquire(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseAndLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::getAndBitwiseAndRelease(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseAndRelease(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseAndRelease(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseAndByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gshort VarHandle::getAndBitwiseAndRelease(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseAndShort(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gchar VarHandle::getAndBitwiseAndRelease(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseAndShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                 Intrinsic::RELEASE);
    }

    gint VarHandle::getAndBitwiseAndRelease(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseAndInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    glong VarHandle::getAndBitwiseAndRelease(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseAndLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gboolean VarHandle::getAndBitwiseXor(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseXor(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseXor(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseXorByte(StaticCache::resolveOffset(object, offset), mask,
                                                Intrinsic::SEQUENTIAL);
    }

    gshort VarHandle::getAndBitwiseXor(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseXorShort(StaticCache::resolveOffset(object, offset), mask,
                                                 Intrinsic::SEQUENTIAL);
    }

    gchar VarHandle::getAndBitwiseXor(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseXorShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                 Intrinsic::SEQUENTIAL);
    }

    gint VarHandle::getAndBitwiseXor(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseXorInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::SEQUENTIAL);
    }

    glong VarHandle::getAndBitwiseXor(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseXorLong(StaticCache::resolveOffset(object, offset), mask,
                                                Intrinsic::SEQUENTIAL);
    }

    gboolean VarHandle::getAndBitwiseXorAcquire(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseXorAcquire(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseXorAcquire(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseXorByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gshort VarHandle::getAndBitwiseXorAcquire(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseXorShort(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gchar VarHandle::getAndBitwiseXorAcquire(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseXorShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                 Intrinsic::ACQUIRE);
    }

    gint VarHandle::getAndBitwiseXorAcquire(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseXorInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    glong VarHandle::getAndBitwiseXorAcquire(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseXorLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::ACQUIRE);
    }

    gboolean VarHandle::getAndBitwiseXorRelease(const Object &object, glong offset, gboolean mask) {
        gbyte value = mask ? 1 : 0;
        return getAndBitwiseXorRelease(object, offset, value);
    }

    gbyte VarHandle::getAndBitwiseXorRelease(const Object &object, glong offset, gbyte mask) {
        return Intrinsic::loadAndBitwiseXorByte(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gshort VarHandle::getAndBitwiseXorRelease(const Object &object, glong offset, gshort mask) {
        return Intrinsic::loadAndBitwiseXorShort(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    gchar VarHandle::getAndBitwiseXorRelease(const Object &object, glong offset, gchar mask) {
        return Intrinsic::loadAndBitwiseXorShort(StaticCache::resolveOffset(object, offset), (gshort) mask,
                                                 Intrinsic::RELEASE);
    }

    gint VarHandle::getAndBitwiseXorRelease(const Object &object, glong offset, gint mask) {
        return Intrinsic::loadAndBitwiseXorInt(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    glong VarHandle::getAndBitwiseXorRelease(const Object &object, glong offset, glong mask) {
        return Intrinsic::loadAndBitwiseXorLong(StaticCache::resolveOffset(object, offset), mask, Intrinsic::RELEASE);
    }

    void VarHandle::fullFence() {
        Intrinsic::threadFence(Intrinsic::SEQUENTIAL);
    }

    void VarHandle::acquireFence() {
        Intrinsic::threadFence(Intrinsic::ACQUIRE);
    }

    void VarHandle::releaseFence() {
        Intrinsic::threadFence(Intrinsic::RELEASE);
    }

    void VarHandle::loadLoadFence() {
        acquireFence();
    }

    void VarHandle::storeStoreFence() {
        releaseFence();
    }

    gboolean VarHandle::isBigEndian() {
        return BE;
    }

    gboolean VarHandle::unalignedAccess() {
        return false;
    }

    gint VarHandle::addressSize() {
        return CORE_PROCESSOR_WORDSIZE;
    }

    gint VarHandle::pageSize() {
        return 1024;
    }

    gshort VarHandle::getShortUnaligned(const Object &object, glong offset, gboolean bigEndian) {
        if ((offset & 1) == 0) return convertEndian(bigEndian, getShort(object, offset));
        return convertEndian(bigEndian, makeShort(getByte(object, offset),
                                                  getByte(object, offset + 1)));
    }

    gchar VarHandle::getCharUnaligned(const Object &object, glong offset, gboolean bigEndian) {
        if ((offset & 1) == 0) return convertEndian(bigEndian, getChar(object, offset));
        return convertEndian(bigEndian, makeChar(getByte(object, offset),
                                                 getByte(object, offset + 1)));
    }

    gint VarHandle::getIntUnaligned(const Object &object, glong offset, gboolean bigEndian) {
        if ((offset & 3) == 0) return convertEndian(bigEndian, getInt(object, offset));
        if ((offset & 1) == 0)
            return convertEndian(
                bigEndian, makeInt(
                    getShort(object, offset),
                    getShort(object, offset + 2)));
        return convertEndian(bigEndian, makeInt(
                                 getByte(object, offset),
                                 getByte(object, offset + 1),
                                 getByte(object, offset + 2),
                                 getByte(object, offset + 3)));
    }

    glong VarHandle::getLongUnaligned(const Object &object, glong offset, gboolean bigEndian) {
        if ((offset & 7) == 0) return convertEndian(bigEndian, getLong(object, offset));
        if ((offset & 3) == 0)
            return convertEndian(bigEndian, makeLong(
                                     getInt(object, offset),
                                     getInt(object, offset + 1)));
        if ((offset & 1) == 0)
            return convertEndian(bigEndian, makeLong(
                                     getShort(object, offset),
                                     getShort(object, offset + 2),
                                     getShort(object, offset + 3),
                                     getShort(object, offset + 4)));
        return convertEndian(bigEndian, makeLong(
                                 getByte(object, offset),
                                 getByte(object, offset + 1),
                                 getByte(object, offset + 2),
                                 getByte(object, offset + 3),
                                 getByte(object, offset + 4),
                                 getByte(object, offset + 5),
                                 getByte(object, offset + 6),
                                 getByte(object, offset + 7)));
    }

    void VarHandle::setUnaligned(const Object &object, glong offset, gshort newValue, gboolean bigEndian) {
        gshort value = convertEndian(bigEndian, newValue);
        if ((offset & 1) == 0) set(object, offset, value);
        else
            writeParts(object, offset,
                       (gbyte) (value >> 0),
                       (gbyte) (value >> 8));
    }

    void VarHandle::setUnaligned(const Object &object, glong offset, gchar newValue, gboolean bigEndian) {
        gchar value = convertEndian(bigEndian, newValue);
        if ((offset & 1) == 0) set(object, offset, value);
        else
            writeParts(object, offset,
                       (gbyte) (value >> 0),
                       (gbyte) (value >> 8));
    }

    void VarHandle::setUnaligned(const Object &object, glong offset, gint newValue, gboolean bigEndian) {
        gint value = convertEndian(bigEndian, newValue);
        if ((offset & 3) == 0) set(object, offset, value);
        if ((offset & 1) == 0)
            writeParts(object, offset,
                       (gshort) (value >> 0),
                       (gshort) (value >> 16));
        else
            writeParts(object, offset,
                       (gbyte) (value >> 0),
                       (gbyte) (value >> 8),
                       (gbyte) (value >> 16),
                       (gbyte) (value >> 24));
    }

    void VarHandle::setUnaligned(const Object &object, glong offset, glong newValue, gboolean bigEndian) {
        glong value = convertEndian(bigEndian, newValue);
        if ((offset & 7) == 0) set(object, offset, value);
        if ((offset & 3) == 0)
            writeParts(object, offset,
                       (gint) (value >> 0),
                       (gint) (value >> 32));
        if ((offset & 1) == 0)
            writeParts(object, offset,
                       (gshort) (value >> 0),
                       (gshort) (value >> 16),
                       (gshort) (value >> 32),
                       (gshort) (value >> 48));
        else
            writeParts(object, offset,
                       (gbyte) (value >> 0),
                       (gbyte) (value >> 8),
                       (gbyte) (value >> 16),
                       (gbyte) (value >> 24),
                       (gbyte) (value >> 32),
                       (gbyte) (value >> 40),
                       (gbyte) (value >> 48),
                       (gbyte) (value >> 56));
    }

    glong VarHandle::allocateMemory(glong sizeInBytes) {
        glong bytes = sizeInBytes;
        if (bytes > 0L) bytes = (bytes + addressSize() - 1) & ~(addressSize() - 1);
        StaticCache::checkSize(sizeInBytes);
        if (bytes == 0L) return 0L;
        glong heap = Memory::allocate(bytes);
        if (heap == 0L)
            OutOfMemoryError(u"Unable to allocate "_Su + bytes + u" bytes"_Su).throws($ftrace());
        return heap;
    }

    glong VarHandle::reallocateMemory(glong address, glong sizeInBytes) {
        glong bytes = sizeInBytes;
        if (bytes > 0L) bytes = (bytes + addressSize() - 1) & ~(addressSize() - 1);
        StaticCache::checkObject(address);
        StaticCache::checkSize(sizeInBytes);
        if (bytes == 0L) {
            deallocateMemory(address);
            return 0L;
        }
        glong heap = address == 0L ? Memory::allocate(bytes) : Memory::reallocate(address, bytes);
        if (heap == 0L)
            OutOfMemoryError(u"Unable to allocate "_Su + bytes + u" bytes"_Su).throws($ftrace());
        return heap;
    }

    void VarHandle::setMemory(const Object &object, glong offset, glong sizeInBytes, gbyte newValue) {
        glong address = StaticCache::resolveOffset(object, offset);
        StaticCache::checkSize(sizeInBytes);
        if (sizeInBytes > 0L)
            Memory::fill(address, sizeInBytes, newValue);
    }

    void VarHandle::copyMemory(const Object &sourceObject, glong sourceOffset, const Object &destinationObject,
                               glong destinationOffset, glong sizeInBytes) {
        glong source = StaticCache::resolveOffset(sourceObject, sourceOffset);
        glong destination = StaticCache::resolveOffset(destinationObject, destinationOffset);
        StaticCache::checkSize(sizeInBytes);
        if (sizeInBytes > 0L)
            Memory::copy(source, destination, sizeInBytes);
    }

    void VarHandle::copySwapMemory(const Object &sourceObject, glong sourceOffset, const Object &destinationObject,
                                   glong destinationOffset, glong sizeInBytes, glong elementSize) {
        glong source = StaticCache::resolveOffset(sourceObject, sourceOffset);
        glong destination = StaticCache::resolveOffset(destinationObject, destinationOffset);
        StaticCache::checkSize(sizeInBytes);
        StaticCache::checkSize(elementSize);
        if (elementSize != 2 && elementSize != 4 && elementSize != 8)
            IllegalArgumentException($toString(Invalid data size for swapping)).throws($ftrace());
        if (sizeInBytes % elementSize != 0)
            IllegalArgumentException($toString(Invalid number of bytes)).throws($ftrace());
        if (sizeInBytes > 0L)
            Memory::copySwap(source, destination, sizeInBytes, elementSize);
    }

    void VarHandle::deallocateMemory(glong address) {
        StaticCache::checkObject(address);
        if (address != 0L)
            Memory::deallocate(address);
    }

    gshort VarHandle::makeShort(gbyte b0, gbyte b1) {
        return (gshort) ((toUnsignedInt(b0) << pickDistance(8, 0)) |
                         (toUnsignedInt(b1) << pickDistance(8, 8)));
    }

    gchar VarHandle::makeChar(gbyte b0, gbyte b1) {
        return (gchar) ((toUnsignedInt(b0) << pickDistance(8, 0)) |
                        (toUnsignedInt(b1) << pickDistance(8, 8)));
    }

    gint VarHandle::makeInt(gbyte b0, gbyte b1, gbyte b2, gbyte b3) {
        return ((toUnsignedInt(b0) << pickDistance(24, 0)) |
                (toUnsignedInt(b1) << pickDistance(24, 8)) |
                (toUnsignedInt(b2) << pickDistance(24, 16)) |
                (toUnsignedInt(b3) << pickDistance(24, 24)));
    }

    glong VarHandle::makeLong(gbyte b0, gbyte b1, gbyte b2, gbyte b3, gbyte b4, gbyte b5, gbyte b6, gbyte b7) {
        return ((toUnsignedLong(b0) << pickDistance(56, 0)) |
                (toUnsignedLong(b1) << pickDistance(56, 8)) |
                (toUnsignedLong(b2) << pickDistance(56, 16)) |
                (toUnsignedLong(b3) << pickDistance(56, 24)) |
                (toUnsignedLong(b4) << pickDistance(56, 32)) |
                (toUnsignedLong(b5) << pickDistance(56, 40)) |
                (toUnsignedLong(b6) << pickDistance(56, 48)) |
                (toUnsignedLong(b7) << pickDistance(56, 56)));
    }

    gint VarHandle::makeInt(gshort s0, gshort s1) {
        return (toUnsignedInt(s0) << pickDistance(16, 0)) |
               (toUnsignedInt(s1) << pickDistance(16, 16));
    }

    glong VarHandle::makeLong(gshort s0, gshort s1, gshort s2, gshort s3) {
        return ((toUnsignedLong(s0) << pickDistance(48, 0)) |
                (toUnsignedLong(s1) << pickDistance(48, 16)) |
                (toUnsignedLong(s2) << pickDistance(48, 32)) |
                (toUnsignedLong(s3) << pickDistance(48, 48)));
    }

    glong VarHandle::makeLong(gint i0, gint i1) {
        return (toUnsignedLong(i0) << pickDistance(32, 0)) |
               (toUnsignedLong(i1) << pickDistance(32, 32));
    }

    gbyte VarHandle::pick(gbyte be, gbyte le) {
        return BE ? be : le;
    }

    gshort VarHandle::pick(gshort be, gshort le) {
        return BE ? be : le;
    }

    gint VarHandle::pick(gint be, gint le) {
        return BE ? be : le;
    }

    gint VarHandle::pickDistance(gint top, gint pos) {
        return BE ? top - pos : pos;
    }

    void VarHandle::writeParts(const Object &object, glong offset, gbyte b0, gbyte b1) {
        set(object, offset + 0, pick(b0, b1));
        set(object, offset + 1, pick(b1, b0));
    }

    void VarHandle::writeParts(const Object &object, glong offset, gbyte b0, gbyte b1, gbyte b2, gbyte b3) {
        set(object, offset + 0, pick(b0, b3));
        set(object, offset + 1, pick(b1, b2));
        set(object, offset + 2, pick(b2, b1));
        set(object, offset + 3, pick(b3, b0));
    }

    void VarHandle::writeParts(const Object &object, glong offset, gbyte b0, gbyte b1, gbyte b2, gbyte b3, gbyte b4,
                               gbyte b5, gbyte b6, gbyte b7) {
        set(object, offset + 0, pick(b0, b7));
        set(object, offset + 1, pick(b1, b6));
        set(object, offset + 2, pick(b2, b5));
        set(object, offset + 3, pick(b3, b4));
        set(object, offset + 4, pick(b4, b3));
        set(object, offset + 5, pick(b5, b2));
        set(object, offset + 6, pick(b6, b1));
        set(object, offset + 7, pick(b7, b0));
    }

    void VarHandle::writeParts(const Object &object, glong offset, gshort s0, gshort s1, gshort s2, gshort s3) {
        set(object, offset + 0, pick(s0, s3));
        set(object, offset + 1, pick(s1, s2));
        set(object, offset + 2, pick(s2, s1));
        set(object, offset + 3, pick(s3, s0));
    }

    void VarHandle::writeParts(const Object &object, glong offset, gshort s0, gshort s1) {
        set(object, offset + 0, pick(s0, s1));
        set(object, offset + 1, pick(s1, s0));
    }

    void VarHandle::writeParts(const Object &object, glong offset, gint i0, gint i1) {
        set(object, offset + 0, pick(i0, i1));
        set(object, offset + 4, pick(i1, i0));
    }

    gint VarHandle::toUnsignedInt(gbyte b) {
        return b & 0xff;
    }

    gint VarHandle::toUnsignedInt(gshort s) {
        return s & 0xffff;
    }

    glong VarHandle::toUnsignedLong(gbyte b) {
        return b & 0xffL;
    }

    glong VarHandle::toUnsignedLong(gshort s) {
        return s & 0xffffL;
    }

    glong VarHandle::toUnsignedLong(gint i) {
        return i & 0xffffffffL;
    }

    gshort VarHandle::convertEndian(gboolean bigEndian, gshort s) {
        return bigEndian == BE ? s : Short::reverseBytes(s);
    }

    gchar VarHandle::convertEndian(gboolean bigEndian, gchar c) {
        return bigEndian == BE ? c : Character::reverseBytes(c);
    }

    gint VarHandle::convertEndian(gboolean bigEndian, gint i) {
        return bigEndian == BE ? i : Integer::reverseBytes(i);
    }

    glong VarHandle::convertEndian(gboolean bigEndian, glong l) {
        return bigEndian == BE ? l : Long::reverseBytes(l);
    }

    Object &VarHandle::ObjectStore::loadObject(const Object &object) {
        glong metadata = Cache::getMetadata(object);
        if (object == null || metadata == 0L) return null;
        if (Class<Throwable>::hasInstance(object)) {
            Cache &exclusiveCache = $cast(Cache&, StaticCache::getExclusiveCache());
            if (exclusiveCache.exists(metadata))
                return Cache::getObject(metadata);
        }
        // if (Class<Thread>::hasInstance(object)) {
        //     Cache &sharedCache = $cast(Cache&, StaticCache::getSharedCache());
        //     if (sharedCache.exists(metadata))
        //         return Cache::getObject(metadata);
        // }
        else {
            Cache &defaultCache = $cast(Cache&, StaticCache::getDefaultCache());
            if (defaultCache.exists(metadata))
                return Cache::getObject(metadata);
        }
        return null;
    }

    Object &VarHandle::ObjectStore::storeObject(Object &object) {
        glong metadata = Cache::getMetadata(object);
        if (object == null || metadata == 0L) return null;
        if (Class<Throwable>::hasInstance(object)) {
            Cache &exclusiveCache = $cast(Cache&, StaticCache::getExclusiveCache());
            exclusiveCache.store(Cache::EXCLUSIVE, metadata);
        }
        // else if (Class<Thread>::hasInstance(object)) {
        //     Cache &sharedCache = $cast(Cache&, StaticCache::getExclusiveCache());
        //     sharedCache.store(Cache::SHARED, metadata);
        // }
        else {
            Cache &defaultCache = $cast(Cache&, StaticCache::getDefaultCache());
            defaultCache.store(Cache::DEFAULT, metadata);
        }
        return object;
    }

    gboolean VarHandle::ObjectStore::compareObject(const Object &a, const Object &b) {
        return &a == &b;
    }

    Object &VarHandle::StaticCache::getDefaultCache() {
        static Cache defaultCache;
        defaultCache.store(Cache::PRIVATE, Cache::getMetadata(defaultCache));
        return defaultCache;
    }

    Object &VarHandle::StaticCache::getSharedCache() {
        static Cache sharedCache;
        sharedCache.store(Cache::PRIVATE, Cache::getMetadata(sharedCache));
        return sharedCache;
    }

    Object &VarHandle::StaticCache::getExclusiveCache() {
        static Cache exclusiveCache;
        exclusiveCache.store(Cache::PRIVATE, Cache::getMetadata(exclusiveCache));
        return exclusiveCache;
    }

    Object &VarHandle::StaticCache::getEnumCache() {
        return null;
    }

    Object &VarHandle::StaticCache::getCache(glong metadata) {
        if (metadata == 0L) return null;
        return *(Address) metadata;
    }

    void VarHandle::StaticCache::checkOffset(glong offset) {
        if (offset < 0)
            IllegalArgumentException($toString(Negative address offset)).throws($ftrace());
        if ((addressSize() == 4) && (offset >> 32) != 0)
            IllegalArgumentException($toString(Invalid address offset)).throws($ftrace());
    }

    void VarHandle::StaticCache::checkSize(glong sizeInBytes) {
        if (sizeInBytes < 0)
            IllegalArgumentException($toString(Negative size)).throws($ftrace());
        if ((addressSize() == 4) && (sizeInBytes >> 32) != 0)
            IllegalArgumentException($toString(Size value is too large)).throws($ftrace());
    }

    void VarHandle::StaticCache::checkObject(glong metadata) {
        if (addressSize() == 4 && (((metadata >> 32) + 1) & ~1) != 0)
            // Accept both zero and sign extended pointers.
            // A valid pointer will, after the +1 below, either have produced the value 0x0 or 0x1.
            // Masking off the low bit allows for testing against 0.
            IllegalArgumentException($toString(Unsupported memory address)).throws($ftrace());
    }

    CORE_WARNING_PUSH
    CORE_WARNING_DISABLE_INVALID_OFFSETOF

    glong VarHandle::StaticCache::resolveOffset(const Object &object, glong offset) {
        static glong metadata = Cache::getMetadata(object);
        if (metadata == 0L) return 0L;
        checkObject(metadata);
        checkOffset(metadata);
        if (Class<AbstractArray>::hasInstance(object)) {
            glong baseOffset = CORE_FIELD_OFFSET(ByteArray, values);
            metadata = (glong) *(Address2D) (metadata + baseOffset);
            offset = offset - baseOffset;
        }
        else if (Class<AbstractObjectArray>::hasInstance(object)) {
            glong baseOffset = CORE_FIELD_OFFSET(AbstractObjectArray, values);
            metadata = (glong) *(Address2D) (metadata + baseOffset);
            offset = offset - baseOffset;
        }
        return metadata + offset;
    }

    CORE_WARNING_POP

    glong VarHandle::StaticCache::newHeap(glong heapSize) {
        checkSize(heapSize);
        if (heapSize == 0) return 0L;
        glong heap = Memory::allocate(heapSize);
        if (heap == 0L)
            OutOfMemoryError(u"Unable to allocate "_Su + heapSize + u" bytes"_S).throws($ftrace());
        return heap;
    }
} // lang
// core
