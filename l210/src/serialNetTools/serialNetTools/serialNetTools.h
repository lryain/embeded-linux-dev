// #ifndef SERIALNETTOOLS_H
// #define SERIALNETTOOLS_H
#pragma once

#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include <QVariantMap>
#include <QHash>
#include <QThread>
#include "mySerial.h"
#include "tcpClient.h"
#include "tcpServer.h"
#include "rosNode.h"

using namespace std;


class SerialNetTools : public QObject
{

Q_OBJECT

public:
     SerialNetTools(int argc, char** argv);
    ~ SerialNetTools();
    int init();

public slots:
    void slot_switch(const QVariantMap&);

signals:
    void signal_tips(const QVariantMap&);

private:
    // 解析和分发逻辑
    // 串口开关
    void switch_mySerial(const QVariantMap&);
   
    void switch_tcpClient(const QVariantMap&); // TCP客户端开关
    void switch_tcpServer(const QVariantMap&); // TCP服务器开关

private:
    int argc_;
    char** argv_;
    // 用QHash来作绑定 来简化if else语句
    QHash<QString, std::function<void(const QVariantMap&)>> switchMap_;

    MySerial *mySerial_ = nullptr;
    MainWindow * mainWindow_ = nullptr;
    QApplication *app_ = nullptr;
    QThread *mySerial_thread_ = nullptr;
    TcpClient *tcpClient_ = nullptr;
    TcpServer *tcpServer_ = nullptr;
    RosNode *rosNode_ = nullptr;
    QThread *ros_thread_ = nullptr;
};





// #endif