cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
set(SOURCES
    main.cpp
    utils/printer.cpp
)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 生成可执行文件
add_executable(HelloWorld ${SOURCES}) 