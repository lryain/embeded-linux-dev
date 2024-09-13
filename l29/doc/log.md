
# log

## 在qt_ui模块导入日志模块

在CMakeLists.txt文件中添加
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)
# 需要链接的库
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${catkin_LIBRARIES} common)

