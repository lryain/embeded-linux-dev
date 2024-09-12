#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QVariantMap>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "common.h"
#include "myLog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slot_send_textEdit(const QVariantMap&);
    // 按钮发送
    void slot_btn_mySerial_send();
    // 开关按钮
    void slot_btn_mySerial_open();
    // 功能模块是否打开成功
    void slot_mod_status(const QVariantMap&);
    // 串口列表刷新
    void slot_btn_mySerial_reload();

signals:
    // UI发送串口数据
    void signal_serialSend(const QString&);
    // 开关
    void signal_switch(const QVariantMap&);

    // void signal_send(const QString&);
    // void signal_rosPub(const QString&);

private:
    Ui::MainWindow *ui_;
    QString addTimeStr(const QString& msg);
    // RosNode rosNode_;
    // Common common_log_;
    // MyLog *myLog_;
};
#endif // MAINWINDOW_H
