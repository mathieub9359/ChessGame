/**
La classe `Knight` est une classe enfant qui défint les mouvements valides d'un cavalier.

ficher      Piece.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/

#include "Knight.h"

std::vector<std::pair<int, int>> Knight::getValidMove(std::shared_ptr<Piece> chessBoard[8][8]) {
    std::vector<std::pair<int, int>> validTiles;
    std::pair<int, int> possibleKnightMove[8] = {
        std::pair<int, int>(xPos_ - 1, yPos_ - 2),
        std::pair<int, int>(xPos_ + 1, yPos_ - 2),
        std::pair<int, int>(xPos_ - 1, yPos_ + 2),
        std::pair<int, int>(xPos_ + 1, yPos_ + 2),
        std::pair<int, int>(xPos_ + 2, yPos_ - 1),
        std::pair<int, int>(xPos_ + 2, yPos_ + 1),
        std::pair<int, int>(xPos_ - 2, yPos_ - 1),
        std::pair<int, int>(xPos_ - 2, yPos_ + 1),
    };

    for (std::pair<int, int> possiblePos : possibleKnightMove) {
        if (possiblePos.first < 0 || possiblePos.second < 0 || possiblePos.first >= 8 || possiblePos.second >= 8) {
            continue;
        }
        else if (isValidMove(chessBoard, possiblePos.first, possiblePos.second) && (!Model::BoardController::willBeChecked(xPos_, yPos_, possiblePos.first, possiblePos.second))) {
            validTiles.push_back(possiblePos);
        }
    }
    return validTiles;
}

bool Knight::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {

    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }

    bool isVerticalL = (std::abs(toVerifyXPos - xPos_) == 1) && (std::abs(toVerifyYPos - yPos_) == 2);
    bool isHorizontalL = (std::abs(toVerifyXPos - xPos_) == 2) && (std::abs(toVerifyYPos - yPos_) == 1);

    if (isVerticalL || isHorizontalL) {
        return true;
    }
    return false;
}