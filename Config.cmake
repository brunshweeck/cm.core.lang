

function(FixDefaultCompilerSettings)

    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC|Clang")
        # For MSVC and Clang, CMake sets certain flags to defaults we want to
        # override.
        # This replacement code is taken from sample in the CMake Wiki at
        # https://gitlab.kitware.com/cmake/community/wikis/FAQ#dynamic-replace.
        foreach (FLAG
                CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if (NOT BUILD_SHARED)
                string(REPLACE "/MD" "-MT" ${FLAG} "${${FLAG}}")

                # When using Ninja with Clang, static builds pass -D_DLL on Windows.
                # This is incorrect and should not happen, so we fix that here.
                string(REPLACE "-D_DLL" "" ${FLAG} "${${FLAG}}")
            endif ()

            # We prefer more strict warning checking for building Google Test.
            # Replaces /W3 with /W4 in defaults.
            string(REPLACE "/W3" "/W4" ${FLAG} "${${FLAG}}")

            # Prevent D9025 warning for targets that have exception handling
            # turned off (/EHs-c- flag). Where required, exceptions are explicitly
            # re-enabled using the cxx_exception_flags variable.
            string(REPLACE "/EHsc" "" ${FLAG} "${${FLAG}}")
        endforeach ()
    endif ()
endfunction()


# Defines the compiler/linker flags used to build project.
# You can tweak these definitions to suit your need. A
# variable's value is empty before it's explicitly assigned to.

function(ConfigureCompiler)

    FixDefaultCompilerSettings()

    # Flags for language
    if (MSVC)
        set(LIBRARY_CXX_DEFAULT ${LIBRARY_CXX_VERSION})

        # Newlines inside flags variables break CMake's NMake generator.
        set(LIBRARY_CXX_BASE "-GS -W4 -WX -wd4251 -wd4275 -nologo -J")
        set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} -D_UNICODE -DUNICODE -DWIN32 -D_WIN32")
        set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} -DSTRICT -DWIN32_LEAN_AND_MEAN")

        set(LIBRARY_CXX_EXCEPTION "-EHsc -D_HAS_EXCEPTIONS=1")
        set(LIBRARY_CXX_NO_EXCEPTION "-EHs-c- -D_HAS_EXCEPTIONS=0")
        set(LIBRARY_CXX_NO_RTTI "-GR-")
        set(LIBRARY_CXX_STRICT "")

        # Suppress "unreachable code" warning,
        # https://stackoverflow.com/questions/3232669 explains the issue.
        set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} -wd4702")

        # Ensure MSVC treats source files as UTF-8 encoded.
        if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} -utf-8")
        endif ()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
            set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} /fp:precise -Wno-inconsistent-missing-override -Wno-microsoft-exception-spec -Wno-unused-function -Wno-unused-but-set-variable")
        endif ()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
        # set(LIBRARY_CXX_BASE "-Wall -Wshadow -Wconversion -Wundef")
        set(LIBRARY_CXX_BASE "-Wall -Wconversion -Wundef")
        set(LIBRARY_CXX_EXCEPTION "-fexceptions")
        set(LIBRARY_CXX_NO_EXCEPTION "-fno-exceptions")
        set(LIBRARY_CXX_STRICT "-W -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wswitch -Wunused-parameter -Wcast-align -Winline -Wredundant-decls")
        set(LIBRARY_CXX_NO_RTTI "-fno-rtti")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            set(LIBRARY_CXX_STRICT "${LIBRARY_CXX_STRICT} -Wchar-subscripts")
        endif ()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
            set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} -Wno-implicit-float-size-conversion -ffp-model=precise")
        endif ()
    elseif (CMAKE_COMPILER_IS_GNUCXX)
        #        set(LIBRARY_CXX_BASE "-Wall -Wshadow -Wundef")
        set(LIBRARY_CXX_BASE "-Wall -Wundef")
        if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0.0)
            set(LIBRARY_CXX_BASE "${LIBRARY_CXX_BASE} -Wno-error=dangling-else")
        endif ()
        set(LIBRARY_CXX_EXCEPTION "-fexceptions")
        set(LIBRARY_CXX_NO_EXCEPTION "-fno-exceptions")
        # Until version 4.3.2, GCC doesn't define a macro to indicate
        # whether RTTI is enabled. Therefore we define CORE_HAS_RTTI
        # explicitly.
        set(LIBRARY_CXX_NO_RTTI "-fno-rtti -DCORE_HAS_RTTI=0")
        set(LIBRARY_CXX_STRICT "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "SunPro")
        set(LIBRARY_CXX_EXCEPTION "-features=except")
        # Sun Pro doesn't provide macros to indicate whether exceptions and
        # RTTI are enabled, so we define CORE_HAS_* explicitly.
        set(LIBRARY_CXX_NO_EXCEPTION "-features=no%except -DCORE_HAS_EXCEPTIONS=0")
        set(LIBRARY_CXX_NO_RTTI "-features=no%rtti -DCORE_HAS_RTTI=0")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "VisualAge" OR
            CMAKE_CXX_COMPILER_ID STREQUAL "XL")
        # CMake 2.8 changes Visual Age's compiler ID to "XL".
        set(LIBRARY_CXX_EXCEPTION "-qeh")
        set(LIBRARY_CXX_NO_EXCEPTION "-qnoeh")
        # Until version 9.0, Visual Age doesn't define a macro to indicate
        # whether RTTI is enabled. Therefore we define CORE_HAS_RTTI
        # explicitly.
        set(LIBRARY_CXX_NO_RTTI "-qnortti -DCORE_HAS_RTTI=0")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "HP")
        set(LIBRARY_CXX_BASE "-AA -mt")
        set(LIBRARY_CXX_EXCEPTION "-DCORE_HAS_EXCEPTIONS=1")
        set(LIBRARY_CXX_NO_EXCEPTION "+noeh -DCORE_HAS_EXCEPTIONS=0")
        # RTTI can not be disabled in HP aCC compiler.
        set(LIBRARY_CXX_NO_RTTI "")
    endif ()

    # For building Core's own tests and samples.

    set(CXX_EXCEPTION "${LIBRARY_CXX_BASE} ${LIBRARY_CXX_EXCEPTION}")
    set(CXX_NO_EXCEPTION "${CMAKE_CXX_FLAGS} ${LIBRARY_CXX_BASE} ${LIBRARY_CXX_NO_EXCEPTION}")
    set(CXX_DEFAULT "${CXX_EXCEPTION}")
    set(CXX_NO_RTTI "${CXX_DEFAULT} ${LIBRARY_CXX_NO_RTTI}")

    # For building the gtest libraries.
    set(CXX_STRICT "${CXX_DEFAULT} ${LIBRARY_CXX_STRICT}")

