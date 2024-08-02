#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Square.h"
//#include "Piece.h"
#include "Player.h"
#include "../pieces/Pawn.h"
#include "../pieces/Knight.h"
#include "../pieces/Bishop.h"
#include "../pieces/Rook.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"
#include "../utils/Color.h"
#include "SDL.h"
#include <map>
#include "SDL_image.h"
//#include "SDL.ttf"

class Player;

class Board {
private:
    //std::vector<std::vector<Square>> gameBoard;
    Square gameBoard[8][8];
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> pieceTextures;

public:
    explicit Board(SDL_Renderer* renderer = nullptr);
    //~Board();
    Square &getSquare(int x, int y);
    void setPiece(std::shared_ptr<Piece> piece, int x, int y);
    void initializePieces(Player &whitePlayer, Player &blackPlayer);
    Square (&getBoard())[8][8];
    void drawBoard();
    //void drawPieces();
    void loadTextures();
    std::string getSerializedState() const;
    void updateFromSerializedState(const std::string &serializedState);
    void initializePiecesForDisplay();
};

#endif
