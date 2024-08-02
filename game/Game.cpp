#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game()
        : whitePlayer(Color::WHITE), blackPlayer(Color::BLACK), currentPlayer(&whitePlayer), isRunning(true) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Chess Client", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    initializeBoard(renderer);
    assignPieces();


}

Game::~Game() {
    delete board;
}

void Game::initializeBoard(SDL_Renderer *renderer) {
    board = new Board(renderer);
    board->loadTextures();
    board->initializePiecesForDisplay();
}

Board* Game::getBoard()  {
    return board;
}

std::string Game::processMove(const std::string &move) {
    std::istringstream iss(move);
    std::string command;
    iss >> command;

    if (command == "MOVE") {
        int startX, startY, endX, endY;
        iss >> startX >> startY >> endX >> endY;

        std::cout << "Attempting move from (" << startX << ", " << startY
                  << ") to (" << endX << ", " << endY << ")" << std::endl;

        Square& startSquare = board->getSquare(startX, startY);
        Square& endSquare = board->getSquare(endX, endY);

        if (currentPlayer->isValidMove(startSquare, endSquare, *board)) {
            currentPlayer->makeMove(startSquare, endSquare, *board, whitePlayer, blackPlayer);
            switchPlayer();
            checkGameEndConditions();
            std::cout << "Move successful" << std::endl;

            return getSerializedState();
        } else {
            std::cout << "Invalid move" << std::endl;
            return "INVALID_MOVE";
        }
    }
    return "UNKNOWN_COMMAND";
}


void Game::switchPlayer() {
    currentPlayer = (currentPlayer == &whitePlayer) ? &blackPlayer : &whitePlayer;
}

void Game::checkGameEndConditions() {
    if (blackPlayer.hasNoPieces() || whitePlayer.hasNoPieces()) {
        isRunning = false;
    }
}

std::string Game::getSerializedState() const {
    std::stringstream ss;
    ss << "GAME_STATE ";

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Square& square = board->getSquare(i, j);
            if (square.isOccupied()) {
                ss << square.getPiece()->getType() << " ";
            } else {
                ss << "EMPTY ";
            }
        }
    }
    ss << (currentPlayer == &whitePlayer ? "WHITE" : "BLACK");
    return ss.str();
}

bool Game::isGameOver() const {
    return !isRunning;
}

std::string Game::getWinnerInfo() const {
    if (blackPlayer.hasNoPieces()) {
        return "WHITE_WINS";
    } else if (whitePlayer.hasNoPieces()) {
        return "BLACK_WINS";
    } else {
        return "DRAW";
    }
}

void Game::assignPieces() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto piece = board->getSquare(i, j).getPiece();
            if (piece) {
                if (piece->getColor() == Color::WHITE) {
                    whitePlayer.addPiece(piece);
                } else {
                    blackPlayer.addPiece(piece);
                }
            }
        }
    }
}
