project(serialNetTools)

# message(STATUS "project_name = ${PROJECT_NAME}")

# Header files
# set(CMAKE_INCLUDE_CURRENT_DIR_ON)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 动态链接库
add_library(${PROJECT_NAME} SHARED serialNetTools.cpp)
# 静态链接库
# add_library(${PROJECT_NAME}_static serialNetTools.cpp)

# 可执行文件，不适用库
# add_executable(${PROJECT_NAME}_test main_test.cpp serialNetTools.cpp)
add_executable(${PROJECT_NAME}_test main_test.cpp)

# 使用动态库
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
# 使用静态库
# target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_static)