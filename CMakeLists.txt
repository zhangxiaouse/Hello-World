cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(COMMON_SOURCES
    utils/printer.cpp
    utils/file/file_handler.cpp
    utils/text/text_processor.cpp
    utils/network/tcp_connection.cpp
)

# Add header directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Main program
add_executable(HelloWorld main.cpp ${COMMON_SOURCES})

# TCP server example
add_executable(TcpServer utils/examples/tcp_server_example.cpp ${COMMON_SOURCES})

# TCP client example
add_executable(TcpClient utils/examples/tcp_client_example.cpp ${COMMON_SOURCES})

# Add dirent.h support for macOS
if(APPLE)
    target_compile_options(HelloWorld PRIVATE -std=c++17)
    target_compile_options(TcpServer PRIVATE -std=c++17)
    target_compile_options(TcpClient PRIVATE -std=c++17)
endif() 