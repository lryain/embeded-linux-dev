# l24 第二章 serialNetTools

mySerial
1. 串口数据收发
2. 信号-发送数据给外部
3. 槽-接收外部的消息

serialNetTools完善

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
