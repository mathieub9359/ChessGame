#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <qgridlayout.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <iostream>
#include <qtimer.h>
#include <vector>
#include <QDir>
class Piece;

#include "Board.h"
namespace GUI {

	class ChessWindow : public QMainWindow {
		Q_OBJECT

	public:
		ChessWindow(QWidget* parent = nullptr);
		~ChessWindow() override = default;

		void createKing(const int xPos, const int yPos, bool isWhite);
		void createPawn(const int xPos, const int yPos, bool isWhite);
		void createKnight(const int xPos, const int yPos, bool isWhite);
		void createBishop(const int xPos, const int yPos, bool isWhite);
		void createRook(const int xPos, const int yPos, bool isWhite);
		void createQueen(const int xPos, const int yPos, bool isWhite);

		void preparePieces();

	private slots:
		void handleButtonClick();
		void handleResetAction();

	private:
		
		void resetTileColors();
		void selectedButtonProcess(QPushButton*& selectedButton, QPushButton* clickedButton, int clickedCol, int clickedRow);
		void validateMoveProcess(QPushButton* clickedButton, int selectedCol, int selectedRow, int clickedCol, int clickedRow);
		
		void resetBoard();

		void getButtonPosition(QPushButton* currButton, int& buttonCol, int& buttonRow) {
			int buttonIndex = gridLayout->indexOf(currButton);

			int selectedRowSpan, selectedColSpan = 1;

			gridLayout->getItemPosition(buttonIndex, &buttonRow, &buttonCol, &selectedRowSpan, &selectedColSpan);
		}

		bool gameHasEnded_ = false;

		QPushButton* buttonSquares[8][8];
		
		QComboBox* endGameSelector_;
		QLabel* turnLabel_;
		QPushButton* resetButton_;

		QLabel* checkMateLabel_;
		QLabel* staleMateLabel_;
		QLabel* invalidMoveLabel_;

		QLabel* checkedLabel_;
		QPushButton* selectedButton;
		QGridLayout* gridLayout;
	};
}
