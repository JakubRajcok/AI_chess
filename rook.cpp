#include "rook.h"

Rook::Rook(BoardPosition *pos, ChessBoard *board) : ChessPiece(pos,board)
{
    findValidMoves();
    if(this->type == 3){//black bishop
        this->iconName = "rook0.png";
    }else{
        this->iconName = "rook1.png";
    }
}

void Rook::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();

    int tmpX=posX;
    int tmpY=posY;
    int i=1;

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 3){// if it is black rook, or we can say if it is black chesspiece too
        /*VSEO princip prehladavania */
        //Prezerame smer v ktorom sa moze figurka pohybovat, ak je pol volne, zapiseme ak nie, zapiseme a koncime

        while(tmpY < 7){//Prezeranie policok na pravo
            //Prezerame ten buduci, preto len do 6, kedze mame 8 policok, ideme od nuly a pozerame 1 dopredu
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(this->board->whosOnBox(posX,posY+i)>5)
                    this->validMoves.append(BoardPosition(posX,posY+i));
                break;
            }
        }
        i=1;
        tmpY=posY;
        while(tmpY > 0){//Prezeranie policok na lavo
            if(this->board->whosOnBox(posX,posY-i)==-1){
                this->validMoves.append(BoardPosition(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(this->board->whosOnBox(posX,posY-i)>5)
                    this->validMoves.append(BoardPosition(posX,posY-i));
                break;
            }
        }
        i=1;
        tmpY=posY;
        while(tmpX < 7){//Prezeranie policek pod figurkou
            if(this->board->whosOnBox(posX+i,posY)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY));
                i++;
                tmpX++;
            }else{
                if(this->board->whosOnBox(posX+i,posY)>5)
                    this->validMoves.append(BoardPosition(posX+i,posY));
                break;
            }
        }
        i=1; tmpX=posX;
        while(tmpX > 0){//Prezeranie policek nad figurkou
            if(this->board->whosOnBox(posX-i,posY)==-1){
                this->validMoves.append(BoardPosition(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(this->board->whosOnBox(posX-i,posY)>5)
                    this->validMoves.append(BoardPosition(posX-i,posY));
                break;
            }
        }
    }else{//its white rook
        while(tmpY < 7){//Prezeranie policok na pravo
            //Prezerame ten buduci, preto len do 6, kedze mame 8 policok, ideme od nuly a pozerame 1 dopredu
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(this->board->whosOnBox(posX,posY+i)<6)
                    this->validMoves.append(BoardPosition(posX,posY+i));
                break;
            }
        }
        i=1;
        tmpY=posY;
        while(tmpY > 0){//Prezeranie policok na lavo
            if(this->board->whosOnBox(posX,posY-i)==-1){
                this->validMoves.append(BoardPosition(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(this->board->whosOnBox(posX,posY-i)<6)
                    this->validMoves.append(BoardPosition(posX,posY-i));
                break;
            }
        }
        i=1;
        while(tmpX < 7){//Prezeranie policek pod figurkou
            if(this->board->whosOnBox(posX+i,posY)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY));
                i++;
                tmpX++;
            }else{
                if(this->board->whosOnBox(posX+i,posY)<6)
                    this->validMoves.append(BoardPosition(posX+i,posY));
                break;
            }
        }
        i=1; tmpX=posX;
        while(tmpX > 0){//Prezeranie policek nad figurkou
            if(this->board->whosOnBox(posX-i,posY)==-1){
                this->validMoves.append(BoardPosition(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(this->board->whosOnBox(posX-i,posY)<6)
                    this->validMoves.append(BoardPosition(posX-i,posY));
                break;
            }
        }
    }

    //am I checking?
    this->checking = this->amIChecking();
}
