project(serialNetTools)

# Header files 由于qt工程的特殊性，这个还是要加上 才能找到ui_mainwindow.h头文件 否则报错：fatal error: ./ui_mainwindow.h: 没有那个文件或目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 导入QT5库
find_package(Qt5 COMPONENTS Widgets Network Concurrent Core REQUIRED)

# 导入ROS1库
find_package(catkin REQUIRED COMPONENTS
            roscpp
            rospy
            std_msgs
            sensor_msgs
            )
# # 导入ROS1头文件
include_directories(${catkin_INCLUDE_DIRS})
# message(STATUS "{catkin_INCLUDE_DIRS} : ${catkin_INCLUDE_DIRS}")

#************************
# 添加源文件
#************************
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h)
set(QT_SOURCES serialNetTools.cpp)

#三个用于处理Qt特定资源和代码生成的命令
# QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) #从 .ui 文件自动生成用户界面类的头文件和源文件
# QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})#将 .qrc 资源文件转换成可编译的C++源文件
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #.h 文件（包含Qt对象的头文件）自动生成moc（元对象编译器）文件，这些文件是Qt信号和槽机制所必需的

#*************************
# 生成动态链接库
#************************
add_library(${PROJECT_NAME} SHARED  ${QT_SOURCES} 
                                    ${QT_MOC_HPP})
                                    
add_definitions(-DGLOG_USE_GLOG_EXPORT)

# 需要链接的库
target_link_libraries(${PROJECT_NAME} 
                        Qt5::Widgets
                        Qt5::Core
                        Qt5::Network
                        Qt5::Concurrent
                        qt_ui
                        mySerial
                        myTcp
                        rosNode
                        # ${catkin_LIBRARIES} 
                        # common
                        )

# 可执行文件，不适用库
add_executable(${PROJECT_NAME}_test main.cpp)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
