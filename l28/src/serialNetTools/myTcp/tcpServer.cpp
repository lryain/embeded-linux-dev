#include "tcpServer.h"

/**
 * 构造函数
 */
TcpServer::TcpServer()
{
}

void TcpServer::init(const string &ip, const int &port)
{
    ip_ = ip;
    port_ = port;
}

TcpServer::~TcpServer()
{
    stop();
}

/**
 * 尝试连接服务器
 */
bool TcpServer::start()
{
    LOG(INFO) << "TcpServer ---> TcpServer::start()!";

    stop();

    tcpServer_ = new QTcpServer();

    if (tcpServer_->listen(QHostAddress::Any, port_))
    {
        LOG(INFO) << "TcpServer ---> listen ok!";
        QVariantMap stateMap;
        stateMap["type"] = "TcpServer";
        stateMap["state"] = true;
        emit signal_openStatus(stateMap);
    }
    else
    {
        LOG(INFO) << "TcpServer ---> listen failed!";
        QVariantMap stateMap;
        stateMap["type"] = "TcpServer";
        stateMap["state"] = false;
        emit signal_openStatus(stateMap);
        return false;
    }

    // 初始化套接字
    tcpSocket_ = new QTcpSocket(this);

    // 当有客户端连接时
    // 信号连接 1. connected -> isConnected_ = true 2. readyRead -> slot_read
    connect(tcpServer_, &QTcpServer::newConnection, [=]
            {
        tcpSocket_ = tcpServer_->nextPendingConnection();
        connect(tcpSocket_, &QTcpSocket::readyRead, this, &TcpServer::slot_read); });
    // 客户端断开连接时
    connect(tcpSocket_, &QTcpSocket::disconnected, [=]
            { stop(); });
}

/**
 * 关闭连接
 */
void TcpServer::stop()
{
    if (tcpSocket_ != nullptr)
    {
        tcpSocket_->close();
        tcpSocket_->disconnect();
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }
    if (tcpServer_ != nullptr)
    {
        tcpServer_->close();
        tcpServer_->disconnect();
        delete tcpServer_;
        tcpServer_ = nullptr;
    }
}

/**
 * 读取TCP数据
 */
void TcpServer::slot_read()
{
    rec_buffer_.clear();
    if (tcpSocket_->bytesAvailable() > 0)
    {
        rec_buffer_ = tcpSocket_->readAll();

        LOG(INFO) << "TCP Server --> RX msg: " << QString::fromUtf8(rec_buffer_).toStdString();

        QVariantMap data;
        data["type"] = "TcpServer";
        data["data"] = rec_buffer_;
        emit signal_TcpServer(data);
    }
}

/**
 * 对外接口 通过服务器发送TCP数据的 槽
 */
void TcpServer::slot_write(const QString &msg)
{
    LOG(INFO) << "TCP Server --> TX msg: " << msg.toUtf8().toStdString();

    QByteArray data = msg.toUtf8();
    write(data);
}

/**
 * 发送TCP数据函数
 */
void TcpServer::write(const QByteArray &msg)
{
    if (tcpSocket_->state() == QAbstractSocket::ConnectedState && tcpSocket_ != nullptr && tcpServer_ != nullptr)
    {
        // tcpSocket_->write(msg);
        tcpSocket_->write(msg.toHex());
    }
}

/**
 * 连接服务器 信号槽
 */
void TcpServer::slot_start()
{
    start();
}