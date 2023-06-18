/**
La classe `PawnPromotion` permet de g�r� la logic lorsqu'un pion arrive au bout de l'�chiquier afin de devenir une dame.

ficher      ChessWindow.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Cr�� le     1 mai 2023
**/
#include "PromotionControler.h"

void PawnPromotion::linkGui(GUI::ChessWindow& chessWindow) {
	chessWindow_ = &chessWindow;
}

void PawnPromotion::promotionProcessus(int pawnXPos, int pawnYPos, int promotionXPos, int promotionYPos, bool pawnIsWhite) {
	Model::BoardController::removePiece(pawnXPos, pawnYPos);
	chessWindow_->createQueen(promotionXPos, promotionYPos, pawnIsWhite);
}

