#include "ChessServer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    int port = 8080; // Default port

    if (argc > 1) {
        port = std::stoi(argv[1]);
    }

    try {
        ChessServer server(port);
        std::cout << "Starting chess server on port " << port << std::endl;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}