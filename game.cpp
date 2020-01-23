#include "game.h"
#include <QDebug>

#include "chessboard.h"
#include "player.h"

Game::Game(QObject *parent) : QObject(parent), board{new ChessBoard}
{
this->gameMode = 0;
this->clickedChessPiece=nullptr;
/*
Nastavenie game mode 0 -> taha biely
Cakaj na signal a po kliku prejdi pole figurok a porovnaj ich pozicie
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

void Game::makeMove(ChessPiece* toByMoved,int row,int col){

    int typeOfChessPiece = toByMoved->getType();
    int oldX= toByMoved->getPosition()->getX();
    int oldY= toByMoved->getPosition()->getY();
    int newX=row;
    int newY=col;
    int*** brd = board->getBoard();

    for(int i=0;i<12;i++){
        if(i==0)
            brd[oldX][oldY][i] = -1;
        else
            brd[oldX][oldY][i] = 0;
    }

    for(int i=0;i<12;i++){
        if(i==0)
            brd[newX][newY][i] = -1;
        else
            brd[newX][newY][i] = 0;
    }

    for(int i=0;i<12;i++){
        if(i == typeOfChessPiece)
            brd[newX][newY][i] = 1;
        else
            brd[newX][newY][i]=0;
    }

    toByMoved->getPosition()->setX(newX);
    toByMoved->getPosition()->setY(newY);

    toByMoved->findValidMoves();

    return;
}


void Game::vyriesKlik(int row, int col)
{   

    int whoWasClicked = this->board->whosOnBox(row,col);

    if (whoWasClicked == -1){
        if(gameMode == 2 || gameMode ==3){
            for(auto& cp : this->clickedChessPiece->getValidMoves() ){
                //qDebug()<< "Kliknute suradnice (row col): " << row << " "<< col << " Figurka (row col): "<< cp.getX() << " " <<cp.getY();
                if(cp.getX() == row && cp.getY() == col){
                    qDebug() << "Nasiel som validne policko";

                    makeMove(this->clickedChessPiece, row, col);

                    if(this->gameMode == 2)
                        this->gameMode = 1;
                    else
                        this->gameMode = 0;

                    this->clickedChessPiece = nullptr;

                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());

                    return;
                }
            }
        }
        qDebug() << "Chyba 1";
        return;
    }

    //if i am black and i choose 1st chesspiece white
    if(gameMode == 0 && whoWasClicked>=6){
        qDebug() << "Som cierny a klikam na bielu";
        return;
    }
    //if i am white and i choose 1st chesspiece black
    if(gameMode == 1 && whoWasClicked<6){
        qDebug() << "Som biely a klikam na ciernu";
        return;
    }

    if(this->gameMode == 0 || gameMode == 2){//black turn

        //if I am black and i clicked on black chesspiece which i want to move
        if(whoWasClicked<6 && this->clickedChessPiece == nullptr){

            this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
            this->clickedChessPiece->findValidMoves();
            //If i cicked corectly, but my chosen chesspiece got no validmoves
            if(this->clickedChessPiece->getValidMoves().size()<=0){
                this->clickedChessPiece=nullptr;
                qDebug() << "Figurka nema platne pohyby";
                return;
            }

            qDebug() << "Inicializacia figurky na pohyb";
            this->gameMode = this->gameMode+2;
            emit validMoves(this->clickedChessPiece->getValidMoves());
            return;
        }

        //if i clicked same chesspiece twice
        if(this->gameMode == 2 && this->clickedChessPiece->getPosition()->getX() == row && this->clickedChessPiece->getPosition()->getY() == col ){
            qDebug() << "Teraz riesim stlacenie tej istej figurky 2x";
            this->clickedChessPiece=nullptr;
            this->gameMode= this->gameMode-2;

            //TU TREBA DOPLNIT CREAL TABULKY, ODZNACENIE ZAZNACENEHO

            return;
        }
        return;
    }else if(this->gameMode == 1 || gameMode == 3){//white turn

        //if I am white and i clicked on white chesspiece which i want to move
        if(whoWasClicked>=6 && this->clickedChessPiece==nullptr){
            this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
            this->gameMode = this->gameMode+2;
            emit validMoves(this->clickedChessPiece->getValidMoves());
            return;
        }

        //if i clicked same chesspiece twice
        if(this->gameMode == 3 && this->clickedChessPiece->getPosition()->getX() == row && this->clickedChessPiece->getPosition()->getY() == col ){
            this->clickedChessPiece=nullptr;
            this->gameMode= this->gameMode-2;

            //TU TREBA DOPLNIT CREAL TABULKY, ODZNACENIE ZAZNACENEHO

            return;
        }
    }


    //QList<BoardPosition> bp = cp->getValidMoves();

    qDebug() << "Som za ifom ";

}
