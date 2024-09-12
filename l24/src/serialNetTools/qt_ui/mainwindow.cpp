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

    // 串口
    QObject::connect(ui_->pushButton_serial_open, &QPushButton::clicked, this, &MainWindow::slot_btn_mySerial_open);
    QObject::connect(ui_->pushButton_serial_send, &QPushButton::clicked, this, &MainWindow::slot_btn_mySerial_send);

    // 获取串口列表
    QList<QSerialPortInfo> serialNams = QSerialPortInfo::availablePorts();
    foreach(const QSerialPortInfo &info, serialNams)
    {
        ui_->comboBox_serialName->addItem("/dev/"+info.portName());
    }

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
    }else{
        data["switch"] = false;
        ui_->pushButton_serial_open->setText("打开");
        ui_->pushButton_serial_open->setStyleSheet("background-color: {}");
    }
    // ui_->pushButton_serial_open->setEnabled(false);
    emit signal_switch(data);
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
 */
void MainWindow::slot_mod_status(const QVariantMap& msg){
    if(!msg.contains("type")&&!msg.contains("state"))
    {
        return;
    }

    QString type = msg.value("type").toString();
    bool state = msg.value("state").toBool();

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
        }else{
            // LOG(INFO)<<"串口打开成功！";
            // ui_->pushButton_serial_open->setText("关闭");
            // ui_->pushButton_serial_open->setStyleSheet("background-color: {}");

            // QDateTime now = QDateTime::currentDateTime();
            // QString str = addTimeStr("mySerial");
            // str += "串口打开失败！";
            // ui_->textEdit_sub->append(str);
            // ui_->pushButton_serial_open->setEnabled(true);
        }
    }
}

/**
 * UI 汇总显示 接收
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