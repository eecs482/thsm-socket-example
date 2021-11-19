#include <array>
#include <cstdint>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // The client sends a string to this server.
    // This server sends an acknowledgement.
    // The client will then close the connection.

    uint16_t server_port = 12345;
    
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        std::cerr << "Error getting socket\n";
        return 1;
    }
    int yes = 1;
	if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        std::cerr << "Error setting socket options\n";
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    if (bind(server, (sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error binding to port\n";
        return 1;
    }

    if (listen(server, 5) == -1) {
        std::cerr << "Error listening\n";
        return 1;
    }

    int connection = accept(server, nullptr, nullptr);
    if (connection == -1) {
        std::cerr << "Error accepting connection\n";
        return 1;
    }

    while (true) {
        std::array<char, 100> buf;
        int len = recv(connection, buf.data(), buf.size(), 0);
        if (len == -1) {
            std::cerr << "Error receiving data\n";
            return 1;
        }
        if (len == 0) {
            std::cerr << "Client closed connection\n";
            return 1;
        }
        std::cout << std::string(buf.data(), len);
        if (buf.data()[len - 1] == '\0') {
            std::string ack = "ACK";
            send(connection, ack.data(), ack.length(), MSG_NOSIGNAL);
            break;
        }
    }
    close(connection);
    close(server);

    return 0;
}
