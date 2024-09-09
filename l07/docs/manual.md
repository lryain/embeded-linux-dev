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


## ros 测试

roscore
rostopic pub /str_msg std_msgs/String "data: 'hello-ros'"
rostopic echo /str_msg

## 在qt_ui模块导入日志模块

在CMakeLists.txt文件中添加
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)
# 需要链接的库
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${catkin_LIBRARIES} common)

报错：
Q:/usr/bin/ld: 找不到 -lcommon
A:
# 指定common库的路径，然后根据这个路径定义一个链接库 给目标链接时使用
find_library(MY_COMMON_LIBRARY NAMES common PATHS /home/lryain/dev/embeded-linux-dev/l07/src/common/build)
link_directories(${MY_COMMON_LIBRARY})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${catkin_LIBRARIES} ${MY_COMMON_LIBRARY})