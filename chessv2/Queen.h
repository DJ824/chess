#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    using Piece::Piece;

    inline void findValidMoves(const Square board[8][8])  override {
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;

        auto checkDirection = [&](int dx, int dy) {
            for (int i = 1; i < 8; ++i) {
                int newRow = row + i * dx;
                int newCol = col + i * dy;

                if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) {
                    break;
                }

                if (board[newRow][newCol].isOccupied()) {
                    break;
                } else {
                    validMoves.emplace_back(newRow, newCol);
                }
            }
        };

        checkDirection(1, 0);
        checkDirection(-1, 0);
        checkDirection(0, 1);
        checkDirection(0, -1);
        checkDirection(1, 1);
        checkDirection(-1, 1);
        checkDirection(1, -1);
        checkDirection(-1, -1);

    }

    void findCaptureMoves(const Square board[8][8])  override {

        auto checkDirection = [&](int dx, int dy) {
            auto pos = getCoordinates();
            int row = pos.first;
            int col = pos.second;
            for (int i = 1; i < 8; ++i) {
                int newRow = row + i * dx;
                int newCol = col + i * dy;

                if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) {
                    break;
                }
                if (board[newRow][newCol].isOccupied()) {
                    if (board[newRow][newCol].getPiece()->getColor() != this->color) {
                        captureMoves.emplace_back(newRow, newCol);
                    }
                    break;
                }
            }
        };

        checkDirection(1, 0);
        checkDirection(-1, 0);
        checkDirection(0, 1);
        checkDirection(0, -1);
        checkDirection(1, 1);
        checkDirection(-1, 1);
        checkDirection(1, -1);
        checkDirection(-1, -1);

    }
};

#endif