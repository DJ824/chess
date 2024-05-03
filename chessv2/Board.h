#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Square.h"
//#include "Piece.h"
#include "Player.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Color.h"
#include "SDL.h"
#include <map>
#include "SDL_image.h"

class Player;

class Board {
private:
    //std::vector<std::vector<Square>> gameBoard;
    Square gameBoard[8][8];
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> pieceTextures;

public:
    explicit Board(SDL_Renderer* renderer);
    //~Board();
    Square &getSquare(int x, int y);
    void setPiece(std::shared_ptr<Piece> piece, int x, int y);
    void initializePieces(Player &whitePlayer, Player &blackPlayer);
    Square (&getBoard())[8][8];
    void drawBoard();
    //void drawPieces();
    void loadTextures();
};

#endif
