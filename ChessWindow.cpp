/**
La classe `ChessWindow` permet de géré l'affichage de l'échecier ainsi que les difféntes piece.
La classe s'occupe aussi de capter les actions du joueur et de l'envoyer a `BoardController` qui fait la logic.

ficher      ChessWindow.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     9 avril 2023
**/


#include "ChessWindow.h"
#include <cmath>
#include <iostream>

class BoardController;

GUI::ChessWindow::ChessWindow(QWidget* parent) : QMainWindow(parent), selectedButton(nullptr) {
	QWidget* centralWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QWidget* topWidget = new QWidget;
    QHBoxLayout* topLayout = new QHBoxLayout(topWidget);

    turnLabel_ = new QLabel("White's turn", this);
    topLayout->addWidget(turnLabel_);


    endGameSelector_ = new QComboBox();
    endGameSelector_->addItem("Normal Game");
    endGameSelector_->addItem("Karpov vs. Kasparov, Tilburg, 1991");
    endGameSelector_->addItem("Pachman vs. Guimard, 1955");
    topLayout->addWidget(endGameSelector_);

    resetButton_ = new QPushButton();
    resetButton_->setText("Reset");
    connect(resetButton_, &QPushButton::clicked, this, &ChessWindow::handleResetAction);
    topLayout->addWidget(resetButton_);

    mainLayout->addWidget(topWidget);

    gridLayout = new QGridLayout;

    Model::BoardController::initalizePieceBoard();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            buttonSquares[col][row] = new QPushButton;
            QPushButton* button = buttonSquares[col][row];


            button->setFixedSize(75, 75);
            connect(button, &QPushButton::clicked, this, &ChessWindow::handleButtonClick); 


            if ((row+col) % 2 == 0) {
                button->setStyleSheet("background-color: rgb(255,206,158);");
            }
            else {
                button->setStyleSheet("background-color: rgb(209,139,71);");
            }

            gridLayout->addWidget(button, row, col);
        }
    }
    mainLayout->addLayout(gridLayout);
    centralWidget->setFixedSize(600, 600);
    setCentralWidget(centralWidget);

    invalidMoveLabel_ = new QLabel("Invalid move!", this);
    invalidMoveLabel_->setAlignment(Qt::AlignCenter);
    invalidMoveLabel_->setGeometry(230, 280, 150, 20);
    invalidMoveLabel_->setStyleSheet("QLabel {color : red; font-size : 24px}");
    invalidMoveLabel_->setVisible(false);

    checkedLabel_ = new QLabel("You are checked!", this);
    checkedLabel_->setAlignment(Qt::AlignCenter);
    checkedLabel_->setGeometry(200, 280, 200, 20);
    checkedLabel_->setStyleSheet("QLabel {color : red; font-size : 24px}");
    checkedLabel_->setVisible(false);

    checkMateLabel_ = new QLabel("Check Mate!", this);
    checkMateLabel_->setAlignment(Qt::AlignCenter);
    checkMateLabel_->setGeometry(200, 280, 200, 20);
    checkMateLabel_->setStyleSheet("QLabel {color : green; font-size : 24px}");
    checkMateLabel_->setVisible(false);

    staleMateLabel_ = new QLabel("Stale Mate!", this);
    staleMateLabel_->setAlignment(Qt::AlignCenter);
    staleMateLabel_->setGeometry(200, 280, 200, 20);
    staleMateLabel_->setStyleSheet("QLabel {color : green; font-size : 24px}");
    staleMateLabel_->setVisible(false);
}

void GUI::ChessWindow::preparePieces() {
     createKing(4, 7, true);
     createQueen(3, 7, true);
     createRook(7, 7, true);
     createRook(0, 7, true);
     createBishop(2, 7, true);
     createBishop(5, 7, true);
     createKnight(6, 7, true);
     createKnight(1, 7, true);

     for (int i = 0; i < 8; i++) {
         createPawn(i, 6, true);
         createPawn(i, 1, false);
     }

     createKing(4, 0, false);
     createQueen(3, 0, false);
     createRook(7, 0, false);
     createRook(0, 0, false);
     createBishop(2, 0, false);
     createBishop(5, 0, false);
     createKnight(6, 0, false);
     createKnight(1, 0, false);
}

