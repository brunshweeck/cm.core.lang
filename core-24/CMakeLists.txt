# Library Properties
include("../Settings.cmake")


# Commom Properties
CMAKE_MINIMUM_REQUIRED_VERSION(VERSION ${LIBRARY_CMAKE_VERSION})

project(
    NAME ${LIBRARY_NAME}
    VERSION ${LIBRARY_VERSION}
    DESCRIPTION ${LIBRARY_DESCRIPTION}
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD ${LIBRARY_CXX_VERSION})
set(CMAKE_CXX_STANDARD_REQUIRED ${LIBRARY_CXX_REQUIRED})
set(CMAKE_EXPORT_COMPILE_COMMANDS ${LIBRARY_EXPORT_COMMANDS})

if (LIBRARY_PLATFORM STREQUAL "")
    if(WIN32)
        set(LIBRARY_PLATFORM "Win32")
    else()
        set(LIBRARY_PLATFORM "Posix")
    endif(WIN32)
endif()

include(CMakeDependentOption)
include(GNUInstallDirs)



if (LIBRARY_BUILD_TEST)
    enable_testing()
    add_subdirectory("Test")
endif()

if (LIBRARY_BUILD_LIB)
    add_subdirectory("Lib")
endif()

if (LIBRARY_BUILD_SRC)
    add_subdirectory("Src")
endif()

# Configurations and macro, function definitions
include("../Config.cmake")
