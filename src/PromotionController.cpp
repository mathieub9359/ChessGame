#include "PromotionController.h"

GUI::ChessWindow* PawnPromotion::chessWindow_ = nullptr;

void PawnPromotion::linkGui(GUI::ChessWindow& chessWindow) {
	chessWindow_ = &chessWindow;
}

void PawnPromotion::promotionProcessus(int pawnXPos, int pawnYPos, int promotionXPos, int promotionYPos, bool pawnIsWhite) {
	Model::BoardController::removePiece(pawnXPos, pawnYPos);
	chessWindow_->createQueen(promotionXPos, promotionYPos, pawnIsWhite);
}

