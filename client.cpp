#include <cstdint>
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

    // TODO: Send data_to_send to the server.

    return 0;
}