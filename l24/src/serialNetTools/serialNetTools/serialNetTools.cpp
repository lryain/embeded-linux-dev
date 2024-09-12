#include "serialNetTools.h"


SerialNetTools:: SerialNetTools(int argc, char** argv):argc_(argc), argv_(argv)
{
}

SerialNetTools:: ~SerialNetTools()
{
}

/**
 * 程序入口
 */
int SerialNetTools::init()
{
    app_ = new QApplication(argc_, argv_);
    mainWindow_ = new MainWindow(argc_, argv_);
    mainWindow_->show();
    
    // 初始化mySerial
    // 如果主窗口发送开关信号，发送给 SerialNetTools::slot_switch 槽来处理
    QObject::connect(mainWindow_, &MainWindow::signal_switch, this, &SerialNetTools::slot_switch);
    switchMap_["mySerial"] = [this](const QVariantMap& msg){switch_mySerial(msg);};

    // 实例化 MySerial
    mySerial_ = new MySerial();
        // 使用QT线程
    mySerial_thread_ = new QThread();
    mySerial_->moveToThread(mySerial_thread_);

    QObject::connect(mySerial_, &MySerial::signal_openStatus, mainWindow_, &MainWindow::slot_mod_status, Qt::QueuedConnection);
    QObject::connect(mySerial_, &MySerial::signal_serial, mainWindow_, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);
    QObject::connect(mainWindow_, &MainWindow::signal_serialSend, mySerial_, &MySerial::slot_write, Qt::QueuedConnection);

    mySerial_thread_->start();
    LOG(INFO)<<"mySerialNetTools thread start.";

    return app_->exec();
}

/**
 * 串口开关逻辑
 */
void SerialNetTools::switch_mySerial(const QVariantMap& msg)
{
    bool state = msg.value("switch").toBool();

    if(state==true){
        string serialName = msg.value("serialName").toString().toStdString();
        int baudRate = msg.value("baudRate").toInt();
        int checkBit = msg.value("checkBit").toInt();
        int dataBit = msg.value("dataBit").toInt();
        int stopBit = msg.value("stopBit").toInt();

        mySerial_->init("1", serialName, baudRate, checkBit, dataBit, stopBit);
        QMetaObject::invokeMethod(mySerial_, "start", Qt::QueuedConnection);
    }else{
        LOG(INFO)<<"mySerial_->stop()";
        QMetaObject::invokeMethod(mySerial_, "stop", Qt::QueuedConnection);
    }


}

/**
 * 各个模块的开关
 */
void SerialNetTools::slot_switch(const QVariantMap& msg)
{
    if(!msg.contains("type")&&!msg.contains("state"))
    {
        return;
    }

    // 名字解析出来，然后用HashMap去找
    QString type = msg.value("type").toString();
    switchMap_[type](msg);
}