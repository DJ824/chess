#include <utility>
//#include "Square.h"
//#include "Color.h"
#include "Piece.h"
#include <iostream>



Piece::Piece(Color color, std::pair<int, int> coordinates, std::string name) : color(color), coordinates(std::move(coordinates)), type(name) {}

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
    //std::cout << type << std::endl;
    return type;
}

std::vector<std::pair<int, int>> Piece:: getValidMoves() const {
    return validMoves;
}

std::vector<std::pair<int, int>> Piece::  getCaptureMoves() const {
    return captureMoves;
}


void Piece::drawPiece(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int tileSize) {
    SDL_Rect dstRect = {x ,y, tileSize, tileSize};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}






