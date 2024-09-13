#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // std::string log_path = common_log_.get_log_path();
    // myLog_ = new MyLog(log_path, "mainWindow");
    // LOG(INFO)<<"mainWindow --> Log Hello World!";

    // 串口界面按钮信号绑定 1. 打开 2. 发送 3. 刷新
    QObject::connect(ui_->pushButton_serial_open, &QPushButton::clicked, this, &MainWindow::slot_btn_mySerial_open);
    QObject::connect(ui_->pushButton_serial_send, &QPushButton::clicked, this, &MainWindow::slot_btn_mySerial_send);
    QObject::connect(ui_->pushButton_serial_reload, &QPushButton::clicked, this, &MainWindow::slot_btn_mySerial_reload);

    // 获取串口列表
    ui_->comboBox_serialName->clear();
    QList<QSerialPortInfo> serialNams = QSerialPortInfo::availablePorts();
    foreach(const QSerialPortInfo &info, serialNams)
    {
        ui_->comboBox_serialName->addItem("/dev/"+info.portName());
    }

    // TCP客户端界面 绑定 打开，发送按钮处理 槽函数
    QObject::connect(ui_->pushButton_tcpClient_open, &QPushButton::clicked, this, &MainWindow::slot_btn_tcpClient_open);
    QObject::connect(ui_->pushButton_tcpClient_send, &QPushButton::clicked, this, &MainWindow::slot_btn_tcpClient_send);

    // TCP服务器界面 绑定 打开，发送按钮处理 槽函数
    QObject::connect(ui_->pushButton_tcpServer_open, &QPushButton::clicked, this, &MainWindow::slot_btn_tcpServer_open);
    QObject::connect(ui_->pushButton_tcpServer_send, &QPushButton::clicked, this, &MainWindow::slot_btn_tcpServer_send);

}

MainWindow::~MainWindow()
{
    delete ui_;
    // delete myLog_;
}

/**
 * 串口发送数据按钮
 */
void MainWindow::slot_btn_mySerial_send(){
    QString send_msg = ui_->lineEdit_serial_input->text();
    // qDebug() << send_msg;
    emit signal_serialSend(send_msg);
    // 清空发送文本框
    // ui_->lineEdit_serial_input->clear();

    // 在发送页面展示
    QString str = addTimeStr("mySerial");
    str += send_msg;
    ui_->textEdit_send->append(str);

}

/**
 * 串口列表刷新
 */
void MainWindow::slot_btn_mySerial_reload(){
    ui_->comboBox_serialName->clear();
    // 获取串口列表
    QList<QSerialPortInfo> serialNames = QSerialPortInfo::availablePorts();
    foreach(const QSerialPortInfo& info, serialNames)
    {
        ui_->comboBox_serialName->addItem("/dev/"+info.portName());
    }

}

/**
 * TCPClient发送数据按钮
 */
void MainWindow::slot_btn_tcpClient_send(){
    QString send_msg = ui_->lineEdit_tcpClient_input->text();
    // qDebug() << send_msg;
    emit signal_tcpClientSend(send_msg);
    // 清空发送文本框
    // ui_->lineEdit_serial_input->clear();

    // 在发送页面展示
    QString str = addTimeStr("tcpClient");
    str += send_msg;
    ui_->textEdit_send->append(str);
}

/**
 * TCPServer发送数据按钮
 */
void MainWindow::slot_btn_tcpServer_send(){
    QString send_msg = ui_->lineEdit_tcpServer_input->text();
    // qDebug() << send_msg;
    emit signal_tcpServerSend(send_msg);
    // 清空发送文本框
    // ui_->lineEdit_serial_input->clear();

    // 在发送页面展示
    QString str = addTimeStr("tcpServer");
    str += send_msg;
    ui_->textEdit_send->append(str);
}

/**
 * TCPClient 开关按钮 槽
 */
void MainWindow::slot_btn_tcpClient_open(){
    QString ip = ui_->lineEdit_tcpClient_ip->text();
    int port = ui_->lineEdit_tcpClient_port->text().toInt();
    
    QVariantMap data;
    data["type"] = "tcpClient";
    data["ip"] = ip;
    data["port"] = port;

    if(ui_->pushButton_tcpClient_open->text()=="打开")
    {
        data["switch"] = true;
        ui_->pushButton_tcpClient_open->setText("关闭");
        ui_->pushButton_tcpClient_open->setStyleSheet("background-color: green");
        // ui_->pushButton_tcpClient_open->setEnabled(false);
    }else{
        data["switch"] = false;
        ui_->pushButton_tcpClient_open->setText("打开");
        ui_->pushButton_tcpClient_open->setStyleSheet("background-color: {}");
    }
    emit signal_switch(data);
}


/**
 * TCPServer 开关按钮 槽
 */
