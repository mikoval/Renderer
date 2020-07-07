cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)

project (renderer)
#add_executable(renderer main.cpp)

file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.cpp"
)

add_library(renderer STATIC ${SOURCES})

target_include_directories(renderer PUBLIC ./includes)

find_package( Threads )
target_link_libraries( renderer ${CMAKE_THREAD_LIBS_INIT} ) 


target_link_libraries (renderer ${CMAKE_DL_LIBS})
target_link_libraries (renderer glfw)
target_link_libraries (renderer glad)
