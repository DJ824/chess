#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>
#include "Color.h"
#include "Square.h"
#include "SDL.h"
#include <string>

//class Square;

class Piece {
protected:
    Color color;
    std::pair<int, int> coordinates;
    std::string type;

public:
    Piece(Color color, std::pair<int, int> coordinates);
    virtual ~Piece() = default;

    Color getColor() const;
    std::string getType() const;
    std::pair<int, int> getCoordinates() const;
    void setPosition(int newX, int newY);
    static void drawPiece(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int tileSize);

    virtual std::vector<std::pair<int, int>> getValidMoves(const Square board[8][8]) const = 0;
    virtual std::vector<std::pair<int, int>> getCaptureMoves(const Square board[8][8]) const = 0;
};

#endif
