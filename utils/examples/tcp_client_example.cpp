#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../../utils/printer.h"
#include "../../utils/network/tcp_connection.h"

// Data reception callback
void onDataReceived(const std::string& data) {
    utils::printMessage("Client received: " + data);
}

int main() {
    utils::printMessage("TCP Client Example");
    utils::printMessage("==================\n");
    
    // Create TCP connection for client
    utils::network::TcpConnection client;
    
    // Initialize socket library
    if (!client.initialize()) {
        utils::printMessage("Failed to initialize socket library");
        return 1;
    }
    
    const std::string SERVER_HOST = "127.0.0.1";  // localhost
    const int SERVER_PORT = 8080;
    
    utils::printMessage("Connecting to server " + SERVER_HOST + ":" + std::to_string(SERVER_PORT) + "...");
    
    // Connect to server
    if (!client.connectToServer(SERVER_HOST, SERVER_PORT)) {
        utils::printMessage("Failed to connect to server");
        return 1;
    }
    
    // Set data callback
    client.setDataCallback(onDataReceived);
    
    // Receive buffer
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    
    // Receive welcome message
    int bytesReceived = client.receiveData(buffer, BUFFER_SIZE);
    if (bytesReceived <= 0) {
        utils::printMessage("Failed to receive welcome message");
        client.closeConnection();
        return 1;
    }
    
    // Send some test messages
    std::string testMessages[] = {
        "Hello from client!",
        "This is a TCP client test",
        "Testing message exchange",
        "quit"  // Last message
    };
    
    for (const auto& message : testMessages) {
        utils::printMessage("Sending: " + message);
        
        if (client.sendData(message) < 0) {
            utils::printMessage("Failed to send message");
            break;
        }
        
        // Wait for response
        bytesReceived = client.receiveData(buffer, BUFFER_SIZE);
        if (bytesReceived <= 0) {
            utils::printMessage("Connection closed by server");
            break;
        }
        
        // Pause before next message
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    utils::printMessage("Client shutting down");
    client.closeConnection();
    
    return 0;
} 