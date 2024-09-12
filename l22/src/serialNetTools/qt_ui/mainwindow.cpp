#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    // , rosNode_(argc, argv)
{
    ui_->setupUi(this);
    // 初始化ros
    // rosNode_.init();
    // 绑定信号到控件
    QObject::connect(ui_->pushButton_serial_send, &QPushButton::clicked, this, &MainWindow::slot_btn_send);
    QObject::connect(this, &MainWindow::signal_send, this, &MainWindow::slot_send_textEdit);

    // 将QT窗体消息 绑定到Ros节点，然后发布出去
    // QObject::connect(this, &MainWindow::signal_rosPub, &rosNode_, &RosNode::slot_pubStrMsg);
    // 将ros收到的消息绑定到QT窗口
    // QObject::connect(&rosNode_, &RosNode::signal_strMsg, this, &MainWindow::slot_send_textEdit);

    // 日志
    std::string log_path = common_log_.get_log_path();
    myLog_ = new MyLog(log_path, "mainWindow");
    LOG(INFO)<<"mainWindow --> Log Hello World!";
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete myLog_;
}

void MainWindow::slot_btn_send(){
    QString send_msg = ui_->lineEdit_serial_input->text();
    qDebug() << send_msg;
    emit signal_send(send_msg);
    emit signal_rosPub(send_msg);
    ui_->lineEdit_serial_input->clear();
}

/**
 * 槽函数
 */
void MainWindow::slot_send_textEdit(const QString& msg){
    ui_->textEdit_sub->append(msg);
}