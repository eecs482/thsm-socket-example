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
    
    // TODO: Receive data from the client and print it.

    return 0;
}