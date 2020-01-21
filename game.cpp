#include "game.h"
#include <QDebug>

#include "chessboard.h"
#include "player.h"

Game::Game(QObject *parent) : QObject(parent), board{new ChessBoard}
{
this->gameMode = 1;
/*
Nastavenie game mode 0 -> taha biely
Cakaj na signal a po klki prejdi pole figurok a porovnaj ich pozicie
Prepni gamemode na -1 a vysviet validne tahy kliknutej figurky
po kliknuti na rovnaku figurku nastav gamemode 0 (white)
po kliknuti na vlaidne policko prepis klavesnicu a nastav game mode 1 (bklack)
*/

}

ChessBoard *Game::getBoard() const
{
    return board;
}

void Game::setBoard(ChessBoard *value)
{
    board = value;
}


void Game::vyriesKlik(int r, int c)
{   

    int wob = this->board->whosOnBox(r,c);

    if (wob == -1)
        return;

    ChessPiece* cp = this->board->chesspieceOnBox(BoardPosition(r,c),this->gameMode);

    QList<BoardPosition> bp = cp->getValidMoves();
   // emit validMoves();

}
