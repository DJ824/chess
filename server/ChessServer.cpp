#include "ChessServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

ChessServer::ChessServer(int port) : port(port), game(new Game()), running(true) {}

ChessServer::~ChessServer() {
    //delete game;
    stop();
}

void ChessServer::start() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 1) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Server started on port " << port << std::endl;

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
        std::cerr << "Error accepting connection" << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Client connected" << std::endl;

    while (running) {
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::string response = game->processMove(buffer);
            send(clientSocket, response.c_str(), response.length(), 0);
        } else if (bytesRead == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        } else {
            std::cerr << "Error reading from socket" << std::endl;
            break;
        }
    }

    close(clientSocket);
    close(serverSocket);
}

void ChessServer::stop() {
    running = false;
}
