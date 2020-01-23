#include "queen.h"

Queen::Queen(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    findValidMoves();
    if(this->type == 4){//black bishop
        this->iconName = "queen0.png";
    }else{
        this->iconName = "queen1.png";
    }
}

void Queen::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 4){// if it is black pawn, or we can say if it is black chesspiece too
        //Kralovna obsahuje vezu a strelca do kopy, hor sa na kopirovanie a modli sa, aby neboli strelec s konom chybne
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //Skopirovany black rook
        while(tmpY < 7){//Prezeranie policok na pravo
            //Prezerame ten buduci, preto len do 6, kedze mame 8 policok, ideme od nuly a pozerame 1 dopredu
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(this->board->whosOnBox(posX,posY+i)>=6)
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
                if(this->board->whosOnBox(posX,posY-i)>=6)
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
                if(this->board->whosOnBox(posX+i,posY)>=6)
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
                if(this->board->whosOnBox(posX-i,posY)>=6)
                    this->validMoves.append(BoardPosition(posX-i,posY));
                break;
            }
        }
        i=1;tmpX=posX;tmpY=posY;
        //Skopirovany black bishop
        while(tmpX < 7 && tmpY > 0){//Pohyb na Severovychod
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
        while(tmpX < 7 && tmpY < 7){//Pohyb na JuhoVychod
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
        while(tmpX > 0 && tmpY < 7){//Pohyb na JuhoZapad
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
        while(tmpX > 0 && tmpY > 0){//Pohyb na SeveroZapad
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
        i=1;tmpX=posX;tmpY=posY;

        //Skopirovany white bishop
        while(tmpX < 7 && tmpY > 0){//Pohyb na Severovychod
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
        while(tmpX < 7 && tmpY < 7){//Pohyb na JuhoVychod
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
        while(tmpX > 0 && tmpY < 7){//Pohyb na JuhoZapad
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
        while(tmpX > 0 && tmpY > 0){//Pohyb na SeveroZapad
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
