#include "pawn.h"

//potrebujem invoke of ChessPiece(BoardPosition &pos, ChessBoard *board);

//+dalsia funkcionalita

Pawn::Pawn(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    findValidMoves();
}

void Pawn::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();

    ////////////////////////////////////////////////////////////
    //if(posX==7) tak vymena za novu figurku
    ///////////////////////////////////////////////////////////

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 0){// if it is black pawn, or we can say if it is black chesspiece too
        //Pokial to je prvy tah a pesiak sa moze pohnut o dve policka
        if(posX == 1){
            if( this->board->whosOnBox(posX+1,posY) == -1 && this->board->whosOnBox(posX+2,posY) == -1 ){
                this->validMoves.append(BoardPosition(posX+2,posY));
            }
        }
        //is place behind free?

        if(this->board->whosOnBox(posX+1,posY)==-1){
            this->validMoves.append(BoardPosition(posX+1,posY));
        }
        //may I attack someone?
        if(posX<6 && posY<7 && this->board->whosOnBox(posX+1,posY+1)>6){
            this->validMoves.append(BoardPosition(posX+1,posY+1));
        }
        //may I attack someone?
        if(posX<6 && posY>0 && this->board->whosOnBox(posX+1,posY-1)>6){
            this->validMoves.append(BoardPosition(posX+1,posY-1));
        }

    }else{// chesspiece is white pawn
        if(posX == 5){
            if( this->board->whosOnBox(posX-1,posY) == -1 && this->board->whosOnBox(posX-2,posY) == -1 ){
                this->validMoves.append(BoardPosition(posX-2,posY));
            }
        }
        //is place behind free?
        if(posX>1 && this->board->whosOnBox(posX-1,posY)==-1){
            this->validMoves.append(BoardPosition(posX-1,posY));
        }
        //may I attack someone?
        if(posX>1 && posY>0 && this->board->whosOnBox(posX-1,posY-1)<=5){
            this->validMoves.append(BoardPosition(posX-1,posY-1));
        }
        //may I attack someone?
        if(posX>1 && posY<7 && this->board->whosOnBox(posX-1,posY+1)<=5){
            this->validMoves.append(BoardPosition(posX-1,posY+1));
        }
    }
}
