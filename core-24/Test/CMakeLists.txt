

include("Settings.cmake")

set(CMAKE_CXX_STANDARD ${TEST_CXX_VERSION})
set(CXX_STANDARD_REQUIRED ${TEST_CXX_REQUIRED})
set(EXPORT_COMPILE_COMMANDS ${TEST_EXPORT_COMMANDS})

CreateTestFor(Sample demo package)

CreateExe("${TEST_PROJECT_NAME}-${TEST_VERSION}" "${TEST_CXX_OPTIONS}" " " "api/Main.cpp")

include_directories("../Lib")
