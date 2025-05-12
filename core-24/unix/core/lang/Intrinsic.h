//
// Created by brunshweeck on 10/05/25.
//

#ifndef CORE_LANG_INTRINSIC_H
#define CORE_LANG_INTRINSIC_H
#include <core/lang/Object.h>


namespace core::lang
{
    class Intrinsic : public Object
    {
        Intrinsic() = default;

    public:
        ~Intrinsic() override = default;

        enum Mode
        {
            RELAXED, CONSUME, ACQUIRE, RELEASE, ACQUIRE_AND_RELEASE, SEQUENTIAL
        };

        static gbyte loadByte(glong address, Mode mode);

        static gshort loadShort(glong address, Mode mode);

        static gint loadInt(glong address, Mode mode);

        static glong loadLong(glong address, Mode mode);

        static void storeByte(glong address, gbyte value, Mode mode);

        static void storeShort(glong address, gshort value, Mode mode);

        static void storeInt(glong address, gint value, Mode mode);

        static void storeLong(glong address, glong value, Mode mode);

        static gbyte exchangeByte(glong address, gbyte value, Mode mode);

        static gshort exchangeShort(glong address, gshort value, Mode mode);

        static gint exchangeInt(glong address, gint value, Mode mode);

        static glong exchangeLong(glong address, glong value, Mode mode);

        static gboolean compareAndExchangeByte(glong address, gbyte expected, gbyte desired, gboolean weakly,
                                               Mode mode);

        static gboolean compareAndExchangeShort(glong address, gshort expected, gshort desired, gboolean weakly,
                                                Mode mode);

        static gboolean compareAndExchangeInt(glong address, int expected, int desired, gboolean weakly, Mode mode);

        static gboolean compareAndExchangeLong(glong address, long expected, long desired, gboolean weakly, Mode mode);

        static void threadFence(Mode mode);

        static void signalFence(Mode mode);

        static gbyte loadAndAddByte(glong address, gbyte value, Mode mode);

        static gshort loadAndAddShort(glong address, gshort value, Mode mode);

        static gint loadAndAddInt(glong address, gint value, Mode mode);

        static glong loadAndAddLong(glong address, glong value, Mode mode);

        static gbyte loadAndBitwiseAndByte(glong address, gbyte value, Mode mode);

        static gshort loadAndBitwiseAndShort(glong address, gshort value, Mode mode);

        static gint loadAndBitwiseAndInt(glong address, gint value, Mode mode);

        static glong loadAndBitwiseAndLong(glong address, glong value, Mode mode);

        static gbyte loadAndBitwiseOrByte(glong address, gbyte value, Mode mode);

        static gshort loadAndBitwiseOrShort(glong address, gshort value, Mode mode);

        static gint loadAndBitwiseOrInt(glong address, gint value, Mode mode);

        static glong loadAndBitwiseOrLong(glong address, glong value, Mode mode);

        static gbyte loadAndBitwiseXorByte(glong address, gbyte value, Mode mode);

        static gshort loadAndBitwiseXorShort(glong address, gshort value, Mode mode);

        static gint loadAndBitwiseXorInt(glong address, gint value, Mode mode);

        static glong loadAndBitwiseXorLong(glong address, glong value, Mode mode);


    };
} // core::lang

#endif // CORE_LANG_INTRINSIC_H
