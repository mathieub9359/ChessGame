/**
La classe `Bishop` est une classe enfant qui défint les mouvements valides d'un fou.

ficher      Piece.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/
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

    if (abs(deltaX) != abs(deltaY)) {
        return false;
    }

    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }
    return canMoveInDiagonale(chessBoard, toVerifyXPos, toVerifyYPos);
}