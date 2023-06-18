/**
La classe `PawnPromotion` permet de géré la logic lorsqu'un pion arrive au bout de l'échiquier afin de devenir une dame.

ficher      ChessWindow.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     1 mai 2023
**/
#include "PromotionControler.h"

void PawnPromotion::linkGui(GUI::ChessWindow& chessWindow) {
	chessWindow_ = &chessWindow;
}

void PawnPromotion::promotionProcessus(int pawnXPos, int pawnYPos, int promotionXPos, int promotionYPos, bool pawnIsWhite) {
	Model::BoardController::removePiece(pawnXPos, pawnYPos);
	chessWindow_->createQueen(promotionXPos, promotionYPos, pawnIsWhite);
}

