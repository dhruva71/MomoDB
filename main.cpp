#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "CommandProcessor.h"
#include "keystore.h"
#include "walogger.h"

// TODO explore not hardcoding this
constexpr int PORT = 9001;
constexpr int MAX_CONNECTIONS = 5;



int main() {
    std::cout << "Starting momoDB" << std::endl;

    WaLogger logger = WaLogger();
    logger.loadLogFile("./sample.log");
    keystore keystore(logger);
    keystore.rebuildFromLog();
    momodb::CommandProcessor command_processor(logger, keystore);

    const int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return 1;
    }
    std::cout << "Socket created successfully: " << server_fd << std::endl;

    sockaddr_in address{.sin_family = AF_INET, .sin_port = htons(PORT)}; // host to network short
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_fd, reinterpret_cast<sockaddr *>(&address), sizeof(address)) == -1) {
        std::cerr << "Could not bind address " << address.sin_addr.s_addr << ":" << ntohs(address.sin_port) <<
                std::endl;
    }
    std::cout << "Binding successfull to port " << ntohs(address.sin_port) << std::endl;

    if (listen(server_fd, MAX_CONNECTIONS) == -1) {
        std::cerr << "Could not listen on socket" << std::endl;
    }
    std::cout << "Listening on port " << ntohs(address.sin_port) << std::endl;

    try {
        while (true) {
            int address_len = sizeof(address);
            const int client_socket = accept(server_fd, reinterpret_cast<sockaddr *>(&address),
                                       reinterpret_cast<socklen_t *>(&address_len));
            if (client_socket == -1) {
                std::cerr << "Could not accept connection" << std::endl;
                continue;
            }
            char buffer[1024] = {};
            const size_t chars_read = read(client_socket, buffer, 1024);
            buffer[chars_read] = '\0'; // adding null just to be sure we have a delimiter
            if (chars_read > 0) {
                std::string_view view{buffer};
                std::cout << "Received message: <" << view << "> of length " << view.length() << std::endl;

                std::string response = "OK";
                send(client_socket, response.data(), response.length(), 0);

                // command processing
                // TODO abstract this away
                // TODO check if exit should possibly check for other open sockets as well
                auto execution_success = command_processor.parse_and_execute_command(view);
                if (execution_success) {
                    std::cout << "Received exit command; shutting down." << std::endl;
                    close(client_socket);
                    break;
                }
            } else {
                std::cerr << "Connection closed" << std::endl;
            }

            close(client_socket);
        }
    } catch (std::exception &e) {
        std::cerr << "Exception occurred!" << std::endl;
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
