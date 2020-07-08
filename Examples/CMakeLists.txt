cmake_minimum_required(VERSION 2.8.9)

project (example)



LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)

file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.cpp"
)

add_executable(example ${SOURCES})




target_link_libraries (example renderer) 
target_link_libraries (example box2d) 
