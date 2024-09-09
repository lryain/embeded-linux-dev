#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include <std_msgs/String.h>
#include <QThread>
#include <QDebug>
#include <QString>

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

public slots:
    void slot_pubStrMsg(const QString&);

Q_SIGNALS:
    void signal_rosShutdown();
    void signal_strMsg(const QString&);

private:
    int init_argc_;
    char **init_argv_;

};

