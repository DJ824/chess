#ifndef PLAYER_H
#define PLAYER_H

#include "Color.h"
#include <vector>
#include <memory>
#include "Piece.h"
#include "Board.h"



class Board;

class Player {
private:
    Color color;
    std::vector<std::shared_ptr<Piece>> pieces;
    bool isInCheck = false;
    bool hasWon = false;
    bool isTurn = false;

public:
    explicit Player(Color color);

    void addPiece(const std::shared_ptr<Piece>& piece);
    void removePiece(const std::shared_ptr<Piece> &piece);
    static bool isValidMove(Square& start, Square& end, Board& board);
    static void makeMove(Square& start, Square& end, Board& board, Player& whitePlayer, Player& blackPlayer);
    Color getColor();
    bool hasNoPieces();
    void printPieces();

};

#endif
