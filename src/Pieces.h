#pragma once

#include <utility>
#include <vector>
#include <memory>

class Piece {
public:
	virtual bool isValidMove(std::shared_ptr<Piece> chessBord[8][8], const int toVerifYPos, const int toVerifXPos) const = 0;

	virtual std::vector<std::pair<int, int>> getValidMove(std::shared_ptr<Piece> chessBord[8][8]) = 0;

	virtual void move(std::shared_ptr<Piece> chessBoard[8][8], const int newYPos, const int newXPos);

	void temporaryMove(std::shared_ptr<Piece> chessBoard[8][8], const int newYPos, const int newXPos);

	bool isTheSameColor(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const;

	virtual ~Piece() = default;

	Piece(const int xPos, const int yPos, const bool isWhite);

	bool getIsWhite();

protected:
	bool canMoveInDiagonal(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const;
	bool canMoveSideway(std::shared_ptr<Piece> chessBoard[8][8], const int toVerifyXPos, const int toVerifyYPos) const;
	void getValidMoveInLine(std::shared_ptr<Piece> chessBoard[8][8], const int xVariation, const int yVariation, std::vector<std::pair<int, int>>& validTiles);
	
	bool hasMoved_;
	int xPos_ = 0;
	int yPos_ = 0;
	bool isWhite_ = false;
	
};
