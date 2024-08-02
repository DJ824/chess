#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>
#include "../utils/Color.h"
#include "../game/Square.h"
#include "SDL.h"
#include <string>
//#include "Board.h"

//class Square;

class Piece {
protected:
    Color color;
    std::pair<int, int> coordinates;
    std::string type;
    std::vector<std::pair<int, int>> validMoves;
    std::vector<std::pair<int, int>> captureMoves;

public:
    Piece(Color color, std::pair<int, int> coordinates, std::string name);
    virtual ~Piece() = default;

    Color getColor() const;
    std::string getType() const;
    std::pair<int, int> getCoordinates() const;
    void setPosition(int newX, int newY);
    static void drawPiece(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int tileSize);
    std::vector<std::pair<int, int>> getValidMoves() const;
    std::vector<std::pair<int, int>> getCaptureMoves() const;

    virtual void findValidMoves(const Square board[8][8]) = 0;
    virtual void findCaptureMoves(const Square board[8][8]) = 0;
};

#endif
