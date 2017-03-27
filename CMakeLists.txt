cmake_minimum_required(VERSION 2.8)
project(fgp21_search)

## Check for Windows ##
if (WIN32) # true if windows (32 and 64 bit)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()


set(SOURCE_FILES source.cpp)

add_executable(fgp21_search_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)


target_link_libraries(fgp21_search_run fgp21_search_library)