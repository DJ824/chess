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

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
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
    board->initializePieces(whitePlayer, blackPlayer);
    board->loadTextures();
    board->drawBoard();
    std::cout << "11111" << std:: endl;
}

void Game::switchPlayer() {
    if (currentPlayer->getColor() == Color::WHITE) {
        currentPlayer = &blackPlayer;
    } else {
        currentPlayer = &whitePlayer;
    }
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
            case SDL_MOUSEBUTTONDOWN:
                int mouseX = 0;
                int mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);
                int rowIndex = mouseY / 100;
                int colIndex = mouseX / 100;
                if (selectedSquare->isOccupied()) {
                    Square &targetSquare = board->getSquare(rowIndex, colIndex);
                    if (currentPlayer->isValidMove(*selectedSquare, targetSquare, reinterpret_cast<Board &>(board))) {
                        currentPlayer->makeMove(*selectedSquare, targetSquare, reinterpret_cast<Board &>(board), whitePlayer, blackPlayer);
                        board->drawBoard();
                    }
                    selectedSquare = nullptr;
                } else {
                    selectedSquare = &board->getSquare(rowIndex, colIndex);
                    if (!selectedSquare->isOccupied() ||
                        selectedSquare->getPiece()->getColor() != currentPlayer->getColor()) {
                        selectedSquare = nullptr;
                    }
                }
                break;
        }
    }
}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
    }
}














