#include "mainwindow.h"
#include "chessboard.h"
#include "game.h"

#include <QApplication>
#include <QObject>
using namespace std;

int main(int argc, char *argv[]){
    ChessBoard *board=new ChessBoard();
    /*
    board.draw_board();
    board.draw_pawns();
    board.deleteBoard();
    */


    QApplication a(argc, argv);
    MainWindow w;
    Game g;
    QObject::connect(&w,SIGNAL(pohniStrelcom(int, int)),&g,SLOT(vyriesPohybStrelca(int, int)));
    w.show();
    return a.exec();
}
