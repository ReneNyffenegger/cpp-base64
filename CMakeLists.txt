cmake_minimum_required(VERSION 3.8)
project(cpp-base64 CXX)

include(CheckCXXCompilerFlag)

option(BASE64_ENABLE_STATIC_LIB "Build static library" ON)
option(BASE64_ENABLE_TESTS "Build test executables and libraries" OFF)
option(BASE64_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# Require C++11 but use C++17 if possible
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 17)

# Collect enabled warnings
set(WARNING_FLAGS
       -Wall
       -Wextra
       -pedantic
       -Wcast-align
       -Wcast-qual
       -Wctor-dtor-privacy
       -Wdisabled-optimization
       -Wformat=2
       -Winit-self
       -Wlogical-op
       -Wmissing-include-dirs
       -Wnoexcept
       -Wold-style-cast
       -Woverloaded-virtual
       -Wredundant-decls
       -Wshadow
       -Wsign-promo
       -Wstrict-null-sentinel
       -Wstrict-overflow=5
       -Wundef
       -Wno-unused
       -Wno-variadic-macros
       -Wno-parentheses
       -fdiagnostics-show-option
   )
if(${BASE64_WARNINGS_AS_ERRORS})
    list(APPEND WARNING_FLAGS -Werror)
endif()

# Main library target
add_library(base64 SHARED
        src/base64.cpp
    )
set(TARGETS base64)
add_library(base64::base64 ALIAS base64)

# Static library target
if(${BASE64_ENABLE_STATIC_LIB})
    add_library(base64_static STATIC
            src/base64.cpp
        )
    set_property(TARGET base64_static PROPERTY POSITION_INDEPENDENT_CODE ON)
    list(APPEND TARGETS base64_static)
    add_library(base64::base64_static ALIAS base64_static)
endif()

if (${BASE64_ENABLE_TESTS})
    enable_testing()

    # CXX11 version of library
    add_library(base64_cxx11 SHARED
            src/base64.cpp
        )
    set_property(TARGET base64_cxx11 PROPERTY CXX_STANDARD 11)

    # CXX11 version of test
    add_executable(base64_test_cxx11
            src/test.cpp
        )
    target_link_libraries(base64_test_cxx11
        PUBLIC
            base64_cxx11
        )
    set_property(TARGET base64_test_cxx11 PROPERTY CXX_STANDARD 11)

    add_test(NAME cxx11 COMMAND base64_test_cxx11)

    # CXX17 version of test
    add_executable(base64_test_cxx17
            src/test.cpp
        )
    target_link_libraries(base64_test_cxx17
        PUBLIC
            base64
        )
    set_property(TARGET base64_test_cxx17 PROPERTY CXX_STANDARD 17)
    set_property(TARGET base64_test_cxx17 PROPERTY CXX_STANDARD_REQUIRED 17)

    add_test(NAME cxx17 COMMAND base64_test_cxx17)

    list(APPEND TARGETS base64_test_cxx17 base64_cxx11 base64_test_cxx11)
endif(${BASE64_ENABLE_TESTS})

# Find supported warning flags
foreach(FLAG ${WARNING_FLAGS})
    string(REPLACE "-" "_" VAR "HAVE${FLAG}")
    check_cxx_compiler_flag("-Werror ${FLAG}" ${VAR})
    if(${${VAR}})
        list(APPEND _WARNING_FLAGS ${FLAG})
    endif()
endforeach()

foreach(TARGET ${TARGETS})
    # Set warning flags on all targets (but don't export them)
    target_compile_options(${TARGET}
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${_WARNING_FLAGS}>
        )

    # Set include directories
    target_include_directories(
        ${TARGET}
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
endforeach()
