#include "Bishop.h"

std::vector<std::pair<int, int>> Bishop::getValidMove(std::shared_ptr<Piece> chessBoard[8][8]) {
    std::vector<std::pair<int, int>> validTiles;
    getValidMoveInLine(chessBoard, 1, 1, validTiles);
    getValidMoveInLine(chessBoard, 1, -1, validTiles);
    getValidMoveInLine(chessBoard, -1, 1, validTiles);
    getValidMoveInLine(chessBoard, -1, -1, validTiles);
    return validTiles;
}

bool Bishop::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
    int deltaX = toVerifyXPos - xPos_;
    int deltaY = toVerifyYPos - yPos_;

    if (std::abs(deltaX) != std::abs(deltaY)) {
        return false;
    }

    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }
    return canMoveInDiagonal(chessBoard, toVerifyXPos, toVerifyYPos);
}