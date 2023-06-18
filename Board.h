#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <stdexcept>
#include <exception>
#include "PiecesInclude.h"

class King;

class Piece;
namespace Model {
	class BoardController {
	public:
		static void createKingPiece(const int xPos, const int yPos, bool isWhite);
		static void createPawnPiece(const int xPos, const int yPos, bool isWhite);
		static void createKnightPiece(const int xPos, const int yPos, bool isWhite);
		static void createBishopPiece(const int xPos, const int yPos, bool isWhite);
		static void createRookPiece(const int xPos, const int yPos, bool isWhite);
		static void createQueenPiece(const int xPos, const int yPos, bool isWhite);
		static void initalizePieceBoard();

		static bool checkValidTurn(const int xPos, const int yPos);
		static bool checkValidMove(const int xPosOfPiece, const int yPosOfPiece, const int xPosToVerify, const int yPosToVerify);
		static std::vector<std::pair<int, int>> getValidMove(const int xPosOfPiece, const int yPosOfPiece);
		static bool squareHasAPiece(const int xPos, const int yPos);
		static bool pieceIsWhite(const int xPos, const int yPos);
		static bool isChecked();
		static bool willBeChecked(const int xPosOfPiece, const int yPosOfPiece, const int xPosToVerify, const int yPosToVerify);
		static bool hasAValidMove();
		static std::shared_ptr<King> findKing();

		static void movePieceTo(const int xPosOfPiece, const int yPosOfPiece, const int xPosToGo, const int yPosToGo);
		static void temporaryMoveTo(const int xPosOfPiece, const int yPosOfPiece, const int xPosToGo, const int yPosToGo);
		static void swapTurn();
		static bool getIsWhiteTurn();
		static void setIsWhiteTurn(bool isWhiteTurn);
		static void removePiece(const int xPos, const int yPos);
		

		static void resetBoard();

		static void cleanUp();

		//This method is for Google Testing purposes only.
		static bool isAQueen(const int xPos, const int yPos);
		

	private:
		static bool isWhiteTurn_;
		
		static std::shared_ptr<Piece> pieceSquares_[8][8];
		static std::vector<std::shared_ptr<Piece>> whitePieces_;
		static std::vector<std::shared_ptr<Piece>> blackPieces_;
	};
}


#endif
