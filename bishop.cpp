#include "bishop.h"

Bishop::Bishop(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    if(this->type == 2){//black bishop
        this->iconName = "bishop0.png";
    }else{
        this->iconName = "bishop1.png";
    }
    findValidMoves();
}


void Bishop::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    int tmpX=posX;
    int tmpY=posY;
    int i=1;

    if(this->type == 2){// if it is black bishop, or we can say if it is black chesspiece too
        while(tmpX < 7 && tmpY > 0){//Move to northeast //SV
            if(this->board->whosOnBox(posX+i,posY-i)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY-i));
                i++;
                tmpX++;
                tmpY--;
            }else{
                if(this->board->whosOnBox(posX+i,posY-i)>=6)
                    this->validMoves.append(BoardPosition(posX+i,posY-i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 && tmpY < 7){//Move to southeast //JV
            if(this->board->whosOnBox(posX+i,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY+i));
                i++;
                tmpX++;
                tmpY++;
            }else{
                if(this->board->whosOnBox(posX+i,posY+i)>=6)
                    this->validMoves.append(BoardPosition(posX+i,posY+i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY < 7){//Move to southwest //JZ
            if(this->board->whosOnBox(posX-i,posY+i)== -1){
                this->validMoves.append(BoardPosition(posX-i,posY+i));
                i++;
                tmpX--;
                tmpY++;
            }else {
                if (this->board->whosOnBox(posX - i, posY + i) >= 6)
                    this->validMoves.append(BoardPosition(posX - i, posY + i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY > 0){//Move to northwest //SZ
            if(this->board->whosOnBox(posX-i,posY-i)== -1){
                this->validMoves.append(BoardPosition(posX-i,posY-i));
                i++;
                tmpX--;
                tmpY--;
            }else {
                if (this->board->whosOnBox(posX - i, posY - i) >= 6)
                    this->validMoves.append(BoardPosition(posX - i, posY - i));
                break;
            }
        }
    }else{
        while(tmpX < 7 && tmpY > 0){//Move to northeast
            if(this->board->whosOnBox(posX+i,posY-i)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY-i));
                i++;
                tmpX++;
                tmpY--;
            }else{
                if(this->board->whosOnBox(posX+i,posY-i)<6)
                    this->validMoves.append(BoardPosition(posX+i,posY-i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 && tmpY < 7){//Pohyb na southeast
            if(this->board->whosOnBox(posX+i,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY+i));
                i++;
                tmpX++;
                tmpY++;
            }else{
                if(this->board->whosOnBox(posX+i,posY+i)<6)
                    this->validMoves.append(BoardPosition(posX+i,posY+i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY < 7){//Pohyb na southwest
            if(this->board->whosOnBox(posX-i,posY+i)== -1){
                this->validMoves.append(BoardPosition(posX-i,posY+i));
                i++;
                tmpX--;
                tmpY++;
            }else {
                if (this->board->whosOnBox(posX - i, posY + i) < 6)
                    this->validMoves.append(BoardPosition(posX - i, posY + i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY > 0){//Pohyb na northwest
            if(this->board->whosOnBox(posX-i,posY-i)== -1){
                this->validMoves.append(BoardPosition(posX-i,posY-i));
                i++;
                tmpX--;
                tmpY--;
            }else {
                if (this->board->whosOnBox(posX - i, posY - i) < 6)
                    this->validMoves.append(BoardPosition(posX - i, posY - i));
                break;
            }
        }
    }

    //am I checking?
    this->checking = this->amIChecking();
}
