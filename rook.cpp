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

        while(tmpY < 7){//Right
            //just to six, becouse we can overflow
            if(this->board->whosOnBox(posX,posY+i)==-1){
                this->validMoves.append(BoardPosition(posX,posY+i));
                i++;
                tmpY++;
            }else{//our ot enemy chesspiece?
                if(this->board->whosOnBox(posX,posY+i)>5)
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
                if(this->board->whosOnBox(posX,posY-i)>5)
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
                if(this->board->whosOnBox(posX+i,posY)>5)
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
                if(this->board->whosOnBox(posX-i,posY)>5)
                    this->validMoves.append(BoardPosition(posX-i,posY));
                break;
            }
        }
    }else{//its white rook
        while(tmpY < 7){//Right
            //only six, becouse of overlflowing
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
        while(tmpY > 0){//left
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
        while(tmpX < 7){//under
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
        while(tmpX > 0){//up
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
