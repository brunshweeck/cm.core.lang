

include("Settings.cmake")

CreateExe("Main" "${SOURCE_CXX_OPTIONS}" " " "Main.cpp")

add_executable("SampleExecutable" "Main.cpp")