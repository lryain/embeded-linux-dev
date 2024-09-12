#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include <std_msgs/String.h>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QVariantMap> // 新加入

class RosNode : public QThread
{
    Q_OBJECT // 这个是QT元对象系统的必须部分，它启用了信号，槽和属性等特性

public:
    RosNode(int argc, char** argv);
    virtual ~RosNode();
    bool init();
    void run() override;

    void callback_strMsg(const std_msgs::StringConstPtr& msg);

    ros::Publisher pub_str_msg;
    ros::Subscriber sub_str_msg;

Q_SIGNALS:
    void signal_rosShutdown();
    void signal_ros_strMsg(const QVariantMap&);

public slots:
    void slot_ros_pubStrMsg(const QString&);

private:
    int init_argc_;
    char** init_argv_;

};

