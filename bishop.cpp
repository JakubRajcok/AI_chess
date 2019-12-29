#include "bishop.h"

Bishop::Bishop()
{

}

void Bishop::findValidMoves(BoardPosition &pos){
    int posX=pos.getX();
    int posY=pos.getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    int tmpX=posX;
    int tmpY=posY;
    int i=1;

    if(this->type == 2){// if it is black bishop, or we can say if it is black chesspiece too
        while(tmpX < 7 || tmpY > 0){//Pohyb na Severovychod
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
        while(tmpX < 7 || tmpY < 7){//Pohyb na JuhoVychod
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
        while(tmpX > 0 || tmpY < 7){//Pohyb na JuhoZapad
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
        while(tmpX > 0 || tmpY > 0){//Pohyb na SeveroZapad
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
        while(tmpX < 7 || tmpY > 0){//Pohyb na Severovychod
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
        while(tmpX < 7 || tmpY < 7){//Pohyb na JuhoVychod
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
        while(tmpX > 0 || tmpY < 7){//Pohyb na JuhoZapad
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
        while(tmpX > 0 || tmpY > 0){//Pohyb na SeveroZapad
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
}
