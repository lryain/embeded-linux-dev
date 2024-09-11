# l11 第二章 实战

ROS
1. 收发TCP网口数据
2. 收发收发数据
3. ROS收发数据
4. 日志类封装glog+自己造一个日志轮子
5. QT页面进行网口，串口配置，收发和查看以上消息
模块


qt_ui-ui
1. UI页面布局
2. 槽-接受tcp，serial，ros的消息
3. 信号-页面数据分发给tcp，serial，ros
4. 串口，网页，ROS初始化参数的配置

common-log
1. 日志类封装glog+
2. 单例模式

myTcp-tcpClient, tcpServer
tcp数据收发
rosNode:
1. 订阅发布ROS消息
2. 信号-ROS接收消息发送给外部
3. 槽-外部接收消息发送给ROS

SerialNetTools
1. 调用上述功能
2. 模块外部的信号于槽进行连接

mySerial
1. 串口数据收发
2. 信号-发送数据给外部
3. 槽-接收外部的消息