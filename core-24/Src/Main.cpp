#include <cstdio>
#include <cstdlib>
#include <core/lang/AssertionError.h>
#include <core/lang/BooleanArray.h>
#include <core/lang/ByteArray.h>
#include <core/lang/CharArray.h>
#include <core/lang/DoubleArray.h>
#include <core/lang/FloatArray.h>
#include <core/lang/IntArray.h>
#include <core/lang/LongArray.h>
#include <core/lang/ShortArray.h>

using namespace core::lang::spi;
using namespace core::lang;
using namespace core;

int main() {
    {
        FloatArray array1 = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        auto array2 = FloatArray::of(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        auto array3 = FloatArray::ofRange(0.0f, 10.0f);
        CORE_FAST gfloat values[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        auto array4 = FloatArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        DoubleArray array1 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
        auto array2 = DoubleArray::of(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
        auto array3 = DoubleArray::ofRange(0.0, 10.0);
        CORE_FAST gdouble values[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
        auto array4 = DoubleArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        ByteArray array1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array2 = ByteArray::of(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto array3 = ByteArray::ofRange(0, 10);
        CORE_FAST gbyte values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array4 = ByteArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        ShortArray array1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array2 = ShortArray::of(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto array3 = ShortArray::ofRange(0, 10);
        CORE_FAST gshort values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array4 = ShortArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        CharArray array1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array2 = CharArray::of(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto array3 = CharArray::ofRange(0, 10);
        CORE_FAST gchar values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array4 = CharArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        IntArray array1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array2 = IntArray::of(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto array3 = IntArray::ofRange(0, 10);
        CORE_FAST gint values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto array4 = IntArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        LongArray array1 = {0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L};
        auto array2 = LongArray::of(0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L);
        auto array3 = LongArray::ofRange(0L, 10L);
        CORE_FAST glong values[] = {0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L};
        auto array4 = LongArray::copyOf(values);
        if (array1 != array2 || array1 != array3 || array1 != array4)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    {
        BooleanArray array1 = {true, false};
        auto array2 = BooleanArray::of(true, false);
        CORE_FAST gboolean values[] = {true, false};
        auto array3 = BooleanArray::copyOf(values);
        if (array1 != array2 || array1 != array3)
            AssertionError($toString(Compiler error)).throws($ftrace());
    }
    return 0;
}
