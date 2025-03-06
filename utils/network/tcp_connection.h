#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <string>
#include <vector>
#include <functional>
#include <memory>

// Platform-specific socket headers
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET SocketType;
    #define SOCKET_ERROR_VALUE INVALID_SOCKET
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <netdb.h>
    typedef int SocketType;
    #define SOCKET_ERROR_VALUE (-1)
#endif

namespace utils {
namespace network {

/**
 * TCP Connection class providing basic TCP client/server functionality
 */
class TcpConnection {
public:
    // Callback for incoming data
    typedef void (*DataCallback)(const std::string&);
    
    /**
     * Constructor
     */
    TcpConnection();
    
    /**
     * Destructor - ensures socket cleanup
     */
    ~TcpConnection();
    
    /**
     * Initialize socket library (required for Windows)
     * @return Whether initialization was successful
     */
    bool initialize();
    
    /**
     * Start a TCP server on specified port
     * @param port Port to listen on
     * @param maxConnections Maximum number of pending connections
     * @return Whether server started successfully
     */
    bool startServer(int port, int maxConnections = 5);
    
    /**
     * Accept an incoming connection
     * @return New socket for the accepted connection, or error value
     */
    SocketType acceptConnection();
    
    /**
     * Connect to a TCP server
     * @param host Server hostname or IP address
     * @param port Server port
     * @return Whether connection was successful
     */
    bool connectToServer(const std::string& host, int port);
    
    /**
     * Send data over the connection
     * @param data Data to send
     * @return Number of bytes sent, or -1 on error
     */
    int sendData(const std::string& data);
    
    /**
     * Receive data from the connection
     * @param buffer Buffer to store received data
     * @param bufferSize Size of the buffer
     * @return Number of bytes received, or -1 on error
     */
    int receiveData(char* buffer, int bufferSize);
    
    /**
     * Close the connection
     */
    void closeConnection();
    
    /**
     * Check if connected
     * @return Whether socket is connected
     */
    bool isConnected() const;
    
    /**
     * Set callback for incoming data
     * @param callback Function to call when data is received
     */
    void setDataCallback(DataCallback callback);
    
private:
    SocketType m_socket;
    bool m_isConnected;
    bool m_isServer;
    DataCallback m_dataCallback;
    
    // Platform-specific cleanup
    void cleanup();
};

} // namespace network
} // namespace utils

#endif // TCP_CONNECTION_H 