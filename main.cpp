/**
Ce fichier permet simplement de lancer les tests(dans `TestChess.cpp`) ainsi que d'initaliser l'échecier ainsi que les Pieces.
Par la suite, il lance un interface graphique(GUI) pour permettre de jouer au échec.

ficher      main.cpp
autheur     Mathieu Banville et Julien Leduc
date        5 mai 2023
Créé le     9 avril 2023
**/

#include <utility>

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

#include "Board.h"
#include "ChessWindow.h"
#include "Pieces.h"
#include "PromotionControler.h"

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  
#endif

//Cette fonction provient du projet ProjetTestQt du cours offert sur le Moodle.
void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    #ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();
	//bibliotheque_cours::executerGoogleTest(argc, argv); 
    #endif
}


bool Model::BoardController::isWhiteTurn_ = true;
std::shared_ptr<Piece> Model::BoardController::pieceSquares_[8][8];
std::vector<std::shared_ptr<Piece>> Model::BoardController::whitePieces_;
std::vector<std::shared_ptr<Piece>> Model::BoardController::blackPieces_;
int King::nbOfKings_ = 0;
GUI::ChessWindow* PawnPromotion::chessWindow_ = nullptr;


int main(int argc, char *argv[])
{
    bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
    QApplication app(argc, argv);
    initialiserBibliothequeCours(argc, argv);

    GUI::ChessWindow chessWindow;
    chessWindow.preparePieces();
    chessWindow.show();

    QObject::connect(&app, &QCoreApplication::aboutToQuit, &Model::BoardController::cleanUp);

    PawnPromotion::linkGui(chessWindow);
    
    return app.exec();
}
