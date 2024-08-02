#include "Board.h"
#include <string>
#include <iostream>
#include <sstream>


Board::Board(SDL_Renderer* providedRenderer) : renderer(providedRenderer) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Color color = ((i + j) % 2 == 0) ? Color::WHITE : Color::BLACK;
            gameBoard[i][j] = Square(std::make_pair(i, j), color);
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


void Board::initializePieces(Player& whitePlayer, Player& blackPlayer) {
    for (int i = 0; i < 8; i++) {
        auto blackPawn = std::make_shared<Pawn>(Color::BLACK, std::make_pair(1, i), "BLACK_PAWN");
        auto whitePawn = std::make_shared<Pawn>(Color::WHITE, std::make_pair(6, i), "WHITE_PAWN");
        gameBoard[1][i].setPiece(blackPawn);
        gameBoard[6][i].setPiece(whitePawn);
        blackPlayer.addPiece(blackPawn);
        whitePlayer.addPiece(whitePawn);
    }

    auto blackRook1 = std::make_shared<Rook>(Color::BLACK, std::make_pair(0, 0), "BLACK_ROOK");
    auto blackRook2 = std::make_shared<Rook>(Color::BLACK, std::make_pair(0, 7), "BLACK_ROOK");
    auto whiteRook1 = std::make_shared<Rook>(Color::WHITE, std::make_pair(7, 0), "WHITE_ROOK");
    auto whiteRook2 = std::make_shared<Rook>(Color::WHITE, std::make_pair(7, 7), "WHITE_ROOK");
    gameBoard[0][0].setPiece(blackRook1);
    gameBoard[0][7].setPiece(blackRook2);
    gameBoard[7][0].setPiece(whiteRook1);
    gameBoard[7][7].setPiece(whiteRook2);
    blackPlayer.addPiece(blackRook1);
    blackPlayer.addPiece(blackRook2);
    whitePlayer.addPiece(whiteRook1);
    whitePlayer.addPiece(whiteRook2);

    auto blackKnight1 = std::make_shared<Knight>(Color::BLACK, std::make_pair(0, 1), "BLACK_KNIGHT");
    auto blackKnight2 = std::make_shared<Knight>(Color::BLACK, std::make_pair(0, 6), "BLACK_KNIGHT");
    auto whiteKnight1 = std::make_shared<Knight>(Color::WHITE, std::make_pair(7, 1), "WHITE_KNIGHT");
    auto whiteKnight2 = std::make_shared<Knight>(Color::WHITE, std::make_pair(7, 6), "WHITE_KNIGHT");
    gameBoard[0][1].setPiece(blackKnight1);
    gameBoard[0][6].setPiece(blackKnight2);
    gameBoard[7][1].setPiece(whiteKnight1);
    gameBoard[7][6].setPiece(whiteKnight2);
    blackPlayer.addPiece(blackKnight1);
    blackPlayer.addPiece(blackKnight2);
    whitePlayer.addPiece(whiteKnight1);
    whitePlayer.addPiece(whiteKnight2);

    auto blackBishop1 = std::make_shared<Bishop>(Color::BLACK, std::make_pair(0, 2), "BLACK_BISHOP");
    auto blackBishop2 = std::make_shared<Bishop>(Color::BLACK, std::make_pair(0, 5), "BLACK_BISHOP");
    auto whiteBishop1 = std::make_shared<Bishop>(Color::WHITE, std::make_pair(7, 2), "WHITE_BISHOP");
    auto whiteBishop2 = std::make_shared<Bishop>(Color::WHITE, std::make_pair(7, 5), "WHITE_BISHOP");
    gameBoard[0][2].setPiece(blackBishop1);
    gameBoard[0][5].setPiece(blackBishop2);
    gameBoard[7][2].setPiece(whiteBishop1);
    gameBoard[7][5].setPiece(whiteBishop2);
    blackPlayer.addPiece(blackBishop1);
    blackPlayer.addPiece(blackBishop2);
    whitePlayer.addPiece(whiteBishop1);
    whitePlayer.addPiece(whiteBishop2);

    auto blackQueen = std::make_shared<Queen>(Color::BLACK, std::make_pair(0, 3), "BLACK_QUEEN");
    auto whiteQueen = std::make_shared<Queen>(Color::WHITE, std::make_pair(7, 3), "WHITE_QUEEN");
    gameBoard[0][3].setPiece(blackQueen);
    gameBoard[7][3].setPiece(whiteQueen);
    blackPlayer.addPiece(blackQueen);
    whitePlayer.addPiece(whiteQueen);

    auto blackKing = std::make_shared<King>(Color::BLACK, std::make_pair(0, 4), "BLACK_KING");
    auto whiteKing = std::make_shared<King>(Color::WHITE, std::make_pair(7, 4), "WHITE_KING");
    gameBoard[0][4].setPiece(blackKing);
    gameBoard[7][4].setPiece(whiteKing);
    blackPlayer.addPiece(blackKing);
    whitePlayer.addPiece(whiteKing);
}

