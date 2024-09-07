#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , rosNode_(argc, argv)
{
    ui_->setupUi(this);

    // 绑定信号到控件
    QObject::connect(ui_->pushButton_send, &QPushButton::clicked, this, &MainWindow::slot_btn_send);
    QObject::connect(this, &MainWindow::signal_send, this, &MainWindow::slot_send_textEdit);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::slot_btn_send(){
    QString send_msg = ui_->lineEdit_input->text();
    qDebug() << ui_->lineEdit_input->text();
    emit signal_send(send_msg);
    ui_->lineEdit_input->clear();
}

/**
 * 槽函数
 */
void MainWindow::slot_send_textEdit(const QString& msg){
    ui_->textEdit_sub->append(msg);
}