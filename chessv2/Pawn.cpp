#ifndef PAWN_H
#define PAWN_H

#include "Piece.cpp"
#include "Square.cpp" 

class Pawn : public Piece
{

private:
    bool hasMoved;

public:
    using Piece::Piece;

    std::vector<std::pair<int, int>> getValidMoves(const std::vector<std::vector<Square>> &board) const override
    {
          auto pos = this->getCoordinates(); 
            int x = pos.first; 
            int y = pos.second; 
        std::vector<std::pair<int, int>> validMoves;

        int direction = -1; 
        if (color == Color::WHITE)
        {
            direction = 1; 
        }

        if (y + direction >= 0 && y + direction < board.size()) 
        {
            if (!board[x][y + direction].isOccupied())
            {
                validMoves.emplace_back(x, y + direction); 
                if (!hasMoved && !board[x][y + (2 * direction)].isOccupied())
                {
                    validMoves.emplace_back(x, y + (2 * direction)); 
                }
            }
        }
        return validMoves; 
    }

    std::vector<std::pair<int, int>> getCaptureMoves(const std::vector<std::vector<Square>> &board) const override 
    {
        std::vector<std::pair<int, int>> captureMoves;
        auto pos = this->getCoordinates(); 
        int x = pos.first; 
        int y = pos.second; 

        int direction = -1;
        if (color == Color::WHITE)
        {
            direction = 1;
        }

        if (board[x + 1][y + direction].isOccupied() && board[x + 1][y + direction].getPiece()->getColor() != this->color)
        {
            captureMoves.emplace_back(x + 1, y + direction); 
        }

        if (board[x - 1][y + direction].isOccupied() && board[x - 1][y + direction].getPiece()->getColor() != this->color)
        {
            captureMoves.emplace_back(x - 1, y + direction); 
        }

    }
};
#endif