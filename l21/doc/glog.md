# 安装glog

git clone --depth=1 https://github.com/google/glog

```s
cd glog
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig`
```

报错： cmake版本过低

CMake 3.22 or higher is required.  You are running version 3.16.3

A:
sudo wget -E https.proxy=192.168.3.8:7890 https://cmake.org/files/v3.23/cmake-3.23.0.tar.gz
sudo tar -zxvf cmake-3.23.0.tar.gz
cd cmake-3.23.0
./configurre
sudo make
sudo make install

#include <glog/logging.h>

Q:
/usr/local/include/glog/logging.h:60:4: error: #error <glog/logging.h> was not included correctly. See the documentation for how to consume the library.
A: 添加-DGLOG_USE_GLOG_EXPORT预定义
add_definitions(-DGLOG_USE_GLOG_EXPORT)