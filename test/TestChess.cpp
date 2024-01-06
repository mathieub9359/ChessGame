#include "../src/ChessWindow.h"
#include "../src/PromotionController.h"


#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif

#ifdef TEST

TEST(king, validMove) {
	using namespace Model;
	BoardController::createKingPiece(4, 4, true);

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 4, 3)) << "The king is not able to move one upward.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 4, 5)) << "The king is not able to move one downward.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 1, 0)) << "The king is able to move to an illegal tile.";
	
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 5, 3)) << "The king is not able to move one to the left.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 4, 5)) << "The king is not able to move one to the right.";

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 5, 5)) << "The king is not able to move one in diagonal.";

	BoardController::createPawnPiece(4, 3, true);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 4, 3)) << "The king is able to move to an ally tile.";

	BoardController::createPawnPiece(4, 5, false);

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 4, 5)) << "The king is not able move on a ennemy tile.";

	BoardController::removePiece(4, 4); // Remove the king
	BoardController::removePiece(4, 3); // Remove the white pawn
	BoardController::removePiece(4, 5); //Remove the black pawn
	BoardController::cleanUp();
}

TEST(queen, validMove) {
	using namespace Model;
	BoardController::createQueenPiece(4, 4, true);

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 4, 0)) << "The queen is not able to move in an empty vertical line.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 0, 4)) << "The queen is not able to move in an empty horizontal line.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 0, 0)) << "The queen is not able to move in an empty diagonal line.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 1, 0)) << "The queen is able to move to an illegal tile.";

	BoardController::createPawnPiece(4, 2, true);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 4, 0)) << "The queen is able to pass through ally pieces in a straight line.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 4, 2)) << "The queen is able to move to an ally tile.";

	BoardController::createPawnPiece(2, 2, true);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 4, 0)) << "The queen is able to pass through ally pieces in a diagonal line.";

	BoardController::createPawnPiece(2, 4, false);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 0, 4)) << "The queen is able to pass through ennemy pieces in a straight line.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 2, 4)) << "The queen is not able move on a ennemy tile.";

	BoardController::createPawnPiece(6, 6, false);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 7, 7)) << "The queen is able to pass through ennemy pieces in a diagonal line.";

	BoardController::removePiece(4, 4); // Remove the queen
	BoardController::removePiece(4, 2); // Remove the fisrt white pawn
	BoardController::removePiece(2, 2); // Remove the second white pawn
	BoardController::removePiece(2, 4); //Remove the black pawn
	BoardController::removePiece(6, 6);
	BoardController::cleanUp();
}

TEST(rook, validMove) {
	using namespace Model;
	BoardController::createRookPiece(4, 4, true);

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 4, 0)) << "The rook is not able to move in an empty vertical line.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 0, 4)) << "The rook is not able to move in an empty horizontal line.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 0, 0)) << "The rook is able to move to an illegal tile.";

	BoardController::createPawnPiece(4, 2, true);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 4, 0)) << "The rook is able to pass through ally pieces in a straight line.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 4, 2)) << "The rook is able to move to an ally tile.";

	BoardController::createPawnPiece(2, 4, false);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 0, 4)) << "The rook is able to pass through ennemy pieces in a straight line.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 2, 4)) << "The rook is not able move on a ennemy tile.";

	BoardController::removePiece(4, 4); // Remove the rook
	BoardController::removePiece(4, 2); // Remove the white pawn
	BoardController::removePiece(2, 4); //Remove the black pawn
	BoardController::cleanUp();
}

TEST(bishop, validMove) {
	using namespace Model;
	BoardController::createBishopPiece(4, 4, true);

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 2, 2)) << "The bishop is not able to move in an empty vertical line.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 6, 0)) << "The bishop is able to move to an illegal tile.";

	BoardController::createPawnPiece(3, 5, true);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 1, 7)) << "The bishop is able to pass through ally pieces.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 3, 5)) << "The bishop is able to move to an ally tile.";

	BoardController::createPawnPiece(6, 2, false);

	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 7, 1)) << "The bishop is able to pass through ennemy pieces.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 6, 2)) << "The bishop is not able move on a ennemy tile.";

	BoardController::removePiece(4, 4); // Remove the bishop
	BoardController::removePiece(3, 5); // Remove the white pawn
	BoardController::removePiece(6, 2); // Remove the black pawn
	BoardController::cleanUp();
}

