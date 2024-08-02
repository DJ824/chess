#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <string>

class Game {
public:
    Game();
    ~Game();
    std::string processMove(const std::string& move);
    std::string getSerializedState() const;
    bool isGameOver() const;
    std::string getWinnerInfo() const;
    Board* getBoard();
    SDL_Renderer* renderer;
    SDL_Window* window;

private:
    Board* board;
    Player whitePlayer;
    Player blackPlayer;
    Player* currentPlayer;
    bool isRunning;
    void initializeBoard(SDL_Renderer* renderer);
    void switchPlayer();
    void checkGameEndConditions();
    void assignPieces();
};

#endif // GAME_H
