cmake_minimum_required(VERSION 3.13)
project(cpy)

#set(CMAKE_LIBRARY_PATH ./build)
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

file(GLOB SOURCES src/*.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(cpy SHARED ${SOURCES})
set_target_properties(cpy PROPERTIES PUBLIC_HEADER include/cpy.h)

#add_library(vld SHARED IMPORTED)
#set_target_properties( vld PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/build/vld_x64)


add_executable(out example.c)
#add_subdirectory(./module/vld) #doesn't work
#link_directories(${CMAKE_SOURCE_DIR}/build)
target_link_directories(out PUBLIC ${CMAKE_SOURCE_DIR}/build) #external pre-compiled .dll or .so
target_include_directories(out PUBLIC ${CMAKE_SOURCE_DIR}/module/vld_x64) #external pre-compiled .dll or .so
#find_library(vld ./build/vld_x64) #won't work: searches in CMAKE_PREFIX
target_link_libraries(out PUBLIC cpy)
#target_link_libraries(out PRIVATE vld_x64)
#target_link_libraries(out PRIVATE dbghelp)


if (MINGW)
else()
    target_compile_options(out PRIVATE -fsanitize=address)
    target_link_options(out PRIVATE -fsanitize=address)

endif(MINGW)