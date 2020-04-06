#include "horse.h"

Horse::Horse(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    findValidMoves();
    if(this->type == 1){//black bishop
        this->iconName = "horse0.png";
    }else{
        this->iconName = "horse1.png";
    }
}

void Horse::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    //now im making if for every possibility to move, max(horse moves) == 8

    if(this->type == 1){// if it is black horse, or we can say if it is black chesspiece too
        if(posX-1>=0 && posY-2>=0){
            if(this->board->whosOnBox(posX-1,posY-2)==-1 || this->board->whosOnBox(posX-1,posY-2)>5)
                this->validMoves.append(BoardPosition(posX-1,posY-2));
        }
        if(posX+1<=7 && posY-2>=0){
            if(this->board->whosOnBox(posX+1,posY-2)==-1 || this->board->whosOnBox(posX+1,posY-2)>5)
                this->validMoves.append(BoardPosition(posX+1,posY-2));
        }
        if(posX+2<=7 && posY-1>=0){
            if(this->board->whosOnBox(posX+2,posY-1)==-1 || this->board->whosOnBox(posX+2,posY-1)>5)
                this->validMoves.append(BoardPosition(posX+2,posY-1));
        }
        if(posX+2<=7 && posY+1<=7){
            if(this->board->whosOnBox(posX+2,posY+1)==-1 || this->board->whosOnBox(posX+2,posY+1)>5)
                this->validMoves.append(BoardPosition(posX+2,posY+1));
        }
        if(posX+1<=7 && posY+2<=7){
            if(this->board->whosOnBox(posX+1,posY+2)==-1 || this->board->whosOnBox(posX+1,posY+2)>5)
                this->validMoves.append(BoardPosition(posX+1,posY+2));
        }
        if(posX-1>=0 && posY+2<=7){
            if(this->board->whosOnBox(posX-1,posY+2)==-1 || this->board->whosOnBox(posX-1,posY+2)>5)
                this->validMoves.append(BoardPosition(posX-1,posY+2));
        }
        if(posX-2>=0 && posY+1<=7){
            if(this->board->whosOnBox(posX-2,posY+1)==-1 || this->board->whosOnBox(posX-2,posY+1)>5)
                this->validMoves.append(BoardPosition(posX-2,posY+1));
        }
        if(posX-2>=0 && posY-1>=0){
            if(this->board->whosOnBox(posX-2,posY-1)==-1 || this->board->whosOnBox(posX-2,posY-1)>5)
                this->validMoves.append(BoardPosition(posX-2,posY-1));
        }
    }else{// it is white horse
        if(posX-1>=0 && posY-2>=0){
            if(this->board->whosOnBox(posX-1,posY-2)==-1 || this->board->whosOnBox(posX-1,posY-2)<6)
                this->validMoves.append(BoardPosition(posX-1,posY-2));
        }
        if(posX+1<=7 && posY-2>=0){
            if(this->board->whosOnBox(posX+1,posY-2)==-1 || this->board->whosOnBox(posX+1,posY-2)<6)
                this->validMoves.append(BoardPosition(posX+1,posY-2));
        }
        if(posX+2<=7 && posY-1>=0){
            if(this->board->whosOnBox(posX+2,posY-1)==-1 || this->board->whosOnBox(posX+2,posY-1)<6)
                this->validMoves.append(BoardPosition(posX+2,posY-1));
        }
        if(posX+2<=7 && posY+1<=7){
            if(this->board->whosOnBox(posX+2,posY+1)==-1 || this->board->whosOnBox(posX+2,posY+1)<6)
                this->validMoves.append(BoardPosition(posX+2,posY+1));
        }
        if(posX+1<=7 && posY+2<=7){
            if(this->board->whosOnBox(posX+1,posY+2)==-1 || this->board->whosOnBox(posX+1,posY+2)<6)
                this->validMoves.append(BoardPosition(posX+1,posY+2));
        }
        if(posX-1>=0 && posY+2<=7){
            if(this->board->whosOnBox(posX-1,posY+2)==-1 || this->board->whosOnBox(posX-1,posY+2)<6)
                this->validMoves.append(BoardPosition(posX-1,posY+2));
        }
        if(posX-2>=0 && posY+1<=7){
            if(this->board->whosOnBox(posX-2,posY+1)==-1 || this->board->whosOnBox(posX-2,posY+1)<6)
                this->validMoves.append(BoardPosition(posX-2,posY+1));
        }
        if(posX-2>=0 && posY-1>=0){
            if(this->board->whosOnBox(posX-2,posY-1)==-1 || this->board->whosOnBox(posX-2,posY-1)<6)
                this->validMoves.append(BoardPosition(posX-2,posY-1));
        }
    }

    //am I checking?
    this->checking = this->amIChecking();
}
