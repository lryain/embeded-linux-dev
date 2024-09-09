project(myLogTest)

# Header files
set(CMAKE_INCLUDE_CURRENT_DIR_ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 添加库路径
# set(CMAKE_MODULE_PATH ${MY_CMAKE_INSTALL_DIRECTORY})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../install) # 相对路径
message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# 查找QtUi库
find_package(QtUi REQUIRED)

# 添加库的头文件
set(QtUi_INCLUDE_DIRS ${CMAKE_MODULE_PATH}/include ${QtUi_INCLUDE_DIRS})
message(STATUS "QtUi_INCLUDE_DIRS: " ${QtUi_INCLUDE_DIRS})
include_directories(${QtUi_INCLUDE_DIRS})

# 可执行文件，不适用库
add_executable(${PROJECT_NAME} main.cpp)

# 动态链接库
# add_library(${PROJECT_NAME} SHARED common.cpp myLog.cpp)
target_link_libraries(${PROJECT_NAME} common)
