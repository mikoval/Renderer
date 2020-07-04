cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(/usr/local/lib)

project (renderer)
#add_executable(renderer main.cpp)

file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.cpp"
)

add_library(renderer STATIC ${SOURCES})

target_include_directories(renderer PUBLIC ./includes)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(renderer ${GLFW_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(renderer ${GLEW_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLM REQUIRED glew)
include_directories(${GLM_INCLUDE_DIRS})
target_link_libraries(renderer ${GLM_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(renderer ${OPENGL_LIBRARIES})

find_package( Threads )
target_link_libraries( renderer ${CMAKE_THREAD_LIBS_INIT} ) 