void GUI::ChessWindow::createKing(const int xPos, const int yPos, bool isWhite) {
    try {
        Model::BoardController::createKingPiece(xPos, yPos, isWhite);

        if (isWhite) {
            buttonSquares[xPos][yPos]->setIcon(QIcon("white_king.png"));
        }
        else {
            buttonSquares[xPos][yPos]->setIcon(QIcon("black_king.png"));
        }
        buttonSquares[xPos][yPos]->setIconSize(QSize(60,60));
    }
    catch(std::exception& e) {
        std::cout << "Error: " << e.what();
    }
}

void GUI::ChessWindow::createQueen(const int xPos, const int yPos, bool isWhite) {
    Model::BoardController::createQueenPiece(xPos, yPos, isWhite);

    if (isWhite) {
        buttonSquares[xPos][yPos]->setIcon(QIcon("white_queen.png"));
    }
    else {
        buttonSquares[xPos][yPos]->setIcon(QIcon("black_queen.png"));
    }

    buttonSquares[xPos][yPos]->setIconSize(QSize(60, 60));
}

void GUI::ChessWindow::createRook(const int xPos, const int yPos, bool isWhite) {
    Model::BoardController::createRookPiece(xPos, yPos, isWhite);

    if (isWhite) {
        buttonSquares[xPos][yPos]->setIcon(QIcon("white_rook.png"));
    }
    else {
        buttonSquares[xPos][yPos]->setIcon(QIcon("black_rook.png"));
    }

    buttonSquares[xPos][yPos]->setIconSize(QSize(60, 60));
}

void GUI::ChessWindow::createBishop(const int xPos, const int yPos, bool isWhite) {
    Model::BoardController::createBishopPiece(xPos, yPos, isWhite);

    if (isWhite) {
        buttonSquares[xPos][yPos]->setIcon(QIcon("white_bishop.png"));
    }
    else {
        buttonSquares[xPos][yPos]->setIcon(QIcon("black_bishop.png"));
    }

    buttonSquares[xPos][yPos]->setIconSize(QSize(60, 60));
}

void GUI::ChessWindow::createPawn(const int xPos, const int yPos, bool isWhite) {
    Model::BoardController::createPawnPiece(xPos, yPos, isWhite);

    if (isWhite) {
        buttonSquares[xPos][yPos]->setIcon(QIcon("white_pawn.png"));
    }
    else {
        buttonSquares[xPos][yPos]->setIcon(QIcon("black_pawn.png"));
    }

    buttonSquares[xPos][yPos]->setIconSize(QSize(60, 60));
}

void GUI::ChessWindow::createKnight(const int xPos, const int yPos, bool isWhite) {
    Model::BoardController::createKnightPiece(xPos, yPos, isWhite);

    if (isWhite) {
        buttonSquares[xPos][yPos]->setIcon(QIcon("white_knight.png"));
    }
    else {
        buttonSquares[xPos][yPos]->setIcon(QIcon("black_knight.png"));
    }

    buttonSquares[xPos][yPos]->setIconSize(QSize(60, 60));
}


void GUI::ChessWindow::resetBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            buttonSquares[i][j]->setIcon(QIcon());
        }
    }
    Model::BoardController::resetBoard();
}

void GUI::ChessWindow::handleResetAction() {
    resetBoard();
    resetTileColors();
    gameHasEnded_ = false;
    staleMateLabel_->hide();
    checkMateLabel_->hide();

    QString selectedEndGame = endGameSelector_->currentText();
    if (selectedEndGame == "Normal Game") {
        Model::BoardController::setIsWhiteTurn(true);
        turnLabel_->setText("White's turn");
        preparePieces();
    }
    else if (selectedEndGame == "Karpov vs. Kasparov, Tilburg, 1991") {
        Model::BoardController::setIsWhiteTurn(false);
        turnLabel_->setText("Black's turn");
        createKing(7, 4, true);
        createBishop(2, 2, true);
        createKnight(3, 5, true);
        createKnight(5, 4, true);

        createKing(5, 2, false);
        createRook(3, 0, false);
    }
    else if (selectedEndGame == "Pachman vs. Guimard, 1955") {
        Model::BoardController::setIsWhiteTurn(false);
        turnLabel_->setText("Black's turn");
        createKing(4, 4, true);
        createKnight(3, 4, true);
        createBishop(4, 5, true);

        createKing(3, 1, false);
        createQueen(0, 7, false);
    }
}

void GUI::ChessWindow::resetTileColors() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) {
                buttonSquares[row][col]->setStyleSheet("background-color: rgb(255,206,158);");
            }
            else {
                buttonSquares[row][col]->setStyleSheet("background-color: rgb(209,139,71);");
            }
        }
    }
}

