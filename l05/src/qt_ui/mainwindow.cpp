#include "mainwindow.h"
#include "build/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
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
}

/**
 * 槽函数
 */
void MainWindow::slot_send_textEdit(const QString& msg){
    ui_->textEdit_sub->append(msg);
}