// #ifndef SERIALNETTOOLS_H
// #define SERIALNETTOOLS_H
#pragma once

#include <iostream>
#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QVariantMap>
#include <QList>
#include <QHash>
#include "mySerial.h"
#include "mainwindow.h"
#include <QApplication>

using namespace std;


class SerialNetTools : public QObject
{

Q_OBJECT

public:
     SerialNetTools(int argc, char** argv);
    ~ SerialNetTools();
    int init();

public slots:
    void slot_switch(const QVariantMap&);

private:
    // 解析和分发逻辑
    void switch_mySerial(const QVariantMap&);

private:
    int argc_;
    char** argv_;
    // 用QHash来作绑定 来简化if else语句
    QHash<QString, std::function<void(const QVariantMap&)>> switchMap_;

    MySerial *mySerial_ = nullptr;
    MainWindow * mainWindow_ = nullptr;
    QApplication *app_ = nullptr;
    QThread *mySerial_thread_ = nullptr;

};





// #endif