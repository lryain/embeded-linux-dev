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

# Header files
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)

# common库 /home/lryain/dev/embeded-linux-dev/l07/src/common/build
# 指定common库的路径，然后根据这个路径定义一个链接库 给目标链接时使用
find_library(MY_COMMON_LIBRARY NAMES common PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../common/build)
link_directories(${MY_COMMON_LIBRARY})

# 导入QT5库
find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

# 导入ROS1库
find_package(catkin REQUIRED COMPONENTS
            roscpp
            rospy
            std_msgs
            sensor_msgs           
)

include_directories(${catkin_INCLUDE_DIRS})
message(STATUS "{catkin_INCLUDE_DIRS} : ${catkin_INCLUDE_DIRS}")

#************************
# 添加源文件
#************************
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h)
# file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp)
set(QT_SOURCES mainwindow.cpp rosNode.cpp)

#三个用于处理Qt特定资源和代码生成的命令
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) #从 .ui 文件自动生成用户界面类的头文件和源文件
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})#将 .qrc 资源文件转换成可编译的C++源文件
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #.h 文件（包含Qt对象的头文件）自动生成moc（元对象编译器）文件，这些文件是Qt信号和槽机制所必需的

#*************************
# 生成动态链接库
#************************
add_library(${PROJECT_NAME} SHARED  ${QT_SOURCES} 
                                    ${QT_RESOURCES_CPP} 
                                    ${QT_FORMS_HPP} 
                                    ${QT_MOC_HPP})
                                    
add_definitions(-DGLOG_USE_GLOG_EXPORT)

# 需要链接的库
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${catkin_LIBRARIES} ${MY_COMMON_LIBRARY})

# 可执行文件，不适用库
add_executable(${PROJECT_NAME}_test main.cpp)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})