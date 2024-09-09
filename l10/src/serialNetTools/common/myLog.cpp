#include "myLog.h"
#include <string>

MyLog::MyLog(const string& log_path, const string& log_file_name) : log_path_(log_path),log_file_name_(log_file_name)
{
//     FLAGS_alsologtostderr = true;               //设置日志消息除了日志文件之外还可显示到屏幕上
//     FLAGS_colorlogtostderr = true;              //设置记录到标准输出的颜色信息
//     FLAGS_log_prefix = true;                    //设置日志前缀是否应该添加到每行输出
//     FLAGS_logbufsecs = 0;                       //设置可以缓冲日志的最大秒数，0指实时输出
//     FLAGS_max_log_size = 20;                    //设置最大日志文件大小（以MB为单位），超过会对文件进行分割
//     FLAGS_stop_logging_if_full_disk = true;     //设置是否在磁盘已满时避免日志记录到磁盘
//     FLAGS_minloglevel = google::INFO;           //设置最小处理日志的等级
//     FLAGS_log_dir = log_path_;//设置日志文件的输出路径
// //    FLAGS_MAX_log_days = //旧版本还不支持
    std::string log_info = log_path_ + "/"+log_file_name_;
    google::SetLogDestination(google::GLOG_INFO,log_info.c_str());

    const char* log_argv = {" "};
    google::InitGoogleLogging(log_argv);//初始化日志系统false
}

MyLog::~MyLog()
{
    google::ShutdownGoogleLogging();
    cout<<"~ShutdownGoogleLogging"<<endl;
}