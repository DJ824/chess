#ifndef CHESS_CLIENT_H
#define CHESS_CLIENT_H

#include <SDL.h>
#include <SDL_image.h>
#include "../game/Board.h"
#include <string>

class ChessClient {
public:
    ChessClient(const char* serverIP, int port);
    ~ChessClient();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unique_ptr<Board> board;
    int socket;
    bool isRunning;
    Square* selectedSquare;
    Player* whitePlayer;
    Player* blackPlayer;

    void connectToServer(const char* serverIP, int port);
    void handleEvents();
    void handleMouseClick(int mouseX, int mouseY);
    void render();
    void sendMove(int startX, int startY, int endX, int endY);
    void receiveServerMessages();
    void handleServerResponse(const std::string& response);
};

#endif // CHESS_CLIENT_H