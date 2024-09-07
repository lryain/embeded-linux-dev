#include "rosNode.h"
#include <QCoreApplication>

RosNode::RosNode(int argc, char** argv) : init_argc_(argc), init_argv_(argv), Node("qt_ui")
{
}

RosNode::~RosNode()
{
    // if(rclcpp::isStarted())
    rclcpp::shutdown();
    // rclcpp::waitForShutdown
}

bool RosNode::init()
{
    // 初始化ROS
    rclcpp::init(init_argc_, init_argv_);
    qt_ui_node_ = rclcpp::Node::make_shared("qt_ui");

    // 发送和订阅
    pub_str_msg = this->create_publisher<std_msgs::msg::String>("topic", 10);
    sub_str_msg = this->create_subscription<std_msgs::msg::String>("/str_msg", rclcpp::QoS(rclcpp::KeepLast(10)), std::bind(&RosNode::callback_strMsg, this, std::placeholders::_1));

    start();

    return true;
}

void RosNode::run()
{
    // rclcpp::executors::SingleThreadedExecutor executor_;
    // qt_ui_node->Start();
    this->start();
    // executor_.add_node(qt_ui_node_);
    // executor_.spin();
    // rclcpp::spin(qt_ui_node_);

    rclcpp::Rate rate(10);

    while (rclcpp::ok())
    {
        QCoreApplication::processEvents(); //确保QT事件循环得到处理
        rclcpp::spin_some(qt_ui_node_);
        rate.sleep();
    }

    Q_EMIT signal_rosShutdown();
}

void RosNode::slot_pubStrMsg(const QString& msg)
{
    std_msgs::msg::String str_msg;
    str_msg.data = msg.toStdString();
    pub_str_msg->publish(str_msg);
}

/**
 * ros消息的回调函数
 */
void RosNode::callback_strMsg(const std_msgs::msg::String& msg)
{
    Q_EMIT signal_strMsg(QString::fromStdString(msg.data));
}