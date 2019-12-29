#include "chesspiece.h"
#include "boardposition.h"
#include "chessboard.h"

ChessPiece::ChessPiece(){}

ChessPiece::ChessPiece(BoardPosition &pos, ChessBoard *board)
{
    this->position=new BoardPosition(pos.getX(),pos.getY());
    this->board=board;
    this->type=this->board->whosOnBox(pos.getX(),pos.getY());//whosOnBox(pos);
    this->isPlaced=true;

    if(whosOnBox(pos)<6)
        this->color=0;
    else
        this->color=1;
}

ChessPiece::~ChessPiece(){
    delete(this->position);
}

//tejto funkcii postnem policko v podobe BoardPositionu alebo posX a posY a ona mi povie
//ako na tom dane policko je
int ChessPiece::whosOnBox(BoardPosition &pos){
    /*******************
     * ret> ID of pawn *
     * ret -1 > Empty  *
     *******************/
    int posX=pos.getX();
    int posY=pos.getY();
    //v poli  sa nachadzaju jednotky a nuly, TAKZE NEVIES co konkretne to je

    return this->board->whosOnBox(posX,posY);
}
