#include "serialNetTools.h"

SerialNetTools::SerialNetTools(int argc, char **argv) : argc_(argc), argv_(argv)
{
}

SerialNetTools::~SerialNetTools()
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

    // 更新消息显示
    QObject::connect(this, &SerialNetTools::signal_tips, mainWindow_, &MainWindow::slot_send_textEdit);
    /**
     * 初始化mySerial
     * 1. 模块开关量连接 2. QHash 字符串和函数指针的绑定
     */
    // 如果主窗口发送开关信号，发送给 SerialNetTools::slot_switch 槽来处理
    QObject::connect(mainWindow_, &MainWindow::signal_switch, this, &SerialNetTools::slot_switch);
    // 初始化Hash 函数表绑定 mySerial 绑定到 switch_mySerial()函数
    switchMap_["mySerial"] = [this](const QVariantMap &msg){ switch_mySerial(msg); };

    // 实例化 MySerial
    mySerial_ = new MySerial();
    // 使用QT线程
    mySerial_thread_ = new QThread();
    mySerial_->moveToThread(mySerial_thread_);

    // 串口模块和MainWindow的直连
    // 1. 打开状态
    QObject::connect(mySerial_, &MySerial::signal_openStatus, mainWindow_, &MainWindow::slot_mod_status, Qt::QueuedConnection);
    // 2. 接收串口数据
    QObject::connect(mySerial_, &MySerial::signal_serial, mainWindow_, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);
    // 3. 发送串口数据
    QObject::connect(mainWindow_, &MainWindow::signal_serialSend, mySerial_, &MySerial::slot_write, Qt::QueuedConnection);

    mySerial_thread_->start();

    LOG(INFO) << "mySerialNetTools thread start.";

    /**
     * tcpClient 初始化 绑定开关函数
     */
    switchMap_["tcpClient"] = [this](const QVariantMap &msg){ switch_tcpClient(msg); };

    /**
     * tcpServer 初始化 绑定开关函数
     */
    switchMap_["tcpServer"] = [this](const QVariantMap &msg){ switch_tcpServer(msg); };

    return app_->exec();
}

/**
 * TCPClient 开关逻辑
 */
void SerialNetTools::switch_tcpClient(const QVariantMap &msg)
{
    LOG(INFO) << "SerialNetTools ---------> switch_tcpClient";
    bool state = msg.value("switch").toBool();

    if (state == true)
    {
        string ip = msg.value("ip").toString().toStdString();
        int port = msg.value("port").toInt();

        tcpClient_ = new TcpClient();
        tcpClient_->init("1", ip, port);

        // slot_mod_status 是一个串口和TCP模块公用的处理函数
        QObject::connect(tcpClient_, &TcpClient::signal_openStatus, mainWindow_, &MainWindow::slot_mod_status);
        bool res = tcpClient_->start();
        if (res)
        {
            // 如果连接成功，绑定signal_tcpClient 到 slot_send_textEdit
            // 也就是说，如果接收到消息，将消息显示到文本框
            QObject::connect(tcpClient_, &TcpClient::signal_tcpClient, mainWindow_, &MainWindow::slot_send_textEdit);
            // 也就是说，如果发送到消息，交给TcpClient::slot_write 将消息发送出去
            QObject::connect(mainWindow_, &MainWindow::signal_tcpClientSend, tcpClient_, &TcpClient::slot_write);
        }
        else
        {
            QVariantMap data;
            data["type"] = "tcpClient";
            data["data"] = "tcpClient 连接失败！";
            data["status"] = false;
            emit signal_tips(data);
        }
        
        // QMetaObject::invokeMethod(mySerial_, "start", Qt::QueuedConnection);
    }
    else
    {
        LOG(INFO) << "SerialNetTools-tcpClient -> stop()";
        QMetaObject::invokeMethod(tcpClient_, "stop", Qt::QueuedConnection);
        
    }
}

/**
 * TCPServer 开关逻辑
 */
void SerialNetTools::switch_tcpServer(const QVariantMap &msg)
{
    LOG(INFO) << "SerialNetTools ---------> switch_tcpServer";
    bool state = msg.value("switch").toBool();

    if (state == true)
    {
        string ip = msg.value("ip").toString().toStdString();
        int port = msg.value("port").toInt();

        tcpServer_ = new TcpServer();
        LOG(INFO) << "SerialNetTools-tcpServer -> tcpServer_("<<ip<<","<<port<<")";
        tcpServer_->init(ip, port);

        // slot_mod_status 是一个串口和TCP模块公用的处理函数
        QObject::connect(tcpServer_, &TcpServer::signal_openStatus, mainWindow_, &MainWindow::slot_mod_status);
        bool res = tcpServer_->start();
        if (res)
        {
            LOG(INFO) << "SerialNetTools ---------> switch_tcpServer";
            // 如果连接成功，绑定signal_tcpServer 到 slot_send_textEdit
            // 也就是说，如果接收到消息，将消息显示到文本框
            QObject::connect(tcpServer_, &TcpServer::signal_tcpServer, mainWindow_, &MainWindow::slot_send_textEdit);
            // 也就是说，如果发送到消息，交给TcpServer::slot_write 将消息发送出去
            // 在 MainWindow 中添加对应的signal函数 
            QObject::connect(mainWindow_, &MainWindow::signal_tcpServerSend, tcpServer_, &TcpServer::slot_write);
        }
        else
        {
            QVariantMap data;
            data["type"] = "tcpServer";
            data["data"] = "tcpServer 连接失败！";
            data["status"] = false;
            emit signal_tips(data);
        }
        
        // QMetaObject::invokeMethod(mySerial_, "start", Qt::QueuedConnection);
    }
    else
    {
        LOG(INFO) << "SerialNetTools-tcpServer -> stop()";
        QMetaObject::invokeMethod(tcpServer_, "stop", Qt::QueuedConnection);
        
    }
}

/**
 * 串口开关逻辑
 */
void SerialNetTools::switch_mySerial(const QVariantMap &msg)
{
    LOG(INFO) << "SerialNetTools ---------> switch_mySerial";
    bool state = msg.value("switch").toBool();

    if (state == true)
    {
        string serialName = msg.value("serialName").toString().toStdString();
        int baudRate = msg.value("baudRate").toInt();
        int checkBit = msg.value("checkBit").toInt();
        int dataBit = msg.value("dataBit").toInt();
        int stopBit = msg.value("stopBit").toInt();

        mySerial_->init("1", serialName, baudRate, checkBit, dataBit, stopBit);
        QMetaObject::invokeMethod(mySerial_, "start", Qt::QueuedConnection);
    }
    else
    {
        LOG(INFO) << "mySerial_->stop()";
        QMetaObject::invokeMethod(mySerial_, "stop", Qt::QueuedConnection);
    }
}

/**
 * 各个模块的开关
 */
void SerialNetTools::slot_switch(const QVariantMap &msg)
{
    if (!msg.contains("type") && !msg.contains("state"))
    {
        return;
    }

    // 名字解析出来，然后用HashMap去找
    // 通过Hash表绑定函数 type: mySerial myTcp ...
    // 比如：Hash 函数表绑定 mySerial 绑定到 switch_mySerial()函数
    QString type = msg.value("type").toString();
    switchMap_[type](msg);
}