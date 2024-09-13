project(common)

# Header files
# set(CMAKE_INCLUDE_CURRENT_DIR_ON)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 查找glog库
find_package(glog REQUIRED)

# dynamic 动态链接库
# add_library(${PROJECT_NAME} SHARED serialNetTools.cpp)
add_library(${PROJECT_NAME} SHARED common.cpp myLog.cpp)
target_link_libraries(${PROJECT_NAME} glog::glog)

# 可执行文件，不适用库
# add_executable(${PROJECT_NAME}_test main_test.cpp serialNetTools.cpp)
add_executable(${PROJECT_NAME}_test main_common_test.cpp)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})