# gbd 调试

gdb ./serialNetTools_test
-c
run
bt
quit

手册

## 封装日志

安装glog
git clone --depth=1 https://github.com/google/glog

```s
cd glog
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig`
```

#include <glog/logging.h>