#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
// #include "rosNode.h"
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
    void slot_btn_send();
    void slot_send_textEdit(const QString&);

signals:
    void signal_send(const QString&);
    void signal_rosPub(const QString&);

private:
    Ui::MainWindow *ui_;
    // RosNode rosNode_;
    Common common_log_;
    MyLog *myLog_;
};
#endif // MAINWINDOW_H
