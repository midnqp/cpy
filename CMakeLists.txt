cmake_minimum_required(VERSION 2.8.12)
project(cpy)
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

file(GLOB SOURCES src/*.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(cpy SHARED ${SOURCES})
set_target_properties(cpy PROPERTIES PUBLIC_HEADER include/cpy.h)

add_executable(out example.c)
target_link_libraries(out PUBLIC cpy)

if (MINGW)
else()
    target_compile_options(out PRIVATE -fsanitize=address)
    target_link_options(out PRIVATE -fsanitize=address)

endif()