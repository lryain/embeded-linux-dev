#pragma once

#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <QVariantMap>
#include "myLog.h"

using namespace std;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer();
    ~TcpServer();

    void init(const string& ip, const int& port);

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
    void signal_TcpServer(const QVariantMap& msg);  // 接收到TCP消息

private:
    string groupID_;
    string ip_ = "127.0.0.1";
    int port_ = 9002;
    
    QTcpSocket *tcpSocket_ = nullptr;
    QTcpServer *tcpServer_ = nullptr;
    // bool isConnected_ = false;
    QByteArray rec_buffer_;
};