endfunction()

# Create new library with given parameters
# CreateLibrary(name, type, flags, ...sources)
function(CreateLibrary libraryName libraryType compileFlags)
    set(libarayPrefixName ${LIBRARY_PROJECT_NAME})
    # type can be either STATIC or SHARED to denote a static or shared library.
    # ARGN refers to additional arguments after 'FLAGS'.
    if ("${libraryPrefixName}" STREQUAL "")
        add_library("${libraryName}" "${libraryType}" ${ARGN})
        add_library("${libraryPrefixName}::${libraryName}" ALIAS ${libraryName})
    else ()
        add_library("${libraryName}" "${libraryType}" ${ARGN})
    endif ()

    get_target_property(PROP1 "${libraryName}" COMPILE_FLAGS)

    set_target_properties("${libraryName}" PROPERTIES COMPILE_FLAGS "${exeFlags}")

    get_target_property(PROP1 "${libraryName}" COMPILE_FLAGS)
    # Set the output directory for build artifacts.
    set_target_properties("${libraryName}"
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    # Make PDBs match library name.
    get_target_property(PDB_DEBUG_POSTFIX ${libraryName} DEBUG_POSTFIX)
    set_target_properties(${libraryName}
            PROPERTIES
            PDB_NAME "${libraryName}"
            PDB_NAME_DEBUG "${libraryName}${PDB_DEBUG_POSTFIX}"
            COMPILE_PDB_NAME "${libraryName}"
            COMPILE_PDB_NAME_DEBUG "${libraryName}${PDB_DEBUG_POSTFIX}")
    if (LIBRARY_TYPE STREQUAL "SHARED")
        set_target_properties(${libraryName} PROPERTIES COMPILE_DEFINITIONS "CORE_CREATE_SHARED_LIBRARY=1")
        target_compile_definitions("${libraryName}" INTERFACE $<INSTALL_INTERFACE:CORE_LINKED_HAS_SHARED_LIBRARY=1>)
        target_compile_features("${libraryName}" PUBLIC "cxx_std_${LIBRARY_CXX_VERSION}")
    endif ()
endfunction()

# Create new executable with given parameters
# CreateExe(name, flags, dependencies, ...sources)
function(CreateExe exeName exeFlags dependencies)

    if (exeFlags STREQUAL "")
        set(exeFlags ${CXX_DEFAULT})
    endif ()

    add_executable("${exeName}" ${ARGN})
    if (MSVC)
        # BigObj required for tests.
        set(FLAGS "${exeFlags} -bigobj")
    endif ()
    if (FLAGS)
        set_target_properties(${exeName}
                PROPERTIES
                COMPILE_FLAGS "${exeFlags}")
    endif ()
    if (BUILD_SHARED)
        set_target_properties(${exeName}
                PROPERTIES
                COMPILE_DEFINITIONS "CORE_LINKED_AS_SHARED_LIBRARY=1")
    endif ()
    # To support mixing linking in static and dynamic libraries, link each
    # library in with an extra call to target_link_libraries.
    foreach (LIBRARY ${LIBRARIES})
        target_link_libraries(${exeName} ${LIBRARY})
    endforeach ()
endfunction()

function(CreateSharedLibrary libraryName libraryFlags)
    CreateLibrary("${libraryName}" SHARED "${libraryFlags}" ${ARGN})
endfunction()

function(CreateStaticLibrary libraryName libraryFlags)
    CreateLibrary(${libraryName} STATIC ${libraryFlags} ${ARGN})
endfunction()

function(CreateTestFor classToTest testDir namespace)
    if (NOT EXISTS ${testDir})
        message(TRACE "Creating of test location")
        make_directory(${testDir})
    endif ()

    if (NOT EXISTS "${testDir}/${classToTest}Test.h")
        write_file("${testDir}/${classToTest}Test.h"
                "
//
// This File has been Created by CMake For Testing of Class ${classToTest}
// Please include this file in your test into api/Main.cpp to execute it
//

#pragma once

#include <core/lang/Object.h>
#include <api/Test.h>
#include <gtest/gtest.h>

using namespace core::lang;

namespace ${namespace} {

    using namespace core::lang;
    using namespace core::util;
    using namespace core::regex;
    using namespace core::text;
    using namespace core::time;
    using namespace core::function;
    using namespace core::concurrent;

    /**
     * The class defined to test ${classToTest} class
     */
    class ${classToTest}Test: public testing::Test, public Object {

        void $before() final {
            // code...
        }

        
        void $after() final {
            // code...
        }

    public:

        void $test() override = 0;
    };


    TEST_F(${classToTest}, test1) {
        // code...
    }


    TEST_F(${classToTest}, test2) {
        // code...
    }
}
")
    endif ()

    write_file(api/Main.cpp "#include \"${testDir}/${classToTest}Test.h\"" APPEND)

endfunction()

function(CreateTest classToTest testDir namespace testFlags dependencies)
    if (NOT EXISTS ${testDir})
        message(WARNING "Creating of test location")
        make_directory(${testDir})
    endif ()

    if (NOT EXISTS "${testDir}/${classToTest}Test.h")
        write_file("${testDir}/${classToTest}Test.h"
                "
//
// This File has been Created by CMake For Testing of Class ${classToTest}
// Please include this file in your test main source file
//

#pragma once

#include <core/lang/Object.h>
#include <gtest/gtest.h>

namespace ${namespace} {

    /**
     * The class defined to test ${classToTest} class
     */
    class ${classToTest}Test: public testing::Test, public core::Object {

        void $before() final;

        void $after();

    public:

        $test()
        void TestBody() override = 0;
    };
}
")
    endif ()

    if (NOT EXISTS "${testDir}/${classToTest}Test.cpp")
        write_file("${testDir}/${classToTest}Test.cpp"
                "
//
// This File has been Created by CMake For Testing of Class ${classToTest}
// Please include this file in your test main source file
//

#pragma once

#include \"${classToTest}Test.h\"

#include <core/lang/Object.h>
#include <api/Test.h>
#include <gtest/gtest.h>


namespace ${namespace} {

    using namespace core::lang;
    using namespace core::util;
    using namespace core::regex;
    using namespace core::text;
    using namespace core::time;
    using namespace core::function;
    using namespace core::concurrent;

    void ${classToTest}Test::$before() {
        // code...
    }

    void ${classToTest}Test::$after() {
        // code...
    }


    TEST_F(${classToTest}, test1) {
        // code...
    }


    TEST_F(${classToTest}, test2) {
        // code...
    }
}
")
    endif ()

    CreateExe(${classToTest}Test ${testFlags})


endfunction()