void Board::loadTextures() {
    std::string resourcePath = "../../Images/";

    std::vector<std::pair<std::string, std::string>> pieceTypes = {
            {"WHITE_PAWN", "white-pawn.png"},
            {"BLACK_PAWN", "black-pawn.png"},
            {"WHITE_KNIGHT", "white-knight.png"},
            {"BLACK_KNIGHT", "black-knight.png"},
            {"WHITE_BISHOP", "white-bishop.png"},
            {"BLACK_BISHOP", "black-bishop.png"},
            {"WHITE_ROOK", "white-rook.png"},
            {"BLACK_ROOK", "black-rook.png"},
            {"WHITE_KING", "white-king.png"},
            {"BLACK_KING", "black-king.png"},
            {"WHITE_QUEEN", "white-queen.png"},
            {"BLACK_QUEEN", "black-queen.png"}
    };

    for (const auto& pieceType : pieceTypes) {
        std::string pieceName = pieceType.first;
        std::string fileName = pieceType.second;
        std::string fullPath = resourcePath + fileName;

        SDL_Texture* texture = IMG_LoadTexture(renderer, fullPath.c_str());
        if (!texture) {
            std::cerr << "Failed to load texture " << fullPath << ": " << IMG_GetError() << std::endl;
        } else {
            pieceTextures[pieceName] = texture;
            std::cout << "Successfully loaded texture for " << pieceName << " from " << fullPath << std::endl;
        }
    }

    if (pieceTextures.size() != pieceTypes.size()) {
        std::cerr << "Warning: Not all textures were loaded successfully." << std::endl;
    }
}

void Board::drawBoard() {
    int tileSize = 100;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gameBoard[i][j].draw(renderer, j * tileSize, i * tileSize, tileSize);
            auto piece = gameBoard[i][j].getPiece();
            if (piece) {
                SDL_Texture* texture = pieceTextures[piece->getType()];
                piece->drawPiece(renderer, texture, j * tileSize, i * tileSize, tileSize);
            }
        }
    }
}

void Board::updateFromSerializedState(const std::string& serializedState) {
    std::istringstream iss(serializedState);
    std::string token;
    iss >> token;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            iss >> token;
            if (token == "EMPTY") {
                gameBoard[i][j].setPiece(nullptr);
            } else {
                Color color = (token.find("WHITE") != std::string::npos) ? Color::WHITE : Color::BLACK;
                std::shared_ptr<Piece> piece;

                if (token.find("PAWN") != std::string::npos) {
                    piece = std::make_shared<Pawn>(color, std::make_pair(i, j), token);
                } else if (token.find("ROOK") != std::string::npos) {
                    piece = std::make_shared<Rook>(color, std::make_pair(i, j), token);
                } else if (token.find("KNIGHT") != std::string::npos) {
                    piece = std::make_shared<Knight>(color, std::make_pair(i, j), token);
                } else if (token.find("BISHOP") != std::string::npos) {
                    piece = std::make_shared<Bishop>(color, std::make_pair(i, j), token);
                } else if (token.find("QUEEN") != std::string::npos) {
                    piece = std::make_shared<Queen>(color, std::make_pair(i, j), token);
                } else if (token.find("KING") != std::string::npos) {
                    piece = std::make_shared<King>(color, std::make_pair(i, j), token);
                }

                gameBoard[i][j].setPiece(piece);
            }
        }
    }
}


