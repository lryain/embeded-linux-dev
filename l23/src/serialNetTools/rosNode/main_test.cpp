#include <iostream>
#include "common.h"
#include "rosNode.h"
#include <QCoreApplication>
#include "myLog.h"

using namespace std;

int main(int argc, char** argv)//(int argc,char* argv[])
{
    Common common;
    string log_path = common.get_log_path();
    MyLog *myLog = new MyLog(log_path, "rosNode");

    LOG(INFO)<<"RosNode ---> My first log!!!";

    QCoreApplication app(argc, argv);

    // RosNode 是一个QThread线程
    RosNode *rosNode = new RosNode(argc, argv);
    rosNode->init();

    // 开始干活
    bool res = QMetaObject::invokeMethod(rosNode, "start", Qt::QueuedConnection);
    std::cout<<"res: "<<res<<std::endl;
    // QThread *p_rosNodeThread = new QThread();
    // rosNode->moveToThread(p_rosNodeThread);

    // QObject::connect(p_rosNodeThread, &QThread::started, rosNode, &RosNode::run);
    QObject::connect(rosNode, &RosNode::signal_rosShutdown, &app, &QCoreApplication::quit);

    // // 启动线程
    // p_rosNodeThread->start();
    int result = app.exec();

    // // 清理资源
    delete rosNode;
    // p_rosNodeThread->deleteLater();
    delete myLog;
    // sleep(1);

    return result;
}