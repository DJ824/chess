#ifndef KING_H
#define KING_H

#include "Piece.h"


class King : public Piece {
public:
    using Piece::Piece;

    inline void findValidMoves(const Square board[8][8])  override {
        auto pos = this->getCoordinates();
        int row = pos.first;
        int col = pos.second;

        if (!board[row + 1][col].isOccupied()) {
            validMoves.emplace_back(row + 1, col);
        }

        if (!board[row - 1][col].isOccupied()) {
            validMoves.emplace_back(row - 1, col);
        }

        if (!board[row][col + 1].isOccupied()) {
            validMoves.emplace_back(row, col + 1);
        }

        if (!board[row][col - 1].isOccupied()) {
            validMoves.emplace_back(row, col + 1);
        }

        if (!board[row + 1][col + 1].isOccupied()) {
            validMoves.emplace_back(row + 1, col + 1);
        }

        if (!board[row + 1][col - 1].isOccupied()) {
            validMoves.emplace_back(row + 1, col - 1);
        }

        if (!board[row - 1][col + 1].isOccupied()) {
            validMoves.emplace_back(row - 1, col + 1);
        }

        if (!board[row - 1][col - 1].isOccupied()) {
            validMoves.emplace_back(row - 1, col - 1);
        }
    }

    void findCaptureMoves(const Square board[8][8])  override {
        auto pos = this->getCoordinates();
        int row = pos.first;
        int col = pos.second;

        if (board[row + 1][col].isOccupied() && board[row + 1][col].getPiece()->getColor() != this->color) {
            captureMoves.emplace_back(row + 1, col);
        }

        if (board[row - 1][col].isOccupied() && board[row - 1][col].getPiece()->getColor()  != this->color) {
            captureMoves.emplace_back(row - 1, col);
        }

        if (board[row][col + 1].isOccupied() && board[row][col + 1].getPiece()->getColor()  != this->color) {
            captureMoves.emplace_back(row, col + 1);
        }

        if (board[row][col + 1].isOccupied() && board[row][col + 1].getPiece()->getColor()  != this->color) {
            captureMoves.emplace_back(row, col + 1);
        }

        if (board[row + 1][col + 1].isOccupied() && board[row + 1][col + 1].getPiece()->getColor()  != this->color) {
            captureMoves.emplace_back(row + 1, col + 1);
        }

        if (board[row + 1][col - 1].isOccupied() && board[row + 1][col - 1].getPiece()->getColor() != this->color) {
            captureMoves.emplace_back(row + 1, col - 1);
        }

        if (board[row - 1][col + 1].isOccupied() && board[row - 1][col + 1].getPiece()->getColor()  != this->color) {
            captureMoves.emplace_back(row - 1, col + 1);
        }

        if (board[row - 1][col - 1].isOccupied() && board[row - 1][col - 1].getPiece()->getColor() != this->color) {
            captureMoves.emplace_back(row - 1, col - 1);
        }
    }
};

#endif