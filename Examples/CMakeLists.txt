cmake_minimum_required(VERSION 2.8.9)

project (Sandbox0)
project (Pong)
project (Platformer)



LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)
include_directories(./src)

file(GLOB_RECURSE SANDBOX0_SOURCES
    "src/*.h"
    "src/*.cpp"
    "Sandbox0/*.cpp"
    "Sandbox0/*.h"
)

file(GLOB_RECURSE PONG_SOURCES
    "src/*.h"
    "src/*.cpp"
    "Pong/*.cpp"
    "Pong/*.h"
)

file(GLOB_RECURSE PLATFORMER_SOURCES
    "src/*.h"
    "src/*.cpp"
    "Platformer/*.cpp"
    "Platformer/*.h"
)

add_executable(Sandbox0 ${SANDBOX0_SOURCES})

add_executable(Pong ${PONG_SOURCES})

add_executable(Platformer ${PLATFORMER_SOURCES})



target_link_libraries (Sandbox0 renderer) 
target_link_libraries (Sandbox0 box2d) 
target_link_libraries (Pong renderer) 
target_link_libraries (Pong box2d) 
target_link_libraries (Platformer renderer) 
target_link_libraries (Platformer box2d) 
