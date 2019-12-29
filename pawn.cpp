#include "pawn.h"

Pawn::Pawn()//ako oddedit ten isty konstruktor a obohatit ho o vlastnu funkcionalitu?
{

//potrebujem invoke of ChessPiece(BoardPosition &pos, ChessBoard *board);

//+dalsia funkcionalita
}

void Pawn::findValidMoves(BoardPosition& pos){
    int posX=pos.getX();
    int posY=pos.getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 0){// if it is black pawn, or we can say if it is black chesspiece too
        //Pokial to je prvy tah a pesiak sa moze pohnut o dve policka
        if(posY == 1){//______________________________________________________bolo tu posX, mozno len bluznis tak sa k tomu vrat
            if( this->board->whosOnBox(posX,posY+1) == -1 && this->board->whosOnBox(posX,posY+2) == -1 ){
                this->validMoves.append(BoardPosition(posX,posY+2));
            }
        }
        //is place behind free?
        if(this->board->whosOnBox(posX,posY+1)==-1){
            this->validMoves.append(BoardPosition(posX,posY+1));
        }
        //may I attack someone?
        if(posX<6 && this->board->whosOnBox(posX+1,posY+1)>=6){
            this->validMoves.append(BoardPosition(posX+1,posY+1));
        }
        //may I attack someone?
        if(posX>0 && this->board->whosOnBox(posX-1,posY+1)>=6){
            this->validMoves.append(BoardPosition(posX-1,posY+1));
        }

    }else{// chesspiece is white pawn
        if(posY == 5){//______________________________________________________bolo tu posX, mozno len bluznis tak sa k tomu vrat
            if( this->board->whosOnBox(posX,posY-1) == -1 && this->board->whosOnBox(posX,posY-2) == -1 ){
                this->validMoves.append(BoardPosition(posX,posY-2));
            }
        }
        //is place behind free?
        if(this->board->whosOnBox(posX,posY-1)==-1){
            this->validMoves.append(BoardPosition(posX,posY-1));
        }
        //may I attack someone?
        if(posX>0 && this->board->whosOnBox(posX-1,posY-1)<=5){
            this->validMoves.append(BoardPosition(posX-1,posY-1));
        }
        //may I attack someone?
        if(posX<6 && this->board->whosOnBox(posX+1,posY-1)>=6){
            this->validMoves.append(BoardPosition(posX+1,posY-1));
        }
    }
}
