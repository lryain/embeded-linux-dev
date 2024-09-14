# l210 ROS节点

## 编码原则

高内聚，低耦合

## 内容

在 serialNetTools 模块中调用ROS节点
在 serialNetTools 模块添加一个新模块的步骤：
1. 在CMakeList.txt 中添加依赖
   1. # find_package(catkin REQUIRED COMPONENTS roscpp std_msgs sensor_msgs)
   2. include_directories(${catkin_INCLUDE_DIRS})
   3. target_link_libraries(${PROJECT_NAME} ... rosNode)
2. serialNetTools.h 添加头文件 #include "rosNode.h"
3. 在serialNetTools.h 中添加 QThread 和 RosNode私有变量，便于管理和销毁
   1. QThread *rosNode_ = nullptr;
   2. RosNode *rosNode_ = nullptr;
4. 在serialNetTools.cpp 中初始化 RosNode rosNode_ = new RosNode(argc_, argc_);

添加信号处理

1. QT线程开始要通知节点开始运行
2. 节点关闭要通知QT程序退出
3. 节点信号映射 ROS接收到消息 -> 通知QTUI进行显示
4. QTUI发送数据到ROS -> 通知ROS接收消息
   1. MainWindow.h 中需要有相应的信号 signal_rosPub
5. 添加槽函数 ros发送按钮 slot_btn_rosNode_send
6. 在QT mainwindow.cpp 中添加连接该RosNode的槽信号 如果发送按钮按下则调用 MainWindow::slot_btn_rosNode_send函数处理

## Log

l210:
QThread: Destroyed while thread is still running
原因：线程没有正确退出

目前有一个bug：
原因：add_subdirectory(test) 中的QtUi库需要 sudo make install 后才能找到
# 查找QtUi库
find_package(QtUi REQUIRED)

2. 然后 sudo make install 会报错：
Traceback (most recent call last):
  File "/home/lryain/dev/embeded-linux-dev/l24/build/catkin_generated/generate_cached_setup.py", line 20, in <module>
    from catkin.environment_cache import generate_environment_script
ModuleNotFoundError: No module named 'catkin'
原因：
没有make就直接 make install 所以报错

## 所以正确的顺序是：
1. 注释掉根目录的 add_subdirectory(test)
因为他是从install目录引用库
2. cmake .. && make -j8
3. sudo make install
4. 打开根目录的 add_subdirectory(test)
5. cmake .. && make -j8
