# C++ Code Modularization and File Organization Example

This is a project demonstrating C++ code modularization and file organization, which showcases good code structure by separating different functionalities into independent modules.

## Project Structure

```
HelloWorld/
│
├── main.cpp                    # Main program entry
├── CMakeLists.txt              # CMake build configuration
│
└── utils/                      # Utility directory
    ├── printer.h               # Printing functionality header
    ├── printer.cpp             # Printing functionality implementation
    │
    ├── file/                   # File operation module
    │   ├── file_handler.h      # File handling header
    │   └── file_handler.cpp    # File handling implementation
    │
    ├── text/                   # Text processing module
    │   ├── text_processor.h    # Text processing header
    │   └── text_processor.cpp  # Text processing implementation
    │
    ├── network/                # Network module
    │   ├── tcp_connection.h    # TCP connection header
    │   └── tcp_connection.cpp  # TCP connection implementation
    │
    └── examples/               # Example programs
        ├── tcp_server_example.cpp # TCP server example
        └── tcp_client_example.cpp # TCP client example
```

## Functional Modules

### 1. Printing Module (utils/printer)
Provides basic message printing functionality, encapsulating standard output operations.

### 2. File Operation Module (utils/file)
Provides file reading/writing and directory operations, including:
- Reading file content
- Writing content to file
- Checking if file exists
- Listing files in a directory

### 3. Text Processing Module (utils/text)
Provides text processing functionality, including:
- Converting text case
- Splitting text
- Replacing text content
- Counting word frequency

### 4. Network Module (utils/network)
Provides TCP network communication functionality, including:
- Creating TCP servers
- Connecting to TCP servers
- Sending and receiving data over TCP
- Platform-independent socket operations

## TCP Examples

The project includes two examples demonstrating TCP networking:

### TCP Server Example
A simple echo server that:
- Listens for incoming connections on port 8080
- Accepts client connections
- Receives data from clients
- Echoes received data back to clients

To run the server:
```bash
./TcpServer
```

### TCP Client Example
A TCP client that:
- Connects to the server on localhost:8080
- Sends test messages to the server
- Receives and displays server responses

To run the client:
```bash
./TcpClient
```

## Building and Running

### Using CMake

```bash
# Create build directory
mkdir build
cd build

# Configure and build project
cmake ..
make

# Run the main program
./HelloWorld

# Run the TCP examples (in separate terminal windows)
./TcpServer
./TcpClient
```

### Using Compiler Directly

```bash
# Compile the main program
g++ -std=c++17 -o HelloWorld main.cpp utils/printer.cpp utils/file/file_handler.cpp utils/text/text_processor.cpp utils/network/tcp_connection.cpp

# Compile the TCP server example
g++ -std=c++17 -o TcpServer utils/examples/tcp_server_example.cpp utils/printer.cpp utils/file/file_handler.cpp utils/text/text_processor.cpp utils/network/tcp_connection.cpp

# Compile the TCP client example
g++ -std=c++17 -o TcpClient utils/examples/tcp_client_example.cpp utils/printer.cpp utils/file/file_handler.cpp utils/text/text_processor.cpp utils/network/tcp_connection.cpp

# Run the main program
./HelloWorld

# Run the TCP examples (in separate terminal windows)
./TcpServer
./TcpClient
```

## Design Principles

This project demonstrates the following C++ design principles:
1. **Modularity**: Related functionality is organized into independent modules
2. **Encapsulation**: Each module exposes functionality through a clear interface
3. **Namespaces**: Using namespaces to avoid name conflicts
4. **Single Responsibility**: Each class and function has a clear single responsibility
5. **Layered Structure**: Code is organized in a logical hierarchical structure
6. **Platform Independence**: Network code works on multiple platforms (Windows, Linux, macOS)

## Extensibility

This project design allows for easy addition of new functionality:
1. Create a new functionality module directory
2. Add interface header and implementation source files
3. Update CMakeLists.txt to include new source files
4. Use the new functionality in main.cpp or create dedicated example programs 