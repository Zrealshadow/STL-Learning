# 指定Version
cmake_minimum_required(VERSION 3.0.0)
# 指定test中需要的头文件目录
include_directories(include)

#选取所有的文件
FILE(GLOB_RECURSE CURRENT_INCLUDE include/*.h)
FILE(GLOB_RECURSE CURRENT_SOURCES *.cpp)

# message(${CURRENT_INCLUDE})
# message(${CURRENT_SOURCES})

#如果有可执行文件， 构建一个可执行文件  一般会有一个main.cpp 保证其中已有一个main函数
add_executable(STLTest ${CURRENT_SOURCES} ${CURRENT_INCLUDE})

# 注： 在这一层CMakeList也可以不构建可执行程序或者Lib， 可以在上一层Cmakelits中进行构建
# src下的CMake只用来检索文件