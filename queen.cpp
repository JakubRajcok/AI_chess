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

        //Copied black rook
        while(tmpY < 7){//Right
            //Attentio of overflow the array, thats the reason of going to 6
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{//our or enemy chesspiece?
                if(this->board->whosOnBox(posX,posY+i)>=6)
                    this->validMoves.append(BoardPosition(posX,posY+i));
                break;
            }
        }
        i=1;
        tmpY=posY;
        while(tmpY > 0){//Left
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
        while(tmpX < 7){//Under
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
        while(tmpX > 0){//Up
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
        //Copied black bishop
        while(tmpX < 7 && tmpY > 0){//SV
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
        while(tmpX < 7 && tmpY < 7){//JV
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
        while(tmpX > 0 && tmpY < 7){//JZ
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
        while(tmpX > 0 && tmpY > 0){//SZ
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
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //copied white rook
        while(tmpY < 7){//right
            //only to 6, becouse we can overflow
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{//our or enemy chesspiece?
                if(this->board->whosOnBox(posX,posY+i)<6)
                    this->validMoves.append(BoardPosition(posX,posY+i));
                break;
            }
        }
        i=1;
        tmpY=posY;
        while(tmpY > 0){//Left
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
        while(tmpX < 7){//Under
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
        while(tmpX > 0){//Up
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
        while(tmpX < 7 && tmpY > 0){//SV
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
        while(tmpX < 7 && tmpY < 7){//JV
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
        while(tmpX > 0 && tmpY < 7){//JZ
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
        while(tmpX > 0 && tmpY > 0){//SZ
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
