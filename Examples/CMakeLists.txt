cmake_minimum_required(VERSION 2.8.9)

project (example)


#include_directories (${RENDERER_SOURCE_DIR}/includes) 
#link_directories (${RENDERER_BINARY_DIR}/renderer) 


LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)

add_executable(example main.cpp)



# Establish target libraries and include directories
if (APPLE)

    list(APPEND glfw_LIBRARIES
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo")
endif()


target_link_libraries (example ${CMAKE_DL_LIBS})
target_link_libraries (example ${RT_LIBRARY})
target_link_libraries (example glfw) 
target_link_libraries (example renderer) 
target_link_libraries (example box2d) 
#target_link_libraries (example glad) 
