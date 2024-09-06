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

## 安装QT6

## qt依赖

sudo apt update
sudo apt install libxcb-cursor0
sudo apt install gcc g++ make
sudo apt install build-essential libgl1-mesa-dev

下载QT6在线安装个安装程序
chmod +x qt-online-installer-linux-x64-4.8.0.run
./qt-online-installer-linux-x64-4.8.0.run

## 添加Qt环境变量

sudo nano /etc/profile 

第二步：在末尾添加qtcreator和qmake路径，其中“/opt/Qt5.12.8/”是我的Qt安装路径，请以Qt的实际安装路径为准。

export PATH="~/Qt/Tools/QtCreator/bin:$PATH"
export PATH="~/Qt/6.7.2/gcc_64:$PATH"


## Q&A

Q: Failed to find required Qt component "Widgets".

Qt needs some package to be installed to work to install dependencies type the following code and get working

sudo apt-get install build-essential libgl1-mesa-dev

## 注意

rm -rf * && cmake .
需要手动将生成的l05/src/qt_ui/build/ui_mainwindow.h头文件复制到qt_ui工作目录，然后再make
make
或者更改头文件路径
#include "build/ui_mainwindow.h"

cmake 需要手动配置两个变量

set(QT_PREFIX_PATH "~/Qt/6.7.2/gcc_64")
set(CMAKE_PREFIX_PATH "${QT_PREFIX_PATH}/lib/cmake")


## 安装依赖

sudo apt install cmake