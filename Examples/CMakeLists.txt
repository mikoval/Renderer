cmake_minimum_required(VERSION 2.8.9)

project (example)

find_package( Threads )

include_directories (${RENDERER_SOURCE_DIR}/includes) 
link_directories (${RENDERER_BINARY_DIR}/renderer) 

LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)

add_executable(example main.cpp)



target_link_libraries (example renderer) 
target_link_libraries (example box2d) 
target_link_libraries (example glfw) 
target_link_libraries (example glad) 
target_link_libraries( example ${CMAKE_THREAD_LIBS_INIT} )
