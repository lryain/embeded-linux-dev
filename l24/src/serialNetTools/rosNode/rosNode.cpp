#include "rosNode.h"
#include <QCoreApplication>

RosNode::RosNode(int argc, char** argv) : init_argc_(argc), init_argv_(argv)
{
}

RosNode::~RosNode()
{
    if(ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }
}

bool RosNode::init()
{
    // 初始化ROS
    ros::init(init_argc_, init_argv_, "qt_ui");

    if(!ros::master::check()) return false;
    ros::start();
    ros::NodeHandle n;

    // 发送和订阅
    pub_str_msg = n.advertise<std_msgs::String>("/str_msg", 10);
    sub_str_msg = n.subscribe("/str_msg", 10, &RosNode::callback_strMsg, this);

    // start(); // start函数要从外部调用，而不是ros节点

    return true;
}

void RosNode::run()
{
    ros::start();
    ros::NodeHandle n;

    ros::Rate rate(10);
    while (ros::ok())
    {
        QCoreApplication::processEvents(); //确保QT事件循环得到处理
        ros::spinOnce();
        rate.sleep();
    }

    Q_EMIT signal_rosShutdown();
}

void RosNode::slot_ros_pubStrMsg(const QString& msg)
{
    std_msgs::String str_msg;
    str_msg.data = msg.toStdString();
    // std::cout<< str_msg.data << endl;
    pub_str_msg.publish(str_msg);
}

/**
 * ros消息的回调函数
 * 将ros订阅到的消息内容 通过QT信号发送出去
 */
void RosNode::callback_strMsg(const std_msgs::StringConstPtr& msg)
{
    std::cout<<"msg-data: "<<msg->data<<std::endl;
    
    QVariantMap data;
    data["type"] = "rosNode";
    data["data"] = QString::fromStdString(msg->data);
    Q_EMIT signal_ros_strMsg(data);
}