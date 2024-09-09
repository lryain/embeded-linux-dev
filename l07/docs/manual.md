# gbd 调试

gdb ./serialNetTools_test
-c
run
bt
quit

手册

##

配置git
git config --global http.proxy http://192.168.3.8:7890
git config --global https.proxy http://192.168.3.8:7890
git config --global user.name "lryain"
git config --global user.email "47129927@qq.com"

## 封装日志

安装glog
git clone --depth=1 https://github.com/google/glog

```s
cd glog
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig`
```

#include <glog/logging.h>

## Q&A

Q: /usr/bin/ld: libqt_ui.so: undefined reference to `ros::shutdown()'

A: 添加ROS链接库即可


Q: Failed to find required Qt component "Widgets".

Qt needs some package to be installed to work to install dependencies type the following code and get working

sudo apt-get install build-essential libgl1-mesa-dev

## 编译运行命令

rm -rf * && cmake .
make

cmake 需要手动配置两个变量

set(QT_PREFIX_PATH "~/Qt/6.7.2/gcc_64")
set(CMAKE_PREFIX_PATH "${QT_PREFIX_PATH}/lib/cmake")


## 安装依赖

sudo apt install cmake

## 06

修复一个bug，导致找不到qt生成的头文件
# Header files
set(CMAKE_INCLUDE_CURRENT_DIR_ON) -> set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

