#pragma once

#ifndef Q_MOC_RUN
// #include <ros2/>
#include <rclcpp/rclcpp.hpp>
#endif

#include <std_msgs/msg/string.hpp>
#include <QThread>

class RosNode : public QThread, public rclcpp::Node
{
    Q_OBJECT // 这个是QT元对象系统的必须部分，它启用了信号，槽和属性等特性

public:
    RosNode(int argc, char** argv);
    virtual ~RosNode();
    bool init();
    void run() override;

    void callback_strMsg(const std_msgs::msg::String& msg);
    void slot_pubStrMsg(const QString& msg);

    std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> pub_str_msg;
    std::shared_ptr<rclcpp::Subscription<std_msgs::msg::String>> sub_str_msg;

    // rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_str_msg;
    // rclcpp::Publisher<std_msgs::msg::String> pub_str_msg;
    // rclcpp::Subscription<std_msgs::msg::String> sub_str_msg;

Q_SIGNALS:
    void signal_rosShutdown();
    void signal_strMsg(const QString&);

private:
    int init_argc_;
    char **init_argv_;

    static inline rclcpp::Node::SharedPtr qt_ui_node_;
};

