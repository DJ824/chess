#include <utility>
//#include "Square.h"
#include "Color.h"
#include "Piece.h"

Piece::Piece(Color color, std::pair<int, int> coordinates) : color(color), coordinates(std::move(coordinates)) {}

Color Piece::getColor() const {
    return color;
}

std::pair<int, int> Piece::getCoordinates() const {
    return coordinates;
}

void Piece::setPosition(int newX, int newY) {
    coordinates = {newX, newY};
}

std::string Piece::getType() const {
    return type;
}

void Piece::drawPiece(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int tileSize) {
    SDL_Rect dstRect = {x ,y, tileSize, tileSize};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}