void GUI::ChessWindow::selectedButtonProcess(QPushButton*& selectedButton, QPushButton* clickedButton,  int clickedCol, int clickedRow) {
    if (Model::BoardController::squareHasAPiece(clickedCol, clickedRow) &&
        Model::BoardController::pieceIsWhite(clickedCol, clickedRow) == Model::BoardController::getIsWhiteTurn()) {
        selectedButton = clickedButton;

        std::vector<std::pair<int, int>> validMoveTiles = Model::BoardController::getValidMove(clickedCol, clickedRow);
        for (std::pair<int, int> validMoveTile : validMoveTiles) {
            if (Model::BoardController::squareHasAPiece(validMoveTile.first, validMoveTile.second)) {
                buttonSquares[validMoveTile.first][validMoveTile.second]->setStyleSheet("background-color: rgb(214,11,45);");
            }
            else {
                buttonSquares[validMoveTile.first][validMoveTile.second]->setStyleSheet("background-color: rgb(154, 186, 86);");
            }
        }
        return;
    }
    return;
}

void GUI::ChessWindow::validateMoveProcess(QPushButton* clickedButton, int selectedCol, int selectedRow, int clickedCol, int clickedRow) {
    bool isValidTurn = Model::BoardController::checkValidTurn(selectedCol, selectedRow);
    bool isValidButton = clickedButton != selectedButton;
    bool isValidMove = Model::BoardController::checkValidMove(selectedCol, selectedRow, clickedCol, clickedRow);

    if (gameHasEnded_) {

    }
    else if (!(isValidTurn && isValidButton && isValidMove)) {
        invalidMoveLabel_->setVisible(true);
        QTimer::singleShot(2000, invalidMoveLabel_, &QWidget::hide);

    }
    else if (Model::BoardController::willBeChecked(selectedCol, selectedRow, clickedCol, clickedRow)) {
        checkedLabel_->setVisible(true);
        QTimer::singleShot(2000, checkedLabel_, &QWidget::hide);
    }
    else {
        clickedButton->setIcon(selectedButton->icon());
        clickedButton->setIconSize(selectedButton->size());
        selectedButton->setIcon(QIcon());
        
        Model::BoardController::movePieceTo(selectedCol, selectedRow, clickedCol, clickedRow);
        
        Model::BoardController::swapTurn();

        if (!Model::BoardController::hasAValidMove()) {
            if (Model::BoardController::isChecked()) {
                checkMateLabel_->setVisible(true);
                gameHasEnded_ = true;
            }
            else {
                staleMateLabel_->setVisible(true);
                gameHasEnded_ = true;
            }
        }

        if (Model::BoardController::getIsWhiteTurn()) {
            turnLabel_->setText("White's turn");
        }
        else {
            turnLabel_->setText("Black's turn");
        }
    }

    if (Model::BoardController::isChecked()) {
        std::pair<int, int> kingPos = Model::BoardController::findKing()->getKingPosition();
        buttonSquares[kingPos.first][kingPos.second]->setStyleSheet("background-color: rgb(214,11,45);");
    }
}

void GUI::ChessWindow::handleButtonClick() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    int clickedRow, clickedCol;
    getButtonPosition(clickedButton, clickedCol, clickedRow);

    if (selectedButton == nullptr) {
        selectedButtonProcess(selectedButton, clickedButton, clickedCol, clickedRow);
        return;
    }

    resetTileColors();
    
    if (Model::BoardController::squareHasAPiece(clickedCol, clickedRow) && 
        Model::BoardController::pieceIsWhite(clickedCol, clickedRow) == Model::BoardController::getIsWhiteTurn()) {
        selectedButtonProcess(selectedButton, clickedButton, clickedCol, clickedRow);
        return;
    }

    if (selectedButton->icon().isNull()) {
        selectedButton = nullptr;
        return;
    }

    int selectedRow, selectedCol;
    getButtonPosition(selectedButton, selectedCol, selectedRow);

    validateMoveProcess(clickedButton, selectedCol, selectedRow, clickedCol, clickedRow);

    if (Model::BoardController::isChecked()) {
        std::pair<int, int> kingPos = Model::BoardController::findKing()->getKingPosition();
        buttonSquares[kingPos.first][kingPos.second]->setStyleSheet("background-color: rgb(214,11,45);");
    }
     
    selectedButton = nullptr;
}
