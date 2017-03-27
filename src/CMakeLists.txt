cmake_minimum_required(VERSION 2.8)

project(fgp21_search_library)

## Check for Windows ##
if (WIN32) # true if windows (32 and 64 bit)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ()


set(HEADER_FILES PathFinding.h VectorMaths.h SearchCell.h)

set(SOURCE_FILES PathFinding.cpp VectorMaths.cpp)

add_library(fgp21_search_library ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(fgp21_search_library PROPERTIES LINKER_LANGUAGE CXX)