TEST(knight, validMove) {
	using namespace Model;
	BoardController::createKnightPiece(4, 4, true);

	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 5, 2)) << "The knight is not able to make a simple movement on an empty and legal square.";

	BoardController::createPawnPiece(5, 2, true);
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 5, 2)) << "The knight is able to move on an ally tile.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 4, 6, 6)) << "The knight is able to move too far away.";

	BoardController::createPawnPiece(3, 2, false);
	EXPECT_TRUE(BoardController::checkValidMove(4, 4, 3, 2)) << "The knight is not able to capture an enemy piece";


	BoardController::removePiece(4, 4); // Remove the knight
	BoardController::removePiece(5, 2); // Remove the white pawn
	BoardController::removePiece(3, 2); //Remove the black pawn
	BoardController::cleanUp();
}

TEST(pawn, validMove) {
	using namespace Model;
	BoardController::createPawnPiece(4, 6, true);

	EXPECT_TRUE(BoardController::checkValidMove(4, 6, 4, 5)) << "The white pawn is not able to move one empty tile foward.";
	EXPECT_TRUE(BoardController::checkValidMove(4, 6, 4, 4)) << "The white pawn is not able to move two empty tiles foward.";

	BoardController::createPawnPiece(3, 1, false);

	EXPECT_TRUE(BoardController::checkValidMove(3, 1, 3, 2)) << "The black pawn is not able to move one empty tile foward.";
	EXPECT_TRUE(BoardController::checkValidMove(3, 1, 3, 3)) << "The black pawn is not able to move two empty tiles foward.";

	BoardController::createPawnPiece(4, 5, true);

	EXPECT_FALSE(BoardController::checkValidMove(4, 6, 4, 5)) << "The pawn is able to move up one foward into a tile with a piece.";
	EXPECT_FALSE(BoardController::checkValidMove(4, 6, 4, 4)) << "The pawn is able to move up two foward through a piece.";

	BoardController::createBishopPiece(4, 2, true);

	EXPECT_TRUE(BoardController::checkValidMove(3, 1, 4, 2)) << "The pawn is not able to capture a enemy piece diagonally.";

	BoardController::createBishopPiece(2, 2, false);

	EXPECT_FALSE(BoardController::checkValidMove(3, 1, 2, 2)) << "The pawn is able to capture a ally piece diagonally.";

	BoardController::movePieceTo(3, 1, 3, 2);

	EXPECT_FALSE(BoardController::checkValidMove(3, 2, 3, 4)) << "The pawn is able to move two tiles foward even after moving.";

	BoardController::removePiece(4, 6); // Remove the white test pawn
	BoardController::removePiece(3, 2); // Remove the black test pawn
	BoardController::removePiece(4, 5); // Remove the third pawn
	BoardController::removePiece(4, 2); // Remove the white bishop
	BoardController::removePiece(2, 2); // Remove the black bishop

	BoardController::cleanUp();
}

TEST(kingCheck, checked) {
	using namespace Model;
	BoardController::createKingPiece(4, 4, true);

	BoardController::createRookPiece(4, 7, false);

	EXPECT_TRUE(BoardController::isChecked()) << "The king isn't being checked properly.";

	BoardController::removePiece(4, 4); //Remove the rook
	BoardController::removePiece(4, 7); //Remove the king

	BoardController::cleanUp();
}

TEST(kingCheck, pinned) {
	using namespace Model;
	BoardController::createKingPiece(4, 4, true);

	BoardController::createRookPiece(4, 3, true);

	BoardController::createQueenPiece(4, 0, false);

	EXPECT_TRUE(BoardController::willBeChecked(4, 3, 0, 3)) << "A piece can move, even if it is pinned.";

	EXPECT_FALSE(BoardController::willBeChecked(4, 3, 4, 0)) << "A pinned piece cannot eat the attacking piece to remove the pin.";

	BoardController::removePiece(4, 4); // Remove the king
	BoardController::removePiece(4, 3); // Remove the rook
	BoardController::removePiece(4, 0); // Remove the queen

	BoardController::cleanUp();
}

TEST(kingCheck, kingMoveIntoCheck) {
	using namespace Model;
	BoardController::createKingPiece(4, 4, true);

	BoardController::createQueenPiece(3, 0, false);

	EXPECT_TRUE(BoardController::willBeChecked(4, 4, 3, 4)) << "The king can move into a position that would put him in check.";

	BoardController::removePiece(4, 4); // Remove the king
	BoardController::removePiece(3, 0); // Remove the queen

	BoardController::cleanUp();
}

#endif