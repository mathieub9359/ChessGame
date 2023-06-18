/**
La classe `King` est une classe enfant qui défint les mouvements valides d'un roi.

ficher      Piece.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/
#include "King.h"

std::pair<int, int> King::getKingPosition() {
    return std::pair<int, int>(xPos_, yPos_);
}

bool King::isValidMove(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const {
	if (std::abs(toVerifyXPos - xPos_) > 1 || std::abs(toVerifyYPos - yPos_) > 1) {
		return false;
	}
	if (isTheSameColor(chessBoard, toVerifyXPos, toVerifyYPos)) {
		return false;
	}
	return true;
}

std::vector<std::pair<int, int>> King::getValidMove(std::shared_ptr<Piece> chessBoard[8][8]) {
	std::vector<std::pair<int, int>> validTiles;
	for (int xVariation = -1; xVariation <= 1; xVariation++) {
		for (int yVariation = -1; yVariation <= 1; yVariation++) {

			if (xVariation == 0 && yVariation == 0) {
				continue;
			}

			int toVerifyXPos = xPos_ + xVariation;
			int toVerifyYPos = yPos_ + yVariation;

			if ((toVerifyXPos >= 8 || toVerifyXPos < 0) ||
				(toVerifyYPos >= 8 || toVerifyYPos < 0)) {
				continue;
			}

			if (!Model::BoardController::willBeChecked(xPos_, yPos_, toVerifyXPos, toVerifyYPos) && isValidMove(chessBoard, toVerifyXPos, toVerifyYPos)) {
				validTiles.push_back(std::pair<int, int>(toVerifyXPos, toVerifyYPos));
			}
		}
	}
	return validTiles;
}