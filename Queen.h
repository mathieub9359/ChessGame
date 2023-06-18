#pragma once

#include "Pieces.h"

class Queen : public Piece {
public:
	Queen(const int xPos, const int yPos, const bool isWhite) :Piece(xPos, yPos, isWhite) {}

	bool isValidMove(std::shared_ptr<Piece> chessBord[8][8], const int toVerifYPos, const int toVerifXPos) const override;

	std::vector<std::pair<int, int>> getValidMove(std::shared_ptr<Piece> chessBord[8][8]) override;
};