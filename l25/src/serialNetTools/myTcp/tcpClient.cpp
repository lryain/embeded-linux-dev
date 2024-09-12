#include "tcpClient.h"

/**
 * 构造函数
 */
TcpClient::TcpClient()
{
}

void TcpClient::init(const string &groupID, const string &ip, const int &port)
{
    groupID_ = groupID;
    ip_ = ip;
    port_ = port;
}

TcpClient::~TcpClient()
{
}

/**
 * 尝试连接服务器
 */
bool TcpClient::start()
{
    LOG(INFO)<<"TcpClient ---> TcpClient::start()!";
    if (tcpSocket_ != nullptr)
    {
        tcpSocket_->close();
        if(tcpSocket_->state() == QAbstractSocket::ConnectedState)
        {
            tcpSocket_->disconnectFromHost();
        }
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }

    // 初始化套接字
    tcpSocket_ = new QTcpSocket(this);

    // 信号连接 1. connected -> isConnected_ = true 2. readyRead -> slot_read
    connect(tcpSocket_, &QTcpSocket::connected, [=]{
        // isConnected_ = true;
        connect(tcpSocket_, &QTcpSocket::readyRead, this, &TcpClient::slot_read);
    });
    // 断开连接
    connect(tcpSocket_, &QAbstractSocket::disconnected, [=]{
        isConnected_= false;
    });

    // 套接字 连接
    tcpSocket_->connectToHost(QString::fromStdString(ip_), port_);

    if (tcpSocket_->waitForConnected(1000))
    {
        isConnected_ = true;
        QVariantMap stateMap;
        stateMap["type"] = "tcpClient";
        stateMap["state"] =  true;
        emit signal_openStatus(stateMap);
    }
    else
    {
        stop();
        isConnected_ = false;
        QVariantMap stateMap;
        stateMap["type"] = "tcpClient";
        stateMap["state"] =  false;
        emit signal_openStatus(stateMap);
    }
    
    
    return isConnected_;
}

/**
 * 关闭连接
 */
void TcpClient::stop()
{
    if (tcpSocket_ != nullptr)
    {
        tcpSocket_->close();
        if(tcpSocket_->state() == QAbstractSocket::ConnectedState){
            tcpSocket_->disconnectFromHost();
        }
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }
}

/**
 * 读取TCP数据
 */
void TcpClient::slot_read()
{
    rec_buffer_.clear();
    if (tcpSocket_->bytesAvailable() > 0)
    {
        rec_buffer_ = tcpSocket_->readAll();

        LOG(INFO) << "tcp_data: " << QString::fromUtf8(rec_buffer_).toStdString();

        QVariantMap data;
        data["type"] = "TcpClient";
        data["data"] = rec_buffer_;
        emit signal_tcpClient(data);
    }
}

/**
 * 发送TCP数据的 槽 对外
 */
void TcpClient::slot_write(const QString &msg)
{
    QByteArray data = msg.toUtf8();
    LOG(INFO) << "TCP->tx msg: " << msg.toUtf8().toStdString();
    if (tcpSocket_ != nullptr)
    {
        write(data);
    }
}


/**
 * 发送TCP数据函数
 */
void TcpClient::write(const QByteArray &msg)
{
    if (isConnected_ && tcpSocket_->state() == QAbstractSocket::ConnectedState && tcpSocket_ != nullptr)
    {
        tcpSocket_->write(msg.toHex());
    }
}

/**
 * 连接服务器 信号槽
 */
void TcpClient::slot_start()
{
    start();
}