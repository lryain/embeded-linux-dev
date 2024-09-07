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

set(ROS2_INCLUDE_PATH "/opt/ros/jazzy/include")
set(QT_PREFIX_PATH "~/Qt/6.7.2/gcc_64")
set(CMAKE_PREFIX_PATH "${QT_PREFIX_PATH}/lib/cmake")
set(CMAKE_AUTOUIC ON)

# message(STATUS "QT_PREFIX_PATH : ${QT_PREFIX_PATH}")
# message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

# Header files
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 导入QT库
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
# 导入ROS库
# set(dependencies rclcpp)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# ${ROS2_INCLUDE_PATH}/std_msgs
include_directories(${ROS2_INCLUDE_PATH}/std_msgs)
message(STATUS "{ROS2_INCLUDE_PATH}/std_msgs : ${ROS2_INCLUDE_PATH}/std_msgs")
# message(STATUS "{ament_LIBRARIES} : ${ament_LIBRARIES}")

#************************
# 添加源文件
#************************
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h)
# file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp)
set(QT_SOURCES mainwindow.cpp rosNode.cpp)

#三个用于处理Qt特定资源和代码生成的命令
QT6_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) #从 .ui 文件自动生成用户界面类的头文件和源文件
QT6_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})#将 .qrc 资源文件转换成可编译的C++源文件
QT6_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #.h 文件（包含Qt对象的头文件）自动生成moc（元对象编译器）文件，这些文件是Qt信号和槽机制所必需的

#*************************
# 生成动态链接库
#************************
add_library(${PROJECT_NAME} SHARED  ${QT_SOURCES} 
                                    ${QT_RESOURCES_CPP} 
                                    ${QT_FORMS_HPP} 
                                    ${QT_MOC_HPP}
                                    # ${ROS2_INCLUDE_PATH}/std_msgs
                                )

# target_link_libraries(${PROJECT_NAME} Qt6::Widgets ${ament_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# 可执行文件，不适用库
add_executable(${PROJECT_NAME}_test main.cpp)

ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
# ament_package()