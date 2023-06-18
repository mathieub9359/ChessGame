/**
La classe `Pawn` est une classe enfant qui défint les mouvements valides d'un pion.

ficher      Piece.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/

#include "Pawn.h"
#include "PromotionControler.h"

class PawnPromotion;

void Pawn::move(std::shared_ptr<Piece> chessBoard[8][8], const int newXPos, const int newYPos) {
    if (newYPos == 0 && isWhite_) {
        PawnPromotion::promotionProcessus(xPos_, yPos_, newXPos, newYPos, isWhite_);
    }
    else if (newYPos == 7 && !isWhite_) {
        PawnPromotion::promotionProcessus(xPos_, yPos_, newXPos, newYPos, isWhite_);
    }
    else {
        Piece::move(chessBoard, newXPos, newYPos);
        return;
    }
    chessBoard[xPos_][yPos_] = nullptr;
}

bool Pawn::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {

    if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
        return false;
    }

    bool isOneUpwards;
    bool isTwoUpwards;

    if (isWhite_) {
        isOneUpwards = (yPos_ - toVerifyYPos == 1);
        isTwoUpwards = (yPos_ - toVerifyYPos == 2) && (chessBoard[xPos_][yPos_ - 1] == nullptr);
    }
    else {
        isOneUpwards = (toVerifyYPos - yPos_ == 1);
        isTwoUpwards = (toVerifyYPos - yPos_ == 2) && (chessBoard[xPos_][yPos_ + 1] == nullptr);
    }

    if (toVerifyXPos == xPos_ && (isOneUpwards || (isTwoUpwards && !hasMoved_))) {
        if (chessBoard[toVerifyXPos][toVerifyYPos] == nullptr) {
            return true;
        }
    }

    bool isDiagonal = std::abs(toVerifyXPos - xPos_) == 1 && isOneUpwards;

    if (isDiagonal && chessBoard[toVerifyXPos][toVerifyYPos] != nullptr) {
        return true;
    }

    return false;
}

std::vector<std::pair<int, int>> Pawn::getValidMove(std::shared_ptr<Piece> chessBoard[8][8]) {
    std::vector<std::pair<int, int>> validTiles;
    if (isWhite_) {
        for (int toVerifyXPos = -1; toVerifyXPos <= 1; toVerifyXPos++) {
            if (xPos_ + toVerifyXPos < 0 || xPos_ + toVerifyXPos >= 8) {
                continue;
            }
            else if (isValidMove(chessBoard, xPos_ + toVerifyXPos, yPos_ - 1) && (!Model::BoardController::willBeChecked(xPos_, yPos_, xPos_ + toVerifyXPos, yPos_ - 1))) {
                validTiles.push_back(std::pair<int, int>(toVerifyXPos + xPos_, yPos_ - 1));
            }
        }
        if (isValidMove(chessBoard, xPos_, yPos_ - 2) && !Model::BoardController::willBeChecked(xPos_, yPos_, xPos_, yPos_ - 2)) {
            validTiles.push_back(std::pair<int, int>(xPos_, yPos_ - 2));
        }
        return validTiles;
    }
    else {
        for (int toVerifyXPos = -1; toVerifyXPos <= 1; toVerifyXPos++) {
            if (xPos_ + toVerifyXPos < 0 || xPos_ + toVerifyXPos >= 8) {
                continue;
            }
            else if (isValidMove(chessBoard, xPos_ + toVerifyXPos, yPos_ + 1) && (!Model::BoardController::willBeChecked(xPos_, yPos_, xPos_ + toVerifyXPos, yPos_ + 1))) {
                validTiles.push_back(std::pair<int, int>(xPos_ + toVerifyXPos, yPos_ + 1));
            }
        }
        if (isValidMove(chessBoard, xPos_, yPos_ + 2) && !Model::BoardController::willBeChecked(xPos_, yPos_, xPos_, yPos_ + 2)) {
            validTiles.push_back(std::pair<int, int>(xPos_, yPos_ + 2));
        }
        return validTiles;
    }
}
