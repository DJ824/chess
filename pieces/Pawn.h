#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include "Piece.h"

class Pawn : public Piece {

public:
    using Piece::Piece;
    bool hasMoved = false;

    inline void findValidMoves(const Square board[8][8]) override {
        validMoves.clear();
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;
        int direction = (color == Color::WHITE) ? -1 : 1;

        if (row + direction >= 0 && row + direction < 8) {
            if (!board[row + direction][col].isOccupied()) {
                validMoves.emplace_back(row + direction, col);
                if (!hasMoved && row + 2 * direction >= 0 && row + 2 * direction < 8 &&
                    !board[row + 2 * direction][col].isOccupied()) {
                    validMoves.emplace_back(row + 2 * direction, col);
                }
            }
        }

    }


    inline void findCaptureMoves(const Square board[8][8]) override {
        captureMoves.clear();
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;
        int direction = (color == Color::WHITE) ? -1 : 1;

        int colOffsets[] = {-1, 1};

        for (int offset : colOffsets) {
            int newRow = row + direction;
            int newCol = col + offset;

            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                if (board[newRow][newCol].isOccupied() && board[newRow][newCol].getPiece()->getColor() != this->color) {
                    captureMoves.emplace_back(newRow, newCol);
                }
            }
        }
    }


};

#endif
