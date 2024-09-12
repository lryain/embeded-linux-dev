#include <iostream>
#include "common.h"
#include "mySerial.h"
#include <QCoreApplication>
#include <QThread>
#include "myLog.h"

using namespace std;

int main(int argc, char** argv)
{
    Common common;
    string log_path = common.get_log_path();
    MyLog *myLog = new MyLog(log_path, "mySerial");

    LOG(INFO)<<"mySerial test start.";

    QCoreApplication app(argc, argv);

    // MySerial 是一个QObject对象
    MySerial *mySerial = new MySerial();

    // 使用QT线程
    QThread *thread = new QThread();
    mySerial->moveToThread(thread);
    thread->start();
    LOG(INFO)<<"mySerial thread start.";

    mySerial->init("1", "/dev/ttyUSB0", 115200, 0, 8, 1);
    // QMetaObject::invokeMethod(mySerial, "slot_start", Qt::QueuedConnection);
    QMetaObject::invokeMethod(mySerial, "start", Qt::QueuedConnection);

    // QObject::connect(rosNode, &RosNode::signal_rosShutdown, &app, &QCoreApplication::quit);

    // delete mySerial;
    // delete myLog;

    return app.exec();
}