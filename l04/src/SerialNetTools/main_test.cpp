#include <iostream>
#include "serialNetTools.h"

int main(int argc, char** argv)
{
    SerialNetTools mySerialNetTools;
    int res = mySerialNetTools.myAdd(2, 3);

    std::cout<<"The result is: "<< res << std::endl;

    return 0;
}