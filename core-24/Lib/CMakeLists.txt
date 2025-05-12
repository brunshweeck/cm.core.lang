
include("Settings.cmake")

if (WIN32)
    set(PLATFORM_DIR "../win32")
else ()
    set(PLATFORM_DIR "../unix")
endif ()

file(GLOB LIBRARY_FILES
        "core/lang/spi/*.cpp"
        "core/lang/spi/*.h"
        "${PLATFORM_DIR}/core/lang/*.cpp"
        "${PLATFORM_DIR}/core/lang/*.h"
        "core/lang/*.cpp"
        "core/lang/*.h"
)

CreateSharedLibrary("${LIBRARY_NAME}-${LIBRARY_FULL_VERSION}" " " ${LIBRARY_FILES})
INCLUDE_DIRECTORIES(".")
INCLUDE_DIRECTORIES("${PLATFORM_DIR}")
