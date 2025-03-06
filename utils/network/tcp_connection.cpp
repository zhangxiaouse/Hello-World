#include "tcp_connection.h"
#include <iostream>
#include <cstring>
#include "../printer.h"

namespace utils {
namespace network {

TcpConnection::TcpConnection() : 
    m_socket(SOCKET_ERROR_VALUE), 
    m_isConnected(false), 
    m_isServer(false) {
}

TcpConnection::~TcpConnection() {
    closeConnection();
    cleanup();
}

bool TcpConnection::initialize() {
#ifdef _WIN32
    // Initialize Winsock on Windows
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        utils::printMessage("Error: WSAStartup failed: " + std::to_string(result));
        return false;
    }
    return true;
#else
    // No initialization needed on Unix/Linux/macOS
    return true;
#endif
}

bool TcpConnection::startServer(int port, int maxConnections) {
    if (m_isConnected) {
        closeConnection();
    }
    
    // Create socket
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == SOCKET_ERROR_VALUE) {
        utils::printMessage("Error: Failed to create server socket");
        return false;
    }
    
    // Setup address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    
    // Enable address reuse
    int opt = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt)) < 0) {
        utils::printMessage("Error: setsockopt(SO_REUSEADDR) failed");
        closeConnection();
        return false;
    }
    
    // Bind the socket
    if (bind(m_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        utils::printMessage("Error: Failed to bind server socket");
        closeConnection();
        return false;
    }
    
    // Listen for connections
    if (listen(m_socket, maxConnections) < 0) {
        utils::printMessage("Error: Failed to listen on server socket");
        closeConnection();
        return false;
    }
    
    m_isServer = true;
    utils::printMessage("Server started on port " + std::to_string(port));
    return true;
}

SocketType TcpConnection::acceptConnection() {
    if (!m_isServer || m_socket == SOCKET_ERROR_VALUE) {
        utils::printMessage("Error: Socket not in server mode or invalid");
        return SOCKET_ERROR_VALUE;
    }
    
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    SocketType clientSocket = accept(m_socket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == SOCKET_ERROR_VALUE) {
        utils::printMessage("Error: Failed to accept connection");
        return SOCKET_ERROR_VALUE;
    }
    
    // Get client IP address
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    utils::printMessage("New connection from " + std::string(clientIP) + ":" + 
                       std::to_string(ntohs(clientAddr.sin_port)));
    
    return clientSocket;
}

bool TcpConnection::connectToServer(const std::string& host, int port) {
    if (m_isConnected) {
        closeConnection();
    }
    
    // Create socket
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == SOCKET_ERROR_VALUE) {
        utils::printMessage("Error: Failed to create client socket");
        return false;
    }
    
    // Resolve server address
    struct addrinfo hints, *serverInfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    int result = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &serverInfo);
    if (result != 0) {
        utils::printMessage("Error: Failed to resolve server address");
        closeConnection();
        return false;
    }
    
    // Connect to server
    if (connect(m_socket, serverInfo->ai_addr, serverInfo->ai_addrlen) < 0) {
        utils::printMessage("Error: Failed to connect to server");
        freeaddrinfo(serverInfo);
        closeConnection();
        return false;
    }
    
    freeaddrinfo(serverInfo);
    m_isConnected = true;
    m_isServer = false;
    utils::printMessage("Connected to server " + host + ":" + std::to_string(port));
    return true;
}

int TcpConnection::sendData(const std::string& data) {
    if (!m_isConnected && !m_isServer) {
        utils::printMessage("Error: Not connected");
        return -1;
    }
    
    int bytesSent = send(m_socket, data.c_str(), data.size(), 0);
    if (bytesSent < 0) {
        utils::printMessage("Error: Failed to send data");
    }
    
    return bytesSent;
}

int TcpConnection::receiveData(char* buffer, int bufferSize) {
    if (!m_isConnected && !m_isServer) {
        utils::printMessage("Error: Not connected");
        return -1;
    }
    
    int bytesReceived = recv(m_socket, buffer, bufferSize - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // Null-terminate the received data
        
        // Call the data callback if set
        if (m_dataCallback) {
            m_dataCallback(std::string(buffer, bytesReceived));
        }
    } else if (bytesReceived < 0) {
        utils::printMessage("Error: Failed to receive data");
    } else {
        // bytesReceived == 0, connection closed
        m_isConnected = false;
        utils::printMessage("Connection closed by peer");
    }
    
    return bytesReceived;
}

void TcpConnection::closeConnection() {
    if (m_socket != SOCKET_ERROR_VALUE) {
#ifdef _WIN32
        closesocket(m_socket);
#else
        close(m_socket);
#endif
        m_socket = SOCKET_ERROR_VALUE;
    }
    
    m_isConnected = false;
}

bool TcpConnection::isConnected() const {
    return m_isConnected;
}

void TcpConnection::setDataCallback(DataCallback callback) {
    m_dataCallback = callback;
}

void TcpConnection::cleanup() {
#ifdef _WIN32
    // Cleanup Winsock on Windows
    WSACleanup();
#endif
}

} // namespace network
} // namespace utils 