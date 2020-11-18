# find your Generators: 
#   cmd: cmake -G

# example, system default Generators, linux=gcc, windows=msvc:
#   cd L:\0_cpp_plus\base64
#   mkdir L:\0_cpp_plus\base64\build
#   cd L:\0_cpp_plus\base64\build
#   cmake ..
#   cmake --build . --config Release
# lib path: 

# example, minGW: 
#   cd L:\0_cpp_plus\base64
#   mkdir L:\0_cpp_plus\base64\gcc
#   cd L:\0_cpp_plus\base64\gcc
#   cmake  -G "MinGW Makefiles" ..
#   cmake --build . --config Release 
# lib path: L:\0_cpp_plus\base64\gcc\libbase64.a

# example, msvc: 
#   cd L:\0_cpp_plus\base64
#   mkdir L:\0_cpp_plus\base64\msvc
#   cd L:\0_cpp_plus\base64\msvc
#   cmake -G "Visual Studio 16 2019" ..
#   cmake --build . --config Release 
# lib path: L:\0_cpp_plus\base64\msvc\Release\base64.lib


cmake_minimum_required(VERSION 3.8)
project(base64 VERSION 0.1.0)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("/utf-8")
    add_compile_options("/O2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options("-O3")
endif()

include_directories(${PROJECT_SOURCE_DIR})
add_library(base64 base64.cpp)

message("project dir: ${PROJECT_SOURCE_DIR}")

