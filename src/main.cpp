#include <utility>

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

#include "Board.h"
#include "ChessWindow.h"
#include "Pieces.h"
#include "PromotionController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GUI::ChessWindow chessWindow;
    chessWindow.preparePieces();
    chessWindow.show();

    QObject::connect(&app, &QCoreApplication::aboutToQuit, &Model::BoardController::cleanUp);

    PawnPromotion::linkGui(chessWindow);
    
    return app.exec();
}
