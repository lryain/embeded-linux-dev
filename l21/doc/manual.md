# manual

## gbd 调试

gdb ./serialNetTools_test
-c
run
bt
quit

## 配置git

git config --global http.proxy http://192.168.3.8:7890
git config --global https.proxy http://192.168.3.8:7890
git config --global user.name "lryain"
git config --global user.email "47129927@qq.com"

## ENV

change language to chinese

安装vscode并**配置proxy**

安装[ros1](/doc/ros1.md)

安装[qt5](/doc/qt.md)

安装[glog](/doc/glog.md)

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

## ros 测试

roscore
rostopic pub /str_msg std_msgs/String "data: 'hello-ros'"
rostopic echo /str_msg


