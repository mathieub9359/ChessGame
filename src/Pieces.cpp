#include "Pieces.h"
#include <iostream>
#include "Board.h"

bool Piece::getIsWhite() {
	return isWhite_;
}

Piece::Piece(const int xPos, const int yPos, const bool isWhite) {
    xPos_ = xPos;
    yPos_ = yPos;
    isWhite_ = isWhite;
    hasMoved_ = false;
}

void Piece::move(std::shared_ptr<Piece> chessBoard[8][8], const int newXPos, const int newYPos) {
    chessBoard[newXPos][newYPos] = chessBoard[xPos_][yPos_];
    chessBoard[xPos_][yPos_] = nullptr;

    xPos_ = newXPos;
    yPos_ = newYPos;
    hasMoved_ = true;
}

void Piece::temporaryMove(std::shared_ptr<Piece> chessBoard[8][8], const int newXPos, const int newYPos) {
    chessBoard[newXPos][newYPos] = chessBoard[xPos_][yPos_];
    chessBoard[xPos_][yPos_] = nullptr;

    xPos_ = newXPos;
    yPos_ = newYPos;
}

bool Piece::isTheSameColor(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
    return (chessBoard[toVerifyXPos][toVerifyYPos] != nullptr && chessBoard[toVerifyXPos][toVerifyYPos]->getIsWhite() == isWhite_);
}

bool Piece::canMoveInDiagonal(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
    int deltaX = toVerifyXPos - xPos_;
    int deltaY = toVerifyYPos - yPos_;

    int deltaDirectionX = deltaX > 0 ? 1 : -1;
    int deltaDirectionY = deltaY > 0 ? 1 : -1;

    int currentPosX = xPos_ + deltaDirectionX;
    int currentPosY = yPos_ + deltaDirectionY;


    while (currentPosX != toVerifyXPos && currentPosY != toVerifyYPos) {
        if (chessBoard[currentPosX][currentPosY] != nullptr) {
            return false;
        }

        currentPosX += deltaDirectionX;
        currentPosY += deltaDirectionY;

    }
    return true;
}

bool Piece::canMoveSideway(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
    int deltaX = toVerifyXPos - xPos_;
    int deltaY = toVerifyYPos - yPos_;

    if (xPos_ == toVerifyXPos) {
        int deltaDirectionY = deltaY > 0 ? 1 : -1;
        int currentPosY = yPos_ + deltaDirectionY;
        while (currentPosY != toVerifyYPos) {
            if (chessBoard[xPos_][currentPosY] != nullptr) {
                return false;
            }
            currentPosY += deltaDirectionY;
        }
    }

    else {
        int deltaDirectionX = deltaX > 0 ? 1 : -1;
        int currentPosX = xPos_ + deltaDirectionX;
        while (currentPosX != toVerifyXPos) {
            if (chessBoard[currentPosX][yPos_] != nullptr) {
                return false;
            }
            currentPosX += deltaDirectionX;
        }
    }
    return true;
}

void Piece::getValidMoveInLine(std::shared_ptr<Piece> chessBoard[8][8], const int xVariation, const int yVariation, std::vector<std::pair<int, int>>& validTiles) {
    int toVerifyXPos = xPos_ + xVariation;
    int toVerifyYPos = yPos_ + yVariation;
    for (; toVerifyXPos < 8 && toVerifyYPos < 8 && toVerifyXPos >= 0 && toVerifyYPos >= 0; toVerifyXPos += xVariation, toVerifyYPos += yVariation) {
        if (!isValidMove(chessBoard, toVerifyXPos, toVerifyYPos)) {
            break;
        }
        else if (!Model::BoardController::willBeChecked(xPos_, yPos_, toVerifyXPos, toVerifyYPos)) {
            validTiles.push_back(std::pair<int, int>(toVerifyXPos, toVerifyYPos));
        }
    }
}
