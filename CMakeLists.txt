cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件
set(SOURCES
    main.cpp
    utils/printer.cpp
    utils/file/file_handler.cpp
    utils/text/text_processor.cpp
)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 生成可执行文件
add_executable(HelloWorld ${SOURCES})

# 在macOS上添加dirent.h支持
if(APPLE)
    target_compile_options(HelloWorld PRIVATE -std=c++17)
endif() 