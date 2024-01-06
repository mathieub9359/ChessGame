#include "Queen.h"

bool Queen::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }

    int deltaX = toVerifyXPos - xPos_;
    int deltaY = toVerifyYPos - yPos_;

    if (abs(deltaX) == abs(deltaY)) {
        return canMoveInDiagonal(chessBoard, toVerifyXPos, toVerifyYPos);
    }
    else if (xPos_ == toVerifyXPos || yPos_ == toVerifyYPos) {
        return canMoveSideway(chessBoard, toVerifyXPos, toVerifyYPos);
    }
    return false;
}

std::vector<std::pair<int, int>> Queen::getValidMove(std::shared_ptr<Piece> chessBoard[8][8]) {
    std::vector<std::pair<int, int>> validTiles;
    getValidMoveInLine(chessBoard, 1, 1, validTiles);
    getValidMoveInLine(chessBoard, 1, -1, validTiles);
    getValidMoveInLine(chessBoard, -1, 1, validTiles);
    getValidMoveInLine(chessBoard, -1, -1, validTiles);
    getValidMoveInLine(chessBoard, 1, 0, validTiles);
    getValidMoveInLine(chessBoard, -1, 0, validTiles);
    getValidMoveInLine(chessBoard, 0, 1, validTiles);
    getValidMoveInLine(chessBoard, 0, -1, validTiles);
    return validTiles;
}