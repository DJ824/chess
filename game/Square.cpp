#include <iostream>
#include "Square.h"
//#include "Piece.h"

Square::Square() : coordinates(std::make_pair(0, 0)), color(Color::WHITE), piece(nullptr) {}

Square::Square(std::pair<int, int> pos, Color color)
        : coordinates(std::move(pos)), color(color), piece(nullptr) {}

bool Square::isOccupied() const {
    return piece != nullptr;
}

std::shared_ptr<Piece> Square::getPiece() const {
    if (!isOccupied()) {
        return nullptr;
    }
    return piece;
}

void Square::setPiece(std::shared_ptr<Piece> newPiece) {
    if (piece == nullptr) {
        piece = std::move(newPiece);
    } else {
        removePiece();
        piece = std::move(newPiece);
    }
}

void Square::removePiece() {
    piece = nullptr;
}

void Square::setColor(Color newColor) {
    color = newColor;
}

std::pair<int, int> Square::getCoordinates() {
    return coordinates;
}

void Square::draw(SDL_Renderer* renderer, int x, int y, int tileSize) {
    SDL_Rect rect = {x, y, tileSize, tileSize};

    if (color == Color::WHITE) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    }
    SDL_RenderFillRect(renderer, &rect);
}

