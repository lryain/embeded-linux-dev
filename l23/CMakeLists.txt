cmake_minimum_required(VERSION 3.16)

project(Serial_Net_Tools)

# set(DEFUALT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-w")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -ggdb ${CMAKE_CXX_FLAGS}")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # 可执行文件输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # 动态库文件输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # 静态库文件输出目录
# 设置一个变量 然后子项目里都可以使用了
set(MY_CMAKE_INSTALL_DIRECTORY ${PROJECT_SOURCE_DIR}/install) # 设置安装目录 

# 添加头文件
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/common)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/qt_ui)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/rosNode)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/mySerial)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/serialNetTools)
include_directories(${PROJECT_SOURCE_DIR}/build/devel/include) # for ROS

# !!套娃添加!!
add_subdirectory(src)