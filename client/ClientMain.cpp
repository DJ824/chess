#include "ChessClient.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port>" << std::endl;
        return 1;
    }

    const char* serverIP = argv[1];
    int port = std::stoi(argv[2]);

    try {
        ChessClient client(serverIP, port);
        std::cout << "Connecting to chess server at " << serverIP << ":" << port << std::endl;
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

