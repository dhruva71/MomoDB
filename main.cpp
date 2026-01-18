#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#include "keystore.h"
#include "walogger.h"

constexpr int PORT = 9001;

int main() {
    std::cout << "Starting momoDB" << std::endl;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return 1;
    }
    std::cout << "Socket created successfully: " << server_fd << std::endl;

    sockaddr_in address{.sin_family = AF_INET, .sin_port = htons(PORT)}; // host to network short
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_fd, reinterpret_cast<sockaddr *>(&address), sizeof(address)) == -1) {
        std::cerr << "Could not bind address" << address.sin_addr.s_addr << ":" << ntohs(address.sin_port) << std::endl;
    }
    std::cout << "Binding successfull to port " << ntohs(address.sin_port) << std::endl;

    return 0;
}
