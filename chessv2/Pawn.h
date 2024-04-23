#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
    bool hasMoved;

public:
    using Piece::Piece;

    inline std::vector<std::pair<int, int>> getValidMoves(const Square board[8][8]) const override {
        std::vector<std::pair<int, int>> validMoves;
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;
        int direction = (color == Color::WHITE) ? 1 : -1;

        if (row + direction >= 0 && row + direction < 8) {
            if (!board[row + direction][col].isOccupied()) {
                validMoves.emplace_back(row + direction, col);
                if (!hasMoved && row + 2 * direction >= 0 && row + 2 * direction < 8 &&
                    !board[row + 2 * direction][col].isOccupied()) {
                    validMoves.emplace_back(row + 2 * direction, col);
                }
            }
        }

        return validMoves;
    }

    inline std::vector<std::pair<int, int>> getCaptureMoves(const Square board[8][8]) const override {
        std::vector<std::pair<int, int>> captureMoves;
        auto pos = getCoordinates();
        int row = pos.first;
        int col = pos.second;
        int direction = (color == Color::WHITE) ? 1 : -1;

        int newRow = row + direction;
        for (int newCol : {col - 1, col + 1}) {
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                if (board[newRow][newCol].isOccupied() && board[newRow][newCol].getPiece()->getColor() != this->color) {
                    captureMoves.emplace_back(newRow, newCol);
                }
            }
        }

        return captureMoves;
    }


};

#endif
