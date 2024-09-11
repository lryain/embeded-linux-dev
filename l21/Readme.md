# l21 第二章 串口模块

mySerial
1. 串口数据收发
2. 信号-发送数据给外部
3. 槽-接收外部的消息

sudo apt install cutecom
找一个USB转串口设备插上电脑 FT232 CH340
sudo chmod 777 /dev/ttyUSB0

virtualbox 的ubuntu 上使用cutecom 关闭串口会死机
换 vmware station pro就可以了

vmware station 的ubuntu会找不到ttyUSB0
sudo dmesg | grep brltty
需要卸载掉
sudo apt remove brltty
然后重新插拔以下USB设备
ls /dev/ttyUSB0

接下来在VMware上重新安装环境
