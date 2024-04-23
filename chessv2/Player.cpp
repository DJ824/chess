#include "Player.h"
//#include "Piece.h"
//#include "Board.h"

Player::Player(Color color) : color(color) {}

void Player::addPiece(const std::shared_ptr<Piece> &piece) {
    pieces.push_back(piece);
}

void Player::removePiece(const std::shared_ptr<Piece> &piece) {
    auto it = std::remove(pieces.begin(), pieces.end(), piece);
    pieces.erase(it, pieces.end());
}

bool Player::isValidMove(Square& start, Square& end, Board& board) {
    std::shared_ptr<Piece> currPiece = start.getPiece();
    std::vector<std::pair<int, int>> validMoves = currPiece->getValidMoves(board.getBoard());
    std::vector<std::pair<int, int>> captureMoves = currPiece->getCaptureMoves(board.getBoard());

    std::pair<int, int> endCoordinates = end.getCoordinates();

    if (std::find(validMoves.begin(), validMoves.end(), endCoordinates) != validMoves.end() ||
        std::find(captureMoves.begin(), captureMoves.end(), endCoordinates) != captureMoves.end()) {
        return true;
    }

    return false;
}

void Player::makeMove(Square& start, Square& end, Board& board, Player& whitePlayer, Player& blackPlayer) {
    if (isValidMove(start, end, board)) {
        std::shared_ptr<Piece> currPiece = start.getPiece();
        start.removePiece();
        if (end.isOccupied()){
            std::shared_ptr<Piece> enemyPiece = end.getPiece();
            Color color = end.getPiece()->getColor();
            if (color == Color::BLACK){
                blackPlayer.removePiece(enemyPiece);
            } else {
                whitePlayer.removePiece(enemyPiece);
            }
        }
        end.setPiece(currPiece);
    }
}

Color Player::getColor() {
    return color;
}

bool Player::hasNoPieces() { return pieces.empty(); }
