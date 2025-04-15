

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
        ../Lib/core/lang/Number.h)