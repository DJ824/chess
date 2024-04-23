#include "Board.h"
#include <string>


/*Board::Board() {
    gameBoard.resize(8);
    int tileSize = 100;
    for (int i = 0; i < 8; ++i) {
        //gameBoard[i].resize(8);
        for (int j = 0; j < 8; ++j) {
            int x = i;
            Color color = ((i + j) % 2 == 0) ? Color::BLACK : Color::WHITE;
            gameBoard[i][j] = Square(std::make_pair(i, j), color);
        }
    }
}*/

Board::Board(SDL_Renderer* providedRenderer) : renderer(providedRenderer) {
    //gameBoard.resize(8);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Color color = ((i + j) % 2 == 0) ? Color::WHITE : Color::BLACK;
            gameBoard[i][j] =  Square(std::make_pair(i, j), color);
        }
    }
}


Square &Board::getSquare(int x, int y) {
    return gameBoard[x][y];
}

void Board::setPiece(std::shared_ptr<Piece> piece, int x, int y) {
    gameBoard[x][y].setPiece(std::move(piece));
}

Square (&Board::getBoard())[8][8] {
    return gameBoard;
}



void Board::initializePieces(Player whitePlayer, Player blackPlayer) {
    for (int i = 0; i < 8; i++) {
        auto blackPawn = std::make_shared<Pawn>(Color::BLACK, std::make_pair(1, i));
        auto whitePawn = std::make_shared<Pawn>(Color::WHITE, std::make_pair(6, i));
        gameBoard[1][i].setPiece(blackPawn);
        gameBoard[6][i].setPiece(whitePawn);
        blackPlayer.addPiece(blackPawn);
        whitePlayer.addPiece(whitePawn);
    }

    auto blackRook1 = std::make_shared<Rook>(Color::BLACK, std::make_pair(0, 0));
    auto blackRook2 = std::make_shared<Rook>(Color::BLACK, std::make_pair(0, 7));
    auto whiteRook1 = std::make_shared<Rook>(Color::WHITE, std::make_pair(7, 0));
    auto whiteRook2 = std::make_shared<Rook>(Color::WHITE, std::make_pair(7, 7));
    gameBoard[0][0].setPiece(blackRook1);
    gameBoard[0][7].setPiece(blackRook2);
    gameBoard[7][0].setPiece(whiteRook1);
    gameBoard[7][7].setPiece(whiteRook2);
    blackPlayer.addPiece(blackRook1);
    blackPlayer.addPiece(blackRook2);
    whitePlayer.addPiece(whiteRook1);
    whitePlayer.addPiece(whiteRook2);

    auto blackKnight1 = std::make_shared<Knight>(Color::BLACK, std::make_pair(0, 1));
    auto blackKnight2 = std::make_shared<Knight>(Color::BLACK, std::make_pair(0, 6));
    auto whiteKnight1 = std::make_shared<Knight>(Color::WHITE, std::make_pair(7, 1));
    auto whiteKnight2 = std::make_shared<Knight>(Color::WHITE, std::make_pair(7, 6));
    gameBoard[0][1].setPiece(blackKnight1);
    gameBoard[0][6].setPiece(blackKnight2);
    gameBoard[7][1].setPiece(whiteKnight1);
    gameBoard[7][6].setPiece(whiteKnight2);
    blackPlayer.addPiece(blackKnight1);
    blackPlayer.addPiece(blackKnight2);
    whitePlayer.addPiece(whiteKnight1);
    whitePlayer.addPiece(whiteKnight2);

    auto blackBishop1 = std::make_shared<Bishop>(Color::BLACK, std::make_pair(0, 2));
    auto blackBishop2 = std::make_shared<Bishop>(Color::BLACK, std::make_pair(0, 5));
    auto whiteBishop1 = std::make_shared<Bishop>(Color::WHITE, std::make_pair(7, 2));
    auto whiteBishop2 = std::make_shared<Bishop>(Color::WHITE, std::make_pair(7, 5));
    gameBoard[0][2].setPiece(blackBishop1);
    gameBoard[0][5].setPiece(blackBishop2);
    gameBoard[7][2].setPiece(whiteBishop1);
    gameBoard[7][5].setPiece(whiteBishop2);
    blackPlayer.addPiece(blackBishop1);
    blackPlayer.addPiece(blackBishop2);
    whitePlayer.addPiece(whiteBishop1);
    whitePlayer.addPiece(whiteBishop2);

    auto blackQueen = std::make_shared<Queen>(Color::BLACK, std::make_pair(0, 3));
    auto whiteQueen = std::make_shared<Queen>(Color::WHITE, std::make_pair(7, 3));
    gameBoard[0][3].setPiece(blackQueen);
    gameBoard[7][3].setPiece(whiteQueen);
    blackPlayer.addPiece(blackQueen);
    whitePlayer.addPiece(whiteQueen);

    auto blackKing = std::make_shared<King>(Color::BLACK, std::make_pair(0, 4));
    auto whiteKing = std::make_shared<King>(Color::WHITE, std::make_pair(7, 4));
    gameBoard[0][4].setPiece(blackKing);
    gameBoard[7][4].setPiece(whiteKing);
    blackPlayer.addPiece(blackKing);
    whitePlayer.addPiece(whiteKing);
}

void Board::loadTextures() {
    pieceTextures["WHITE_PAWN"] = IMG_LoadTexture(renderer, "Images/white-pawn.png");
    pieceTextures["BLACK_PAWN"] = IMG_LoadTexture(renderer, "Images/black-pawn.png");
    pieceTextures["WHITE_KNIGHT"] = IMG_LoadTexture(renderer, "Images/white-knight.png");
    pieceTextures["BLACK_KNIGHT"] = IMG_LoadTexture(renderer, "Images/black-knight.png");
    pieceTextures["WHITE_BISHOP"] = IMG_LoadTexture(renderer, "Images/white-bishop.png");
    pieceTextures["BLACK_BISHOP"] = IMG_LoadTexture(renderer, "Images/black-bishop.png");
    pieceTextures["WHITE_ROOK"] = IMG_LoadTexture(renderer, "Images/white-rook.png");
    pieceTextures["BLACK_ROOK"] = IMG_LoadTexture(renderer, "Images/black-rook.png");
    pieceTextures["WHITE_KING"] = IMG_LoadTexture(renderer, "Images/white-king.png");
    pieceTextures["BLACK_KING"] = IMG_LoadTexture(renderer, "Images/black-king.png");
    pieceTextures["WHITE_QUEEN"] = IMG_LoadTexture(renderer, "Images/white-queen.png");
    pieceTextures["BLACK_QUEEN"] = IMG_LoadTexture(renderer, "Images/black-queen.png");
}


void Board::drawBoard() {
    int tileSize = 100;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gameBoard[i][j].draw(renderer, i * tileSize, j * tileSize, tileSize);
            auto piece = gameBoard[i][j].getPiece();
            if (piece) {
                SDL_Texture* texture = pieceTextures[piece->getType()];
                piece->drawPiece(renderer, texture, i * tileSize, j * tileSize, tileSize);
            }
        }
    }
    SDL_RenderPresent(renderer);
}



