#include <iostream>
#include "common.h"
#include "myLog.h"
#include "serialNetTools.h"

using namespace std;

int main(int argc, char** argv)
{
    Common common;
    string log_path = common.get_log_path();
    MyLog *myLog = new MyLog(log_path, "serialNetTools");

    // MySerial 是一个QObject对象
    SerialNetTools serialNetTools(argc, argv);

    LOG(INFO)<<"serialNetTools main start.";
    int res = serialNetTools.init();

    delete myLog;

    return res;
}