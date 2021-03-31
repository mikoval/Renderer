cmake_minimum_required(VERSION 2.8.9)

project (b2_Sandbox0)
project (Pong)
project (Platformer)
project (3D_Sandbox0)
project (3D_Sandbox1)



LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)
include_directories(./src)

file(GLOB_RECURSE B2_SANDBOX0_SOURCES
    "src/*.h"
    "src/*.cpp"
    "b2_Sandbox0/*.cpp"
    "b2_Sandbox0/*.h"
)

file(GLOB_RECURSE 3D_SANDBOX0_SOURCES
    "3D_Sandbox0/*.cpp"
    "3D_Sandbox0/*.h"
)
file(GLOB_RECURSE 3D_SANDBOX1_SOURCES
    "3D_Sandbox1/*.cpp"
    "3D_Sandbox1/*.h"
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

add_executable(b2_Sandbox0 ${B2_SANDBOX0_SOURCES})

add_executable(3D_Sandbox0 ${3D_SANDBOX0_SOURCES})
add_executable(3D_Sandbox1 ${3D_SANDBOX1_SOURCES})

add_executable(Pong ${PONG_SOURCES})

add_executable(Platformer ${PLATFORMER_SOURCES})



target_link_libraries (b2_Sandbox0 renderer) 
target_link_libraries (b2_Sandbox0 box2d) 
target_link_libraries (Pong renderer) 
target_link_libraries (Pong box2d) 
target_link_libraries (Platformer renderer) 
target_link_libraries (Platformer box2d) 

target_link_libraries (3D_Sandbox0 renderer) 
target_link_libraries (3D_Sandbox1 renderer) 
