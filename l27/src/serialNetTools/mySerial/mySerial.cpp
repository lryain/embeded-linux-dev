#include "mySerial.h"

/**
 * 构造函数
 */
MySerial::MySerial()
{
}

void MySerial::init(const string &groupID, const string &serialName, const int &baudRate,
                    const int &checkBit, const int &dataBit, const int &stopBit)
{
    groupID_ = groupID;
    serialName_ = serialName;
    baudRate_ = baudRate;
    checkBit_ = checkBit;
    dataBit_ = dataBit;
    stopBit_ = stopBit;
}

MySerial::~MySerial()
{
}

/**
 * 尝试开启串口
 */
bool MySerial::start()
{
    LOG(INFO)<<"mySerial ---> MySerial::start()!";
    if (serialPort_ != nullptr)
    {
        serialPort_->flush(); // 清空缓冲区
        serialPort_->close();
        delete serialPort_;
        serialPort_ = nullptr;
    }

    serialPort_ = new QSerialPort();
    serialPort_->setPortName(QString::fromStdString(serialName_));
    serialPort_->setBaudRate(baudRate_);
    switch (checkBit_)
    {
    case 0:
        serialPort_->setParity(QSerialPort::NoParity);
        break;
    case 2:
        serialPort_->setParity(QSerialPort::EvenParity);
        break;
    case 3:
        serialPort_->setParity(QSerialPort::OddParity);
        break;
    case 4:
        serialPort_->setParity(QSerialPort::SpaceParity);
        break;
    case 5:
        serialPort_->setParity(QSerialPort::MarkParity);
        break;
    case -1:
        serialPort_->setParity(QSerialPort::UnknownParity);
        break;
    default:
        break;
    }
    // 设置数据位
    switch (dataBit_)
    {
    case 5:
        serialPort_->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        serialPort_->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        serialPort_->setDataBits(QSerialPort::Data7);
        break;
    case 8:
        serialPort_->setDataBits(QSerialPort::Data8);
        break;
    case -1:
        serialPort_->setDataBits(QSerialPort::UnknownDataBits);
        break;
    default:
        break;
    }
    // 设置停止位
    switch (stopBit_)
    {
    case 1:
        serialPort_->setStopBits(QSerialPort::OneStop);
        break;
    case 2:
        serialPort_->setStopBits(QSerialPort::TwoStop);
        break;
    case 3:
        serialPort_->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case -1:
        serialPort_->setStopBits(QSerialPort::UnknownStopBits);
        break;
    default:
        break;
    }
    // 设置控制流
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    // 打开串口
    bool open_state = serialPort_->open(QIODevice::ReadWrite);

    // 发送打开状态用的数据结构
    QVariantMap stateMap;
    if (open_state)
    {
        // 建立串口数据的连接 当串口读准备好，调用slot_read读取
        QObject::connect(serialPort_, &QSerialPort::readyRead, this, &MySerial::slot_read);
        stateMap["type"] = "mySerial";
        stateMap["state"] = "true";
        emit signal_openStatus(stateMap);
        LOG(INFO)<<"mySerial ---> Serial port open ok!";
        return true;
    }
    else
    {
        stop();
        stateMap["type"] = "mySerial";
        stateMap["state"] = "false";
        emit signal_openStatus(stateMap);
        LOG(INFO)<<"mySerial ---> Serial port open failed!! ";
        return false;
    }
}

/**
 * 关闭串口
 */
void MySerial::stop()
{
    if (serialPort_ != nullptr)
    {
        serialPort_->flush(); // 清空缓冲区
        serialPort_->close();
        delete serialPort_;
        serialPort_ = nullptr;
    }
}

/**
 * 读取数据
 */
void MySerial::slot_read()
{
    if (serialPort_->bytesAvailable() > 0)
    {
        QByteArray serial_data;
        serial_data = serialPort_->readAll();

        LOG(INFO) << "serial_data: " << QString::fromUtf8(serial_data).toStdString();

        QVariantMap data;
        data["type"] = "mySerial";
        data["data"] = serial_data;
        emit signal_serial(data);
    }
}

/**
 * 写入串口数据
 */
void MySerial::slot_write(const QString &msg)
{
    if (serialPort_ != nullptr)
    {
        QByteArray data = msg.toUtf8();
        serialPort_->write(data);
    }
}

/**
 * 开启串口
 */
void MySerial::slot_start()
{
    start();
}