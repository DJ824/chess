#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include "Color.h"
//#include "Piece.h"
#include <SDL.h>

class Piece;

class Square {
private:
    std::pair<int, int> coordinates;
    std::shared_ptr<Piece> piece;
    Color color;

public:
    Square () ;
    Square(std::pair<int, int> pos, Color color);
    bool isOccupied() const;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> newPiece);
    void removePiece();
    void setColor(Color newColor);
    std::pair<int, int> getCoordinates();
    void draw(SDL_Renderer* renderer, int x, int y, int tileSize);
};

#endif
