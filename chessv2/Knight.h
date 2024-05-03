#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
//#include "Square.cpp"



class Knight : public Piece {
public:
    using Piece::Piece;

    inline void findValidMoves(const Square board[8][8])  override {
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;

        const int moves[8][2] = {
                {1,  2},
                {2,  1},
                {-1, 2},
                {-2, 1},
                {1,  -2},
                {2,  -1},
                {-1, -2},
                {-2, -1}};

        for (const auto &move: moves) {
            validMoves.emplace_back(row + move[0], col + move[1]);
        }
    }

    void findCaptureMoves(const Square board[8][8])  override {
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;

        const int moves[8][2] = {
                {1,  2},
                {2,  1},
                {-1, 2},
                {-2, 1},
                {1,  -2},
                {2,  -1},
                {-1, -2},
                {-2, -1}};

        for (const auto &move: moves) {
            if (board[row + move[0]][col + move[1]].isOccupied() &&
                board[row + move[0]][col + move[1]].getPiece()->getColor() != this->color)
                captureMoves.emplace_back(row + move[0], col + move[1]);
        }
    }


};

#endif