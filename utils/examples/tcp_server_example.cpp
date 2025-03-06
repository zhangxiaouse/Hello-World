#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../../utils/printer.h"
#include "../../utils/network/tcp_connection.h"

// Data reception callback
void onDataReceived(const std::string& data) {
    utils::printMessage("Server received: " + data);
}

int main() {
    utils::printMessage("TCP Server Example");
    utils::printMessage("==================\n");
    
    // Create TCP connection for server
    utils::network::TcpConnection server;
    
    // Initialize socket library
    if (!server.initialize()) {
        utils::printMessage("Failed to initialize socket library");
        return 1;
    }
    
    const int PORT = 8080;
    
    // Start server on port 8080
    if (!server.startServer(PORT)) {
        utils::printMessage("Failed to start server");
        return 1;
    }
    
    utils::printMessage("Server started on port " + std::to_string(PORT));
    utils::printMessage("Waiting for client connections...");
    
    // Set data callback
    server.setDataCallback(onDataReceived);
    
    // Accept a client connection
    auto clientSocket = server.acceptConnection();
    if (clientSocket == SOCKET_ERROR_VALUE) {
        utils::printMessage("Failed to accept connection");
        return 1;
    }
    
    // Send welcome message
    std::string welcomeMsg = "Welcome to the TCP server example!";
    if (server.sendData(welcomeMsg) < 0) {
        utils::printMessage("Failed to send welcome message");
    }
    
    // Receive buffer
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    
    // Keep receiving data until connection closed
    while (true) {
        int bytesReceived = server.receiveData(buffer, BUFFER_SIZE);
        if (bytesReceived <= 0) {
            break;  // Connection closed or error
        }
        
        // Echo received data back to client
        std::string response = "Echo: " + std::string(buffer);
        server.sendData(response);
    }
    
    utils::printMessage("Server shutting down");
    server.closeConnection();
    
    return 0;
} 