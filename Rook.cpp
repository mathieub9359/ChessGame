/**
La classe `Rook` est une classe enfant qui défint les mouvements valides d'un tour.

ficher      Piece.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/
#include "Rook.h"

bool Rook::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {

    if (xPos_ != toVerifyXPos && yPos_ != toVerifyYPos) {
        return false;
    }

    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }

    return canMoveSideway(chessBoard, toVerifyXPos, toVerifyYPos);
}

std::vector<std::pair<int, int>> Rook::getValidMove(std::shared_ptr<Piece> chessBoard[8][8]) {
    std::vector<std::pair<int, int>> validTiles;
    getValidMoveInLine(chessBoard, 1, 0, validTiles);
    getValidMoveInLine(chessBoard, -1, 0, validTiles);
    getValidMoveInLine(chessBoard, 0, 1, validTiles);
    getValidMoveInLine(chessBoard, 0, -1, validTiles);
    return validTiles;
}