#pragma once

#include <QString>
#include <QObject>
#include <QVariantMap>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "myLog.h"

using namespace std;

class MySerial : public QObject
{
    Q_OBJECT
private:
    string groupID_;
    string serialName_ = "COM1";
    int baudRate_ = 115200;
    int checkBit_ = 0;
    int dataBit_ = 8;
    int stopBit_ = 1;
    
    QSerialPort *serialPort_ = nullptr;

public:
    MySerial();
    ~MySerial();
    Q_INVOKABLE bool start();
    Q_INVOKABLE void stop();
    void init(const string& groupID, const string& serialName, const int& baudReate, const int& checkData, const int& dataBit, const int& stopBit);

public slots:
    void slot_read();
    void slot_write(const QString& msg);
    void slot_start();

signals:
    void signal_serial(const QVariantMap& msg);
    void signal_openStatus(const QVariantMap& msg);

};

