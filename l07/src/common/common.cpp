#include "common.h"

/**
 * 创建文件目录
 */
void Common::create_multilevel_dir(const char* dir){
    char command[100] = "mkdir -p ";
    strcat(command, dir);
    system(command);
}

string Common::get_cur_path(){
    char* cur_path;
    cur_path = getcwd(NULL, 0);
    string str_cur_path(cur_path, strlen(cur_path));
    return str_cur_path;
}

string Common::get_log_path(){
    string cur_path = get_cur_path();
    int index = cur_path.find_last_of('/');
    string log_path = cur_path.substr(0, index) + "/logs";
    if(access(log_path.c_str(), 0)){
        cout<<"---> log_path is not exit, create it ..."<<endl;
        create_multilevel_dir(log_path.c_str());
    }
    return log_path;
}

Common::Common(/* args */)
{
}

Common::~Common()
{
}