
#pragma once

#include "Pieces.h"
#include "Board.h"

class Pawn : public Piece {
public:
	Pawn(const int xPos, const int yPos, const bool isWhite) :Piece(xPos, yPos, isWhite) {}

	bool isValidMove(std::shared_ptr<Piece> chessBord[8][8], const int toVerifyXPos, const int toVerifyYPos) const override;

	std::vector<std::pair<int, int>> getValidMove(std::shared_ptr<Piece> chessBord[8][8]) override;

	void move(std::shared_ptr<Piece> chessBoard[8][8], const int newYPos, const int newXPos) override;
};