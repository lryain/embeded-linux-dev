# Q&A

Q: /usr/bin/ld: libqt_ui.so: undefined reference to `ros::shutdown()'

A: 添加ROS链接库即可


Q: Failed to find required Qt component "Widgets".

Qt needs some package to be installed to work to install dependencies type the following code and get working

sudo apt-get install build-essential libgl1-mesa-dev

## 编译运行命令

rm -rf * && cmake .
make

## 安装依赖

sudo apt install cmake

## 06

修复一个bug，导致找不到qt生成的头文件
# Header files
set(CMAKE_INCLUDE_CURRENT_DIR_ON) -> set(CMAKE_INCLUDE_CURRENT_DIR ON)

## ros1

Q:
sudo apt install cmake
src/serialNetTools/rosNode/CMakeLists.txt:11 (find_package)
find_package(catkin REQUIRED COMPONENTS
ModuleNotFoundError: No module named 'catkin'

A:
没有make就直接 make install 所以报错

## 安装ros2

git clone https://github.com/fishros/install
sudo nano ~/.bashrc
在最后一行添加：
source /opt/ros/jazzy/setup.bash

ros2 头文件
/opt/ros/jazzy/include

## 添加ros依赖

但是找不到ros包
Q: Could not find a package configuration file provided by "catkin" with any
  of the following names:
A:
list(APPEND CMAKE_MODULE_PATH ${CMAKE_PREFIX_PATH})

# Verify
message(STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")

## 报错

1.找不到rclcpp/rclcpp.h

在 add_executable 之后添加 ament_target_dependencies
add_executable(${PROJECT_NAME}_test main.cpp)

ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs)

2. /usr/bin/ld: libqt_ui.so: undefined reference to `RosNode::run()'
定义 void RosNode::run() 方法即可！

## Ros1 向 Ros2 迁徙

报错：
Q:/usr/bin/ld: 找不到 -lcommon
A:
# 指定common库的路径，然后根据这个路径定义一个链接库 给目标链接时使用
find_library(MY_COMMON_LIBRARY NAMES common PATHS /home/lryain/dev/embeded-linux-dev/l07/src/common/build)
link_directories(${MY_COMMON_LIBRARY})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${catkin_LIBRARIES} ${MY_COMMON_LIBRARY})

Q：
# Header files 由于qt工程的特殊性，这个还是要加上 才能找到ui_mainwindow.h头文件 否则报错：fatal error: ./ui_mainwindow.h: 没有那个文件或目录
A：
加上
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})