void MainWindow::slot_btn_tcpServer_open(){
    LOG(INFO) << "!! slot_btn_tcpServer_open !!";
    QString ip = ui_->lineEdit_tcpServer_ip->text();
    int port = ui_->lineEdit_tcpServer_port->text().toInt();
    
    QVariantMap data;
    data["type"] = "tcpServer";
    data["ip"] = ip;
    data["port"] = port;

    if(ui_->pushButton_tcpServer_open->text()=="打开")
    {
        data["switch"] = true;
        ui_->pushButton_tcpServer_open->setText("关闭");
        ui_->pushButton_tcpServer_open->setStyleSheet("background-color: green");
        // ui_->pushButton_tcpServer_open->setEnabled(false);
    }else{
        data["switch"] = false;
        ui_->pushButton_tcpServer_open->setText("打开");
        ui_->pushButton_tcpServer_open->setStyleSheet("background-color: {}");
    }
    LOG(INFO) << "!! emit signal_switch with data: ip: "<<ip.toStdString()<<" port: "<<port;
    emit signal_switch(data);
}

/**
 * 串口开关按钮 槽
 */
void MainWindow::slot_btn_mySerial_open(){
    QString serialName = ui_->comboBox_serialName->currentText();
    int baudRate = ui_->comboBox_baudRate->currentText().toInt();
    int dataBit = ui_->comboBox_dataBit->currentText().toInt();
    int stopBit = ui_->comboBox_stopBit->currentText().toInt();
    QString checkBitStr = ui_->comboBox_checkBit->currentText();
    int checkBit = -1;
    if (checkBitStr == "NoParity")
    {
        checkBit = 0;
    }
    else if (checkBitStr == "EvenParity")
    {
        checkBit = 2;
    }
    else if (checkBitStr == "OddParity")
    {
        checkBit = 3;
    }
    else if (checkBitStr == "SpaceParity")
    {
        checkBit = 4;
    }
    else if (checkBitStr == "MarkParity")
    {
        checkBit = 5;
    }
    else
    {
        checkBit = -1;
    }
    
    QVariantMap data;
    data["type"] = "mySerial";
    data["serialName"] = serialName;
    data["baudRate"] = baudRate;
    data["checkBit"] = checkBit;
    data["dataBit"] = dataBit;
    data["stopBit"] = stopBit;

    if(ui_->pushButton_serial_open->text()=="打开")
    {
        data["switch"] = true;
        ui_->pushButton_serial_open->setText("关闭");
        ui_->pushButton_serial_open->setStyleSheet("background-color: green");
        // ui_->pushButton_serial_open->setEnabled(false);
    }else{
        data["switch"] = false;
        ui_->pushButton_serial_open->setText("打开");
        ui_->pushButton_serial_open->setStyleSheet("background-color: {}");
    }
    emit signal_switch(data);

    // 获取串口列表
    ui_->comboBox_serialName->clear();
    QList<QSerialPortInfo> serialNams = QSerialPortInfo::availablePorts();
    foreach(const QSerialPortInfo &info, serialNams)
    {
        ui_->comboBox_serialName->addItem("/dev/"+info.portName());
    }
}

// 时间戳函数
QString MainWindow::addTimeStr(const QString& msg){
    QDateTime now = QDateTime::currentDateTime();
    QString str = now.toString("hh:mm:ss.zzzzzz");
    str += (" "+msg+": ");
    return str;
}

/**
 * 各个模块的状态返回
 * 串口，TCP客户端，服务器端
 */
void MainWindow::slot_mod_status(const QVariantMap& msg){
    LOG(INFO)<<"!! slot_mod_status ------------>";
    if(!msg.contains("type")||!msg.contains("state"))
    {
        LOG(INFO)<<"missing type or state!";
        return;
    }

    QString type = msg.value("type").toString();
    bool state = msg.value("state").toBool();
    LOG(INFO)<<"slot_mod_status ------------> type: ["<< type.toStdString() << "] state: "<<state;

    if(type == "mySerial")
    {
        if(!state){
            LOG(INFO)<<"串口打开失败！";
            ui_->pushButton_serial_open->setText("关闭");
            ui_->pushButton_serial_open->setStyleSheet("background-color: {}");

            QDateTime now = QDateTime::currentDateTime();
            QString str = addTimeStr("mySerial");
            str += "串口打开失败！";
            ui_->textEdit_sub->append(str);
            ui_->pushButton_serial_open->setEnabled(true);
        }
    }
    else if(type == "tcpClient")
    {
        if(!state){
            LOG(INFO)<<"tcpClient 打开失败！";
            QVariantMap data;
            data["type"] = "tcpClient";
            data["switch"] = false;
            ui_->pushButton_tcpClient_open->setText("关闭");
            ui_->pushButton_tcpClient_open->setStyleSheet("background-color: {}");
            emit signal_switch(data);
        }
    }
    else if(type == "tcpServer")
    {
        LOG(INFO)<<"the type is tcpServer and the state: "<<state;
        
        if(!state){
            LOG(INFO)<<"tcpServer 打开失败！";
            QVariantMap data;
            data["type"] = "tcpServer";
            data["switch"] = false;
            ui_->pushButton_tcpServer_open->setText("关闭");
            ui_->pushButton_tcpServer_open->setStyleSheet("background-color: {}");
            emit signal_switch(data);
        }
    }
    LOG(INFO)<<"slot_mod_status ------------> done!";

}

/**
 * UI 汇总显示 接收
 * 显示到文本框
 */
void MainWindow::slot_send_textEdit(const QVariantMap& msg){
    if(!msg.contains("type")&&!msg.contains("state"))
    {
        return;
    }

    QString type = msg.value("type").toString();
    QString str = addTimeStr(type);
    str += msg.value("data").toString();
    ui_->textEdit_sub->append(str);
}