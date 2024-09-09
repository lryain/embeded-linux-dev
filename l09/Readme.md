# l09 install

目和库的导出安装，以便别人使用和docker封装
减少重复编译，保证部署有效性

新建install目录
把头文件都导出到install目录

1. 在qt_ui的CMakeList.txt文件中添加

```s
# 安装目标
#*********************************************
# 项目和库的导出安装，以便别人使用和docker封装
#*********************************************
# 安装目标
install(
    # 导出可执行文件和库
    TARGETS ${PROJECT_NAME}_test ${PROJECT_NAME} common
    # find(QtUi) 可以找到
    EXPORT FindQtUi
    RUNTIME DESTINATION ${MY_CMAKE_INSTALL_DIRECTORY}/bin
    LIBRARY DESTINATION ${MY_CMAKE_INSTALL_DIRECTORY}/lib
    ARCHIVE DESTINATION ${MY_CMAKE_INSTALL_DIRECTORY}/lib
)

# 头文件
install(FILES mainwindow.h rosNode.h ../common/myLog.h ../common/common.h
        DESTINATION ${MY_CMAKE_INSTALL_DIRECTORY}/include)

# 导出安装集，这样其他项目就可以使用find_package来找到my_library
install(EXPORT FindQtUi
        FILE FindQtUi.cmake 
        DESTINATION ${MY_CMAKE_INSTALL_DIRECTORY})
```

2. 在跟目录CMakeList.txt文件中添加
# 设置一个变量 然后子项目里都可以使用了
set(MY_CMAKE_INSTALL_DIRECTORY ${PROJECT_SOURCE_DIR}/install) # 设置安装目录 

3. 测试：
sudo make install

测试install 下的bin
./qt_ui_test 
Q:
./qt_ui_test: error while loading shared libraries: libqt_ui.so: cannot open shared object file: No such file or directory
A:
ldd qt_ui_test 指令查看依赖库
手动指定路径
在qt_ui的CMakeList.txt文件中添加
# 特定目标设置 INSTALL_RPATH 绝对路径
set_target_properties(${PROJECT_NAME}_test PROPERTIES
        INSTALL_RPATH ${MY_CMAKE_INSTALL_DIRECTORY}/lib
)

./qt_ui_test 
Q:
./qt_ui_test: error while loading shared libraries: libcommon.so: cannot open shared object file: No such file or directory

A:
ldd qt_ui_test 指令查看依赖库
手动指定路径
在qt_ui的CMakeList.txt文件中添加
# 特定目标设置 INSTALL_RPATH 绝对路径
set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH ${MY_CMAKE_INSTALL_DIRECTORY}/lib
)

./qt_ui_test: /lib/x86_64-linux-gnu/libQt5Core.so.5: version `Qt_5.15' not found (required by ./qt_ui_test)
./qt_ui_test: /lib/x86_64-linux-gnu/libQt5Core.so.5: version `Qt_5.15' not found (required by /home/lryain/dev/embeded-linux-dev/l09/install/bin/../lib/libqt_ui.so)
貌似QT的环境变量未设置好所导致，添加
nano /etc/profile
export LD_LIBRARY_PATH=~/Qt/5.15.1/gcc_64/lib:$LD_LIBRARY_PATH
还真是这个问题

## 删除指令

cat install_manifest.txt | xargs sudo rm

如果使用绝对路径，那么程序更换了位置就找不到库
需要手动指定LD链接库路径

## 指定
export LD_LIBRARY_PATH=/home/lryain/dev/embeded-linux-dev/l09/install/lib:$LD_LIBRARY_PATH

测试命令
rm -rf * && cmake .. &&  make -j4 && sudo make install
