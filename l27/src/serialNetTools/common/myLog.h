#pragma once

#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <string>

using namespace std;

class MyLog
{
private:
    /* data */
    string log_path_;
    string log_file_name_;
public:
    MyLog(const string& log_path, const string& log_file_name);
    ~MyLog();
};

