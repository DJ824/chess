#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game()
        : whitePlayer(Color::WHITE), blackPlayer(Color::BLACK), currentPlayer(&whitePlayer), isRunning(true) {

}

Game::~Game() {
    delete board;
}

void Game::initializeBoard(SDL_Renderer *renderer) {
    board = new Board(renderer);
    board->loadTextures();
    board->initializePieces(whitePlayer, blackPlayer);
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

        Square& startSquare = board->getSquare(startX, startY);
        Square& endSquare = board->getSquare(endX, endY);

        if (currentPlayer->isValidMove(startSquare, endSquare, *board)) {
            currentPlayer->makeMove(startSquare, endSquare, *board, whitePlayer, blackPlayer);
            switchPlayer();
            checkGameEndConditions();
            return getSerializedState();
        } else {
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
