#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.cpp"
#include "Square.cpp"


class Knight : public Piece
{
public:
    using Piece::Piece;

    std::vector<std::pair<int, int>> getValidMoves(const std::vector<std::vector<Square>> &board) const override
    {
           auto pos = this->getCoordinates(); 
            int x = pos.first; 
            int y = pos.second; 
        std::vector<std::pair<int, int>> validMoves;
    
        const int moves[8][2] = {
            {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1}};

        for (const auto &move : moves)
        {
            validMoves.emplace_back(x + move[0], y + move[1]);
        }
        return validMoves;
    }

    std::vector<std::pair<int, int>> getCaptureMoves(const std::vector<std::vector<Square>> &board) const override
    {
           auto pos = this->getCoordinates(); 
            int x = pos.first; 
            int y = pos.second; 
        std::vector<std::pair<int, int>> captureMoves;

        const int moves[8][2] = {
            {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1}};

        for (const auto &move : moves)
        {
            if (board[x + move[0]][y + move[1]].isOccupied() && board[x + move[0]][y + move[1]].getPiece()->getColor() != this->color)
            captureMoves.emplace_back(x + move[0], y + move[1]);
        }
        return captureMoves;
    }

    
};
#endif