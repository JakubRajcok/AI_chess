#include "queen.h"

Queen::Queen()
{

}

void Queen::findValidMoves(BoardPosition &pos){
    int posX=pos.getX();
    int posY=pos.getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 4){// if it is black pawn, or we can say if it is black chesspiece too
        //Kralovna obsahuje vezu a strelca do kopy, hor sa na kopirovanie a modli sa, aby neboli strelec s konom chybne
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //Skopirovany black rook
        while(tmpX < 7){//Prezeranie policok na pravo
            if(this->board->whosOnBox(posX+i,posY)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY));
                i++;
                tmpX++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(this->board->whosOnBox(posX+i,posY)>=6)
                    this->validMoves.append(BoardPosition(posX+i,posY));
                break;
            }
        }
        i=1;
        tmpX=posX;
        while(tmpX > 0){//Prezeranie policok na lavo
            if(this->board->whosOnBox(posX-i,posY)==-1){
                this->validMoves.append(BoardPosition(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(this->board->whosOnBox(posX+i,posY)>=6)
                    this->validMoves.append(BoardPosition(posX-i,posY));
                break;
            }
        }
        i=1;
        while(tmpY < 7){//Prezeranie policek pod figurkou
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{
                if(this->board->whosOnBox(posX,posY+i)>=6)
                    this->validMoves.append(BoardPosition(posX,posY+i));
                break;
            }
        }
        i=1; tmpY=posY;
        while(tmpY > 0){//Prezeranie policek nad figurkou
            if(this->board->whosOnBox(posX,posY-i)==-1){
                this->validMoves.append(BoardPosition(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(this->board->whosOnBox(posX,posY-i)>=6)
                    this->validMoves.append(BoardPosition(posX,posY-i));
                break;
            }
        }
        i=1;tmpX=posX;tmpY=posY;
        //Skopirovany black bishop
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
        //Kralovna obsahuje vezu a strelca do kopy, hor sa na kopirovanie a modli sa, aby neboli strelec s konom chybne
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //skopirovany white rook
        while(tmpX < 7){//Prezeranie policok na pravo
            if(this->board->whosOnBox(posX+i,posY)==-1){
                this->validMoves.append(BoardPosition(posX+i,posY));
                i++;
                tmpX++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(this->board->whosOnBox(posX+i,posY)<6)
                    this->validMoves.append(BoardPosition(posX+i,posY));
                break;
            }
        }
        i=1;
        tmpX=posX;
        while(tmpX > 0){//Prezeranie policok na lavo
            if(this->board->whosOnBox(posX-i,posY)==-1){
                this->validMoves.append(BoardPosition(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(this->board->whosOnBox(posX+i,posY)<6)
                    this->validMoves.append(BoardPosition(posX-i,posY));
                break;
            }
        }
        i=1;
        while(tmpY < 7){//Prezeranie policek pod figurkou
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{
                if(this->board->whosOnBox(posX,posY+i)<6)
                    this->validMoves.append(BoardPosition(posX,posY+i));
                break;
            }
        }
        i=1; tmpY=posY;
        while(tmpY > 0){//Prezeranie policek nad figurkou
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
        i=1;tmpX=posX;tmpY=posY;

        //Skopirovany white bishop
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
