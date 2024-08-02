#ifndef CHESS_SERVER_H
#define CHESS_SERVER_H

#include <SDL.h>
#include <vector>
#include <mutex>
#include <memory>
#include "../game/Game.h"

class ChessServer {
public:
    ChessServer(int port);
    ~ChessServer();
    void start();
    void stop();

private:
    int port;
    std::vector<int> clientSockets;
    std::unique_ptr<Game> game;
    std::mutex clientsMutex;
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void initializeGame();
    void handleClientConnection(int clientSocket);
    void processClientMessage(int clientSocket, const std::string& message);
    void removeClient(int clientSocket);
    void broadcastMessage(const std::string& message);
};

#endif // CHESS_SERVER_H