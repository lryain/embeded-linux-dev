cmake_minimum_required(VERSION 3.16)

project(qt_ui)

# set(DEFUALT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-w")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -ggdb ${CMAKE_CXX_FLAGS}")

set(QT_PREFIX_PATH "~/Qt/6.7.2/gcc_64")
set(CMAKE_PREFIX_PATH "${QT_PREFIX_PATH}/lib/cmake")

# message(STATUS "QT_PREFIX_PATH : ${QT_PREFIX_PATH}")
# message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

# 倒入QT库
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

# Header files
set(CMAKE_INCLUDE_CURRENT_DIR_ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#************************
# 添加源文件
#************************
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h)
# file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp)
set(QT_SOURCES mainwindow.cpp)

#三个用于处理Qt特定资源和代码生成的命令
QT6_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) #从 .ui 文件自动生成用户界面类的头文件和源文件
QT6_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})#将 .qrc 资源文件转换成可编译的C++源文件
QT6_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #.h 文件（包含Qt对象的头文件）自动生成moc（元对象编译器）文件，这些文件是Qt信号和槽机制所必需的

# dynamic 动态链接库
#*************************
# 生成动态库
#************************
add_library(${PROJECT_NAME} SHARED  ${QT_SOURCES} 
                                    ${QT_RESOURCES_CPP} 
                                    ${QT_FORMS_HPP} 
                                    ${QT_MOC_HPP})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
# 可执行文件，不适用库
add_executable(${PROJECT_NAME}_test main.cpp)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
