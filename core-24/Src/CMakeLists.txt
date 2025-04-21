

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
        ../Lib/core/lang/Double.h)
