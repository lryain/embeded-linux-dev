cmake_minimum_required(VERSION 3.16)

project(common)

# 查找glog库
find_package(glog REQUIRED)

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
set(CMAKE_INCLUDE_CURRENT_DIR_ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# dynamic 动态链接库
# add_library(${PROJECT_NAME} SHARED serialNetTools.cpp)
add_library(${PROJECT_NAME} SHARED common.cpp myLog.cpp)
target_link_libraries(${PROJECT_NAME} glog::glog)

# 可执行文件，不适用库
# add_executable(${PROJECT_NAME}_test main_test.cpp serialNetTools.cpp)
add_executable(${PROJECT_NAME}_test main_common_test.cpp)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})