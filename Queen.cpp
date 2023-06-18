/**
La classe `Queen` est une classe enfant qui défint les mouvements valides d'un dame.

ficher      Piece.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/
#include "Queen.h"

bool Queen::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }

    int deltaX = toVerifyXPos - xPos_;
    int deltaY = toVerifyYPos - yPos_;

    if (abs(deltaX) == abs(deltaY)) {
        return canMoveInDiagonale(chessBoard, toVerifyXPos, toVerifyYPos);
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