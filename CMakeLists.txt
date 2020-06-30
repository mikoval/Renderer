cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project (renderer)
add_executable(renderer Renderer/main.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(renderer ${GLFW_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(renderer ${GLEW_LIBRARIES})
