
# 安装QT5

## qt依赖

下载QT5在线安装个安装程序
https://d13lb3tujbc8s0.cloudfront.net/onlineinstallers/qt-online-installer-linux-x64-4.8.0.run
chmod +x qt-online-installer-linux-x64-4.8.0.run
./qt-online-installer-linux-x64-4.8.0.run

sudo apt update
sudo apt install libxcb-cursor0
sudo apt install gcc g++ make
sudo apt install build-essential libgl1-mesa-dev

## 添加Qt环境变量

sudo nano /etc/profile 

第二步：在末尾添加qtcreator和qmake路径，其中“/opt/Qt5.15.1/”是我的Qt安装路径，请以Qt的实际安装路径为准。

export PATH="~/Qt/Tools/QtCreator/bin:$PATH"
export PATH="~/Qt/5.15.1/gcc_64:$PATH"

source /etc/profile

## vscode c++path添加

include path for vscode
"~/Qt/5.15.1/gcc_64/include/**",
"~/Qt/5.15.1/gcc_64/include/*"