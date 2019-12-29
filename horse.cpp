#include "horse.h"

Horse::Horse()
{

}

void Horse::findValidMoves(BoardPosition& pos){
    int posX=pos.getX();
    int posY=pos.getY();

    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 1){// if it is black horse, or we can say if it is black chesspiece too
        if(posX-1>=0 && posY-3>=0){
            if(this->board->whosOnBox(posX-1,posY-3)==-1 || this->board->whosOnBox(posX-1,posY-3)>5)
                this->validMoves.append(BoardPosition(posX-1,posY-3));
        }
        if(posX+1<=7 && posY-3>=0){
            if(this->board->whosOnBox(posX+1,posY-3)==-1 || this->board->whosOnBox(posX+1,posY-3)>5)
                this->validMoves.append(BoardPosition(posX+1,posY-3));
        }
        if(posX+2<=7 && posY-1>=0){
            if(this->board->whosOnBox(posX+2,posY-1)==-1 || this->board->whosOnBox(posX+2,posY-1)>5)
                this->validMoves.append(BoardPosition(posX+2,posY-1));
        }
        if(posX+2<=7 && posY+1<=7){
            if(this->board->whosOnBox(posX+2,posY+1)==-1 || this->board->whosOnBox(posX+2,posY+1)>5)
                this->validMoves.append(BoardPosition(posX+2,posY+1));
        }
        if(posX+1<=7 && posY+3<=7){
            if(this->board->whosOnBox(posX+1,posY+3)==-1 || this->board->whosOnBox(posX+1,posY+3)>5)
                this->validMoves.append(BoardPosition(posX+1,posY+3));
        }
        if(posX-1>=0 && posY+3<=7){
            if(this->board->whosOnBox(posX-1,posY+3)==-1 || this->board->whosOnBox(posX-1,posY+3)>5)
                this->validMoves.append(BoardPosition(posX-1,posY+3));
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
        if(posX-1>=0 && posY-3>=0){
            if(this->board->whosOnBox(posX-1,posY-3)==-1 || this->board->whosOnBox(posX-1,posY-3)<6)
                this->validMoves.append(BoardPosition(posX-1,posY-3));
        }
        if(posX+1<=7 && posY-3>=0){
            if(this->board->whosOnBox(posX+1,posY-3)==-1 || this->board->whosOnBox(posX+1,posY-3)<6)
                this->validMoves.append(BoardPosition(posX+1,posY-3));
        }
        if(posX+2<=7 && posY-1>=0){
            if(this->board->whosOnBox(posX+2,posY-1)==-1 || this->board->whosOnBox(posX+2,posY-1)<6)
                this->validMoves.append(BoardPosition(posX+2,posY-1));
        }
        if(posX+2<=7 && posY+1<=7){
            if(this->board->whosOnBox(posX+2,posY+1)==-1 || this->board->whosOnBox(posX+2,posY+1)<6)
                this->validMoves.append(BoardPosition(posX+2,posY+1));
        }
        if(posX+1<=7 && posY+3<=7){
            if(this->board->whosOnBox(posX+1,posY+3)==-1 || this->board->whosOnBox(posX+1,posY+3)<6)
                this->validMoves.append(BoardPosition(posX+1,posY+3));
        }
        if(posX-1>=0 && posY+3<=7){
            if(this->board->whosOnBox(posX-1,posY+3)==-1 || this->board->whosOnBox(posX-1,posY+3)<6)
                this->validMoves.append(BoardPosition(posX-1,posY+3));
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
}
