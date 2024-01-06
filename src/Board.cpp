#include "Board.h"
#include <iostream>
#include <memory>

bool Model::BoardController::isWhiteTurn_ = true;
std::shared_ptr<Piece> Model::BoardController::pieceSquares_[8][8];
std::vector<std::shared_ptr<Piece>> Model::BoardController::whitePieces_;
std::vector<std::shared_ptr<Piece>> Model::BoardController::blackPieces_;


void Model::BoardController::createKingPiece(const int xPos, const int yPos, bool isWhite) {
    auto newKing = std::make_shared<King>(xPos, yPos, isWhite);
    pieceSquares_[xPos][yPos] = newKing;

    if (isWhite) {
        whitePieces_.push_back(newKing);
    }
    else {
        blackPieces_.push_back(newKing);
    }
}

void Model::BoardController::createQueenPiece(const int xPos, const int yPos, bool isWhite) {
    pieceSquares_[xPos][yPos] = std::make_shared<Queen>(Queen(xPos, yPos, isWhite));

    if (isWhite) {
        whitePieces_.push_back(pieceSquares_[xPos][yPos]);
    }
    else {
        blackPieces_.push_back(pieceSquares_[xPos][yPos]);
    }
}

void Model::BoardController::createRookPiece(const int xPos, const int yPos, bool isWhite) {
    pieceSquares_[xPos][yPos] = std::make_shared<Rook>(Rook(xPos, yPos, isWhite));

    if (isWhite) {
        whitePieces_.push_back(pieceSquares_[xPos][yPos]);
    }
    else {
        blackPieces_.push_back(pieceSquares_[xPos][yPos]);
    }
}

void Model::BoardController::createBishopPiece(const int xPos, const int yPos, bool isWhite) {
    pieceSquares_[xPos][yPos] = std::make_shared<Bishop>(Bishop(xPos, yPos, isWhite));

    if (isWhite) {
        whitePieces_.push_back(pieceSquares_[xPos][yPos]);
    }
    else {
        blackPieces_.push_back(pieceSquares_[xPos][yPos]);
    }
}

void Model::BoardController::createKnightPiece(const int xPos, const int yPos, bool isWhite) {
    pieceSquares_[xPos][yPos] = std::make_shared<Knight>(Knight(xPos, yPos, isWhite));

    if (isWhite) {
        whitePieces_.push_back(pieceSquares_[xPos][yPos]);
    }
    else {
        blackPieces_.push_back(pieceSquares_[xPos][yPos]);
    }
}

void Model::BoardController::createPawnPiece(const int xPos, const int yPos, bool isWhite) {
    pieceSquares_[xPos][yPos] = std::make_shared<Pawn>(Pawn(xPos, yPos, isWhite));

    if (isWhite) {
        whitePieces_.push_back(pieceSquares_[xPos][yPos]);
    }
    else {
        blackPieces_.push_back(pieceSquares_[xPos][yPos]);
    }
}

void Model::BoardController::removePiece(const int xPos, const int yPos) {
    std::shared_ptr<Piece> ptrPieceToRemove = pieceSquares_[xPos][yPos];
    if (ptrPieceToRemove->getIsWhite()) {
        for (int i = 0; i < whitePieces_.size(); i++) {
            if (whitePieces_[i] == ptrPieceToRemove) {
                whitePieces_[i] = whitePieces_[whitePieces_.size() - 1];
                whitePieces_.pop_back();
                return;
            }
        }
    }
    else {
        for (int i = 0; i < blackPieces_.size(); i++) {
            if (blackPieces_[i] == ptrPieceToRemove) {
                blackPieces_[i] = blackPieces_[blackPieces_.size() - 1];
                blackPieces_.pop_back();
                return;
            }
        }
    }
}

std::shared_ptr<King> Model::BoardController::findKing() {
    if (isWhiteTurn_) {
        for (std::shared_ptr<Piece> currentPiece : whitePieces_) {
            if (std::shared_ptr<King> ptrKing = std::dynamic_pointer_cast<King>(currentPiece)) {
                return ptrKing;
            }
        }
    }
    else {
        for (std::shared_ptr<Piece> currentPiece : blackPieces_) {
            if (std::shared_ptr<King> ptrKing = std::dynamic_pointer_cast<King>(currentPiece)) {
                return ptrKing;
            }
        }
    }
    // Should never be reached because there is always one king on the board.
    return nullptr;
}

