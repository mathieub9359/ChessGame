#pragma once

#include "Pieces.h"
#include "Board.h"
#include <exception> 

class King : public Piece {
public:
	King(const int xPos, const int yPos, const bool isWhite) :Piece(xPos, yPos, isWhite) {
		if (nbOfKings_ >= 2) {
			throw std::runtime_error("Too many kings created");
		}
		nbOfKings_++;
	}
	bool isValidMove(std::shared_ptr<Piece> chessBord[8][8], const int toVerifYPos, const int toVerifXPos) const override;

	std::vector<std::pair<int, int>> getValidMove(std::shared_ptr<Piece> chessBord[8][8]) override;

	std::pair<int, int> getKingPosition();

	~King() {
		nbOfKings_--;
	}

private:
	static int nbOfKings_;
};