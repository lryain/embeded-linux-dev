cmake_minimum_required(VERSION 3.16)

project(serialNetTools)

# set(DEFUALT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-w")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -ggdb ${CMAKE_CXX_FLAGS}")

# Header files
# set(CMAKE_INCLUDE_CURRENT_DIR_ON)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# exe file
add_executable(${PROJECT_NAME}_test main_test.cpp)