bool Model::BoardController::isChecked() {
    if (isWhiteTurn_) {
        std::pair<int, int> whiteKingPos = findKing()->getKingPosition();
        for (std::shared_ptr<Piece> currentPiece : blackPieces_) {
            if (currentPiece->isValidMove(pieceSquares_, whiteKingPos.first, whiteKingPos.second)) {
                return true;
            }
        }
    }
    else {
        std::pair<int, int> blackKingPos = findKing()->getKingPosition();
        for (std::shared_ptr<Piece> currentPiece : whitePieces_) {
            if (currentPiece->isValidMove(pieceSquares_, blackKingPos.first, blackKingPos.second)) {
                return true;
            }
        }
    }
    return false;
}

bool Model::BoardController::willBeChecked(const int xPosOfPiece, const int yPosOfPiece, const int xPosToVerify, const int yPosToVerify) {
    std::shared_ptr<Piece> tempPiece = pieceSquares_[xPosToVerify][yPosToVerify];
    temporaryMoveTo(xPosOfPiece, yPosOfPiece, xPosToVerify, yPosToVerify);

    bool const isInChecked = isChecked();

    temporaryMoveTo(xPosToVerify, yPosToVerify, xPosOfPiece, yPosOfPiece);
    pieceSquares_[xPosToVerify][yPosToVerify] = tempPiece;
    
    if (tempPiece != nullptr && tempPiece->getIsWhite()) {
        whitePieces_.push_back(tempPiece);
    }
    else if (tempPiece != nullptr) {
        blackPieces_.push_back(tempPiece);
    }

    return isInChecked;
}

bool Model::BoardController::checkValidTurn(const int xPos, const int yPos) {
    return isWhiteTurn_ == pieceSquares_[xPos][yPos]->getIsWhite();
}

bool Model::BoardController::checkValidMove(const int xPosOfPiece, const int yPosOfPiece, const int xPosToVerify, const int yPosToVerify) {
    return pieceSquares_[xPosOfPiece][yPosOfPiece]->isValidMove(pieceSquares_, xPosToVerify, yPosToVerify);
}

bool Model::BoardController::squareHasAPiece(const int xPos, const int yPos) {
    return pieceSquares_[xPos][yPos] != nullptr;
}

bool Model::BoardController::pieceIsWhite(const int xPos, const int yPos) {
    return pieceSquares_[xPos][yPos]->getIsWhite();
}

void Model::BoardController::movePieceTo(const int xPosOfPiece, const int yPosOfPiece, const int xPosToGo, const int yPosToGo) {
    if (pieceSquares_[xPosToGo][yPosToGo] != nullptr) {
        removePiece(xPosToGo, yPosToGo);
    }
    pieceSquares_[xPosOfPiece][yPosOfPiece]->move(pieceSquares_, xPosToGo, yPosToGo);
}

void Model::BoardController::temporaryMoveTo(const int xPosOfPiece, const int yPosOfPiece, const int xPosToGo, const int yPosToGo) {
    if (pieceSquares_[xPosToGo][yPosToGo] != nullptr) {
        removePiece(xPosToGo, yPosToGo);
    }
    pieceSquares_[xPosOfPiece][yPosOfPiece]->temporaryMove(pieceSquares_, xPosToGo, yPosToGo);
}

void Model::BoardController::swapTurn() {
    isWhiteTurn_ = !isWhiteTurn_;
}

bool Model::BoardController::getIsWhiteTurn() {
    return isWhiteTurn_;
}

void Model::BoardController::setIsWhiteTurn(bool isWhiteTurn) {
    isWhiteTurn_ = isWhiteTurn;
}

void Model::BoardController::initalizePieceBoard() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            pieceSquares_[col][row] = nullptr;
        }
    }
}

void Model::BoardController::cleanUp() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            pieceSquares_[col][row] = nullptr;
        }
    }
}

std::vector<std::pair<int, int>> Model::BoardController::getValidMove(const int xPosOfPiece, const int yPosOfPiece) {
    return pieceSquares_[xPosOfPiece][yPosOfPiece]->getValidMove(pieceSquares_);
}

void Model::BoardController::resetBoard() {
    cleanUp();
    whitePieces_.clear();
    blackPieces_.clear();
}

bool Model::BoardController::hasAValidMove() {
    if (isWhiteTurn_) {
        for (std::shared_ptr<Piece> currentPiece : whitePieces_) {
            if (currentPiece->getValidMove(pieceSquares_).size() > 0) {
                return true;
            }
        }
        return false;
    }
    else {
        for (std::shared_ptr<Piece> currentPiece : blackPieces_) {
            if (currentPiece->getValidMove(pieceSquares_).size() > 0) {
                return true;
            }
        }
        return false;
    }
}