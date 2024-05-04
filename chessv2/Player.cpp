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
    if (!currPiece) return false;

    currPiece->findValidMoves(board.getBoard());
    currPiece->findCaptureMoves(board.getBoard());
    std::pair<int, int> endCoordinates = end.getCoordinates();

    std::cout << "Valid moves for " << currPiece->getType() << " at (" << start.getCoordinates().first << ", " << start.getCoordinates().second << "): ";
    for (const auto& move : currPiece->getValidMoves()) {
        std::cout << "(" << move.first << ", " << move.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "Capture moves for " << currPiece->getType() << " at (" << start.getCoordinates().first << ", " << start.getCoordinates().second << "): ";
    for (const auto& move : currPiece->getCaptureMoves()) {
        std::cout << "(" << move.first << ", " << move.second << ") ";
    }
    std::cout << std::endl;


    bool isValid = false;

    for (const auto& move : currPiece->getValidMoves()) {
        if (move.first == endCoordinates.first && move.second == endCoordinates.second) {
            isValid = true;
            break;
        }
    }


    for (const auto& move : currPiece->getCaptureMoves()) {
        if (move.first == endCoordinates.first && move.second == endCoordinates.second) {
            isValid = true;
            break;
        }
    }
    return isValid;
}


void Player::makeMove(Square& start, Square& end, Board& board, Player& whitePlayer, Player& blackPlayer) {
    if (isValidMove(start, end, board)) {
        std::shared_ptr<Piece> currPiece = start.getPiece();

        if (end.isOccupied()) {
            std::shared_ptr<Piece> enemyPiece = end.getPiece();
            Color enemyColor = enemyPiece->getColor();
            if (enemyColor == Color::BLACK) {
                blackPlayer.removePiece(enemyPiece);
            } else {
                whitePlayer.removePiece(enemyPiece);
            }
        }
        start.removePiece();
        end.setPiece(currPiece);

        if (Pawn* p = dynamic_cast<Pawn*>(currPiece.get())) {
            p->hasMoved = true;
        }

        std::pair<int, int> endCoordinates = end.getCoordinates();
        currPiece->setPosition(endCoordinates.first, endCoordinates.second);

        std::cout << "Move executed successfully from (" << start.getCoordinates().first << ", "
                  << start.getCoordinates().second << ") to (" << end.getCoordinates().first << ", "
                  << end.getCoordinates().second << ")" << std::endl;
    } else {
        std::cout << "Move execution failed, move is not valid." << std::endl;
    }
}



Color Player::getColor() {
    return color;
}

bool Player::hasNoPieces() { return pieces.empty(); }

void Player::printPieces() {
    for (const auto& it : pieces) {
        std::cout << it << std:: endl;
    }
}
