#include "Game.h"
#include <iostream>

Game::Game()
        : whitePlayer(Color::WHITE),
          blackPlayer(Color::BLACK),
          currentPlayer(&whitePlayer),
          isRunning(true),
          window(nullptr),
          renderer(nullptr),
          board(nullptr),
          selectedSquare(nullptr) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);

    if (!window) {
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        exit(1);
    }

    board = new Board(renderer);
    board->loadTextures();
    board->initializePieces(whitePlayer, blackPlayer);
    board->drawBoard();
    //std::cout << "11111" << std::endl;
    //std::cout << currentPlayer->getColor() << std:: endl;
    //std:: cout << blackPlayer.hasNoPieces() <<std::endl;
    //std::cout<<whitePlayer.hasNoPieces()<<std::endl;
    //blackPlayer.printPieces();
    //whitePlayer.printPieces();
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == &whitePlayer) ? &blackPlayer : &whitePlayer;
}

void Game::update() {
    if (blackPlayer.hasNoPieces() || whitePlayer.hasNoPieces()) {
        isRunning = false;
    }
}


void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN: {
                int mouseX = 0;
                int mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);
                int rowIndex = mouseY / 100;
                int colIndex = mouseX / 100;

                if (rowIndex >= 0 && rowIndex < 8 && colIndex >= 0 && colIndex < 8) {
                    Square& clickedSquare = board->getSquare(rowIndex, colIndex);

                    if (selectedSquare) {
                        std::cout << "Trying move from (" << selectedSquare->getCoordinates().first << ", "
                                  << selectedSquare->getCoordinates().second << ") to ("
                                  << rowIndex << ", " << colIndex << ")" << std::endl;

                        if (currentPlayer->isValidMove(*selectedSquare, clickedSquare, *board)) {
                            currentPlayer->makeMove(*selectedSquare, clickedSquare, *board, whitePlayer, blackPlayer);
                            board->drawBoard();
                            switchPlayer();
                            selectedSquare = nullptr;
                        } else {
                            std::cout << "Invalid move attempted." << std::endl;
                            selectedSquare = &clickedSquare;
                        }
                    } else {
                        if (clickedSquare.isOccupied() && clickedSquare.getPiece()->getColor() == currentPlayer->getColor()) {
                            selectedSquare = &clickedSquare;
                        }
                    }
                } else {
                    std::cerr << "Clicked outside of board bounds." << std::endl;
                }
                break;
            }
        }
    }
}



    void Game::run() {
        while (isRunning) {
            handleEvents();
            update();
        }
    }














