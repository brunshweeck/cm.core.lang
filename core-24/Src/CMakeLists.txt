

include("Settings.cmake")

CreateExe("Main" "${SOURCE_CXX_OPTIONS}" " " "Main.cpp")

add_executable("SampleExecutable" "Main.cpp"
        ../Lib/core/lang/Object.cpp
        ../Lib/core/lang/Object.h
        ../Lib/core/lang/Null.cpp
        ../Lib/core/lang/Null.h
        ../Lib/core/lang/Appendable.cpp
        ../Lib/core/lang/Appendable.h
        ../Lib/core/lang/CharSequence.cpp
        ../Lib/core/lang/CharSequence.h
        ../Lib/core/lang/Comparable.cpp
        ../Lib/core/lang/Comparable.h
        ../Lib/core/lang/Iterable.cpp
        ../Lib/core/lang/Iterable.h
        ../Lib/core/lang/Number.cpp
        ../Lib/core/lang/Number.h
        ../Lib/core/lang/String.cpp
        ../Lib/core/lang/String.h
        ../Lib/core/lang/Boolean.cpp
        ../Lib/core/lang/Boolean.h
        ../Lib/core/lang/Byte.cpp
        ../Lib/core/lang/Byte.h
        ../Lib/core/lang/Short.cpp
        ../Lib/core/lang/Short.h
        ../Lib/core/lang/Integer.cpp
        ../Lib/core/lang/Integer.h
        ../Lib/core/lang/Long.cpp
        ../Lib/core/lang/Long.h
        ../Lib/core/lang/Float.cpp
        ../Lib/core/lang/Float.h
        ../Lib/core/lang/Double.cpp
        ../Lib/core/lang/Double.h
        ../Lib/core/lang/TraceInfo.cpp
        ../Lib/core/lang/TraceInfo.h
        ../Lib/core/lang/Throwable.cpp
        ../Lib/core/lang/Throwable.h
        ../Lib/core/lang/Exception.cpp
        ../Lib/core/lang/Exception.h
        ../Lib/core/lang/Error.cpp
        ../Lib/core/lang/Error.h
        ../Lib/core/lang/ArithmeticException.cpp
        ../Lib/core/lang/ArithmeticException.h
        ../Lib/core/lang/AssertionError.cpp
        ../Lib/core/lang/AssertionError.h
        ../Lib/core/lang/ClassCastException.cpp
        ../Lib/core/lang/ClassCastException.h
        ../Lib/core/lang/CloneNotSupportedException.cpp
        ../Lib/core/lang/CloneNotSupportedException.h
        ../Lib/core/lang/IllegalArgumentException.cpp
        ../Lib/core/lang/IllegalArgumentException.h
        ../Lib/core/lang/RuntimeException.cpp
        ../Lib/core/lang/RuntimeException.h
        ../Lib/core/lang/IllegalStateException.cpp
        ../Lib/core/lang/IllegalStateException.h
        ../Lib/core/lang/IndexOutOfBoundsException.cpp
        ../Lib/core/lang/IndexOutOfBoundsException.h
        ../Lib/meta/lang/StringIndexOutOfBoundsException.cpp
        ../Lib/meta/lang/StringIndexOutOfBoundsException.h
        ../Lib/core/lang/NumberFormatException.cpp
        ../Lib/core/lang/NumberFormatException.h
        ../Lib/core/lang/OutOfMemoryError.cpp
        ../Lib/core/lang/OutOfMemoryError.h
        ../Lib/core/lang/SecurityException.cpp
        ../Lib/core/lang/SecurityException.h
        ../Lib/core/lang/UnsupportedOperationException.cpp
        ../Lib/core/lang/UnsupportedOperationException.h
        ../Lib/core/lang/Void.cpp
        ../Lib/core/lang/Void.h
        ../Lib/core/lang/Character.cpp
        ../Lib/core/lang/Character.h
        ../Lib/core/lang/spi/AbstractArray.cpp
        ../Lib/core/lang/spi/AbstractArray.h
        ../Lib/core/lang/spi/AbstractPrimitiveArray.cpp
        ../Lib/core/lang/spi/AbstractPrimitiveArray.h
        ../Lib/core/lang/spi/AbstractObjectArray.cpp
        ../Lib/core/lang/spi/AbstractObjectArray.h
        ../Lib/core/lang/Array.cpp
        ../Lib/core/lang/Array.h
        ../Lib/core/lang/spi/AbstractValueArray.cpp
        ../Lib/core/lang/spi/AbstractValueArray.h
        ../Lib/core/lang/BooleanArray.cpp
        ../Lib/core/lang/BooleanArray.h
        ../Lib/core/lang/FloatArray.cpp
        ../Lib/core/lang/FloatArray.h
        ../Lib/meta/lang/ArrayIndexOutOfBoundsException.cpp
        ../Lib/meta/lang/ArrayIndexOutOfBoundsException.h
        ../Lib/core/lang/ByteArray.cpp
        ../Lib/core/lang/ByteArray.h
        ../Lib/core/lang/DoubleArray.cpp
        ../Lib/core/lang/DoubleArray.h
        ../Lib/core/lang/ShortArray.cpp
        ../Lib/core/lang/ShortArray.h
        ../Lib/core/lang/CharArray.cpp
        ../Lib/core/lang/CharArray.h
        ../Lib/core/lang/IntArray.cpp
        ../Lib/core/lang/IntArray.h
        ../Lib/core/lang/LongArray.cpp
        ../Lib/core/lang/LongArray.h
        ../Lib/meta/lang/Strings.cpp
        ../Lib/meta/lang/Strings.h
        ../Lib/core/lang/Preconditions.cpp
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 1dd40da (refactor(core-lang-19): unix adjustement)
        ../Lib/core/lang/Preconditions.h
        ../Lib/meta/lang/spi/ConcurrentQueue.cpp
        ../Lib/meta/lang/spi/ConcurrentQueue.h
        ../Lib/meta/lang/spi/TraceInfoProvider.cpp
        ../Lib/meta/lang/spi/TraceInfoProvider.h)
<<<<<<< HEAD
=======
        ../Lib/core/lang/Preconditions.h)
>>>>>>> 3aa0f8c (???)
=======
>>>>>>> 1dd40da (refactor(core-lang-19): unix adjustement)

include_directories("../Lib")
