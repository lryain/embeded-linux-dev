# manual

## gbd 调试

gdb ./serialNetTools_test
-c
run
bt
quit

## 配置git

git config --global http.proxy http://192.168.3.8:7890
git config --global https.proxy http://192.168.3.8:7890
git config --global user.name "lryain"
git config --global user.email "47129927@qq.com"

## ENV

change language to chinese



## ros 测试

roscore
rostopic pub /str_msg std_msgs/String "data: 'hello-ros'"
rostopic echo /str_msg


