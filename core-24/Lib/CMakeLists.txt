
include("Settings.cmake")

file(GLOB LIBRARY_FILES
        "core/lang/Object.cpp"
        "core/lang/Object.h"
        "core/lang/spi/*.h"
)

CreateSharedLibrary("${LIBRARY_NAME}-${LIBRARY_FULL_VERSION}" " " ${LIBRARY_FILES})
