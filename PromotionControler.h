#pragma once

#include "ChessWindow.h"

class PawnPromotion {
public:
	static void promotionProcessus(int pawnXPos, int pawnYPos, int promotionXPos, int promotionYPos, bool pawnIsWhite);
	static void linkGui(GUI::ChessWindow& chessWindow);

private:
	static GUI::ChessWindow* chessWindow_;
};