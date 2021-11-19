#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // This client sends a string to the server.
    // The server will send an acknowledgement.
    // This client can then close the connection.

    std::string data_to_send = "Hello, world!\n";
    uint16_t server_port = 12345;

    int connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection == -1) {
        std::cerr << "Error getting socket\n";
        return 1;
    }

    hostent *host = gethostbyname("localhost");
    if (!host) {
        std::cerr << "Error resolving host\n";
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr, host->h_addr, host->h_length);
    server_addr.sin_port = htons(server_port);

    if (connect(connection, (sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error connecting to server\n";
        return 1;
    }

    if (send(connection, data_to_send.c_str(), data_to_send.length() + 1, 0) == -1) {
        std::cerr << "Error sending data\n";
        return 1;
    }

    std::string ack = "ACK";
    std::array<char, 3> buf;
    if (recv(connection, buf.data(), buf.size(), MSG_WAITALL) != (int) buf.size()) {
        std::cerr << "Error receving ACK\n";
        return 1;
    }

    assert(std::string(buf.data(), buf.size()) == ack);
    std::cout << "Got ACK from server\n";

    close(connection);

    return 0;
}
