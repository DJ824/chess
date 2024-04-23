#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "SDL.h"


class Game {
public:
    Game();
    //~Game();
    void run();

private:
    Board *board;
    Player whitePlayer;
    Player blackPlayer;
    Player *currentPlayer;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isRunning;
    Square *selectedSquare;

    //void initSDL();
    void handleEvents();
    void update();
    //void render();
    //bool isGameOver();
    void switchPlayer();
};

#endif