#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Set up the hints for getaddrinfo
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Get the address information
    struct addrinfo *result;
    int status = getaddrinfo("localhost", "1234", &hints, &result);
    if (status != 0) {
        std::cerr << "Error getting address information: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Create a socket
    int sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Connect to the server
    if (connect(sock, result->ai_addr, result->ai_addrlen) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    std::cout << "Connected to server" << std::endl;

    // Send data to the server
    std::string message = "Hello, server!";
    send(sock, message.c_str(), message.length(), 0);

    // Receive data from the server
    char buffer[1024];
    int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        std::cerr << "Error receiving data from server" << std::endl;
        return 1;
    }

    std::cout << "Received: " << std::string(buffer, bytes_received) << std::endl;

    // Close the socket
    close(sock);
    freeaddrinfo(result);

    return 0;
}
