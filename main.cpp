#include "mainwindow.h"
#include "chessboard.h"
#include "game.h"

#include <QApplication>
#include <QObject>
using namespace std;

int main(int argc, char *argv[]){

    /*
    board.draw_board();
    board.draw_pawns();
    board.deleteBoard();
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
