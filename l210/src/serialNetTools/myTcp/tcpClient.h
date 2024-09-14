#pragma once

#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <qtimer.h>
#include <QVariantMap>
#include "myLog.h"

using namespace std;

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();

    void init(const string& groupID, const string& ip, const int& port);

    Q_INVOKABLE void stop();
    Q_INVOKABLE bool start();

private:
    void write(const QByteArray& msg);

public slots:
    void slot_write(const QString& msg);
    void slot_start();

private slots:
    void slot_read();

signals:
    void signal_openStatus(const QVariantMap& msg); // 是否成功打開
    void signal_tcpClient(const QVariantMap& msg);  // 接收到TCP消息

private:
    string groupID_;
    string ip_ = "127.0.0.1";
    int port_ = 9002;
    
    QTcpSocket *tcpSocket_ = nullptr;
    bool isConnected_ = false;
    QByteArray rec_buffer_;
};
