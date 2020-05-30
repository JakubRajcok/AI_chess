#include "king.h"

King::King(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    findValidMoves();
    if(this->type == 5){//black king
        this->iconName = "king0.png";
    }else{
        this->iconName = "king1.png";
    }
}
bool King::checking(){

    //It is black king
    if(this->getType() == 5){

        int posX = this->getPosition()->getX();
        int posY = this->getPosition()->getY();

        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //Am i attacked by queen or rook?
        while(tmpY < 7){//Listing boxes on the right
            if(this->board->whosOnBox(posX,posY+i) == 9 || this->board->whosOnBox(posX,posY+i) == 10)
                return true;
            i++;
            tmpY++;
        }
        i=1;
        tmpY=posY;
        while(tmpY > 0){//Listing boxes on the left
            if(this->board->whosOnBox(posX,posY-i) == 9 || this->board->whosOnBox(posX,posY-i) == 10)
                return true;
            i++;
            tmpY--;

        }
        i=1;
        tmpY=posY;
        while(tmpX < 7){//Listing boxes under the chesspiece
            if(this->board->whosOnBox(posX+i,posY) == 9 || this->board->whosOnBox(posX+i,posY) == 10)
                return true;
            i++;
            tmpX++;
        }
        i=1; tmpX=posX;
        while(tmpX > 0){//Listing boxes on top of the chesspiece
            if(this->board->whosOnBox(posX-i,posY) == 9 || this->board->whosOnBox(posX-i,posY) == 10)
                return true;
            i++;
            tmpX--;
        }
        i=1;tmpX=posX;tmpY=posY;

        //Am I attacked by bishop or queen?
        while(tmpX < 7 && tmpY > 0){//SV
            if(this->board->whosOnBox(posX+i,posY-i) == 8 || this->board->whosOnBox(posX+i,posY-i) == 10)
                return true;
            i++;
            tmpX++;
            tmpY--;

        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 && tmpY < 7){//JV
            if(this->board->whosOnBox(posX+i,posY+i) == 8 || this->board->whosOnBox(posX+i,posY+i) == 10)
                return true;
            i++;
            tmpX++;
            tmpY++;

        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY < 7){//JZ
            if(this->board->whosOnBox(posX-i,posY+i)== 8 || this->board->whosOnBox(posX-i,posY+i)== 10)
                return true;
            i++;
            tmpX--;
            tmpY++;

        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY > 0){//SZ
            if(this->board->whosOnBox(posX-i,posY-i)== 8 || this->board->whosOnBox(posX-i,posY-i)== 10)
                return true;
            i++;
            tmpX--;
            tmpY--;
        }

        //copied knight

        if(posX-1>=0 && posY-2>=0){
            if( this->board->whosOnBox(posX-1,posY-2) == 7)
                return true;
        }
        if(posX+1<=7 && posY-2>=0){
            if(this->board->whosOnBox(posX+1,posY-2) == 7)
                return true;
        }
        if(posX+2<=7 && posY-1>=0){
            if( this->board->whosOnBox(posX+2,posY-1) == 7)
                return true;
        }
        if(posX+2<=7 && posY+1<=7){
            if( this->board->whosOnBox(posX+2,posY+1) == 7)
                return true;
        }
        if(posX+1<=7 && posY+2<=7){
            if( this->board->whosOnBox(posX+1,posY+2) == 7)
                return true;
        }
        if(posX-1>=0 && posY+2<=7){
            if( this->board->whosOnBox(posX-1,posY+2) == 7)
                return true;
        }
        if(posX-2>=0 && posY+1<=7){
            if( this->board->whosOnBox(posX-2,posY+1) == 7)
                return true;
        }
        if(posX-2>=0 && posY-1>=0){
            if( this->board->whosOnBox(posX-2,posY-1) == 7)
                return true;
        }

        //am I attacked by the pawn?
        if(posX<6 && posY<7 && this->board->whosOnBox(posX+1,posY+1) == 6){
            return true;
        }
        if(posX<6 && posY>0 && this->board->whosOnBox(posX+1,posY-1) == 6){
            return true;
        }

    //It is white king
    } else{

        int posX = this->getPosition()->getX();
        int posY = this->getPosition()->getY();

        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //am i attacked by queen or rook?
        while(tmpY < 7){//Right
            if(this->board->whosOnBox(posX,posY+i) == 9-6 || this->board->whosOnBox(posX,posY+i) == 10-6)
                return true;
            i++;
            tmpY++;
        }
        i=1;
        tmpY=posY;
        while(tmpY > 0){//Left
            if(this->board->whosOnBox(posX,posY-i) == 9-6 || this->board->whosOnBox(posX,posY-i) == 10-6)
                return true;
            i++;
            tmpY--;

        }
        i=1;
        tmpY=posY;
        while(tmpX < 7){//Under
            if(this->board->whosOnBox(posX+i,posY) == 9-6 || this->board->whosOnBox(posX+i,posY) == 10-6)
                return true;
            i++;
            tmpX++;
        }
        i=1; tmpX=posX;
        while(tmpX > 0){//Up
            if(this->board->whosOnBox(posX-i,posY) == 9-6 || this->board->whosOnBox(posX-i,posY) == 10-6)
                return true;
            i++;
            tmpX--;
        }
        i=1;tmpX=posX;tmpY=posY;

        //Am I attacked by bishop or queen?
        while(tmpX < 7 && tmpY > 0){//SV
            if(this->board->whosOnBox(posX+i,posY-i) == 8-6 || this->board->whosOnBox(posX+i,posY-i) == 10-6)
                return true;
            i++;
            tmpX++;
            tmpY--;

        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 && tmpY < 7){//JV
            if(this->board->whosOnBox(posX+i,posY+i) == 8-6 || this->board->whosOnBox(posX+i,posY+i) == 10-6)
                return true;
            i++;
            tmpX++;
            tmpY++;

        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY < 7){//JZ
            if(this->board->whosOnBox(posX-i,posY+i)== 8-6 || this->board->whosOnBox(posX-i,posY+i)== 10-6)
                return true;
            i++;
            tmpX--;
            tmpY++;

        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 && tmpY > 0){//SZ
            if(this->board->whosOnBox(posX-i,posY-i)== 8-6 || this->board->whosOnBox(posX-i,posY-i)== 10-6)
                return true;
            i++;
            tmpX--;
            tmpY--;
        }

        //copied black horse

        if(posX-1>=0 && posY-2>=0){
            if( this->board->whosOnBox(posX-1,posY-2) == 7-6)
                return true;
        }
        if(posX+1<=7 && posY-2>=0){
            if(this->board->whosOnBox(posX+1,posY-2) == 7-6)
                return true;
        }
        if(posX+2<=7 && posY-1>=0){
            if( this->board->whosOnBox(posX+2,posY-1) == 7-6)
                return true;
        }
        if(posX+2<=7 && posY+1<=7){
            if( this->board->whosOnBox(posX+2,posY+1) == 7-6)
                return true;
        }
        if(posX+1<=7 && posY+2<=7){
            if( this->board->whosOnBox(posX+1,posY+2) == 7-6)
                return true;
        }
        if(posX-1>=0 && posY+2<=7){
            if( this->board->whosOnBox(posX-1,posY+2) == 7-6)
                return true;
        }
        if(posX-2>=0 && posY+1<=7){
            if( this->board->whosOnBox(posX-2,posY+1) == 7-6)
                return true;
        }
        if(posX-2>=0 && posY-1>=0){
            if( this->board->whosOnBox(posX-2,posY-1) == 7-6)
                return true;
        }

        //am I attacked by the pawn?
        if(posX<6 && posY<7 && this->board->whosOnBox(posX+1,posY+1) == 6-6){
            return true;
        }
        if(posX<6 && posY>0 && this->board->whosOnBox(posX+1,posY-1) == 6-6){
            return true;
        }
    }

    return false;
}


void King::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();


    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 5){// if it is black King, or we can say if it is black chesspiece too

        if(posX>0 && posY>0){
            if(this->board->whosOnBox(posX-1,posY-1)==-1 )
                this->validMoves.append(BoardPosition(posX-1,posY-1));
            if(this->board->whosOnBox(posX-1,posY-1) >= 6)
                this->validMoves.append(BoardPosition(posX-1,posY-1));
        }
        if(posY>0){
            if(this->board->whosOnBox(posX,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX,posY-1));
            if(this->board->whosOnBox(posX,posY-1)>= 6)
                this->validMoves.append(BoardPosition(posX,posY-1));
        }
        if(posX<7 && posY>0){
            if(this->board->whosOnBox(posX+1,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY-1));
            if(this->board->whosOnBox(posX+1,posY-1)>= 6)
                this->validMoves.append(BoardPosition(posX+1,posY-1));
        }
        if(posX<7){
            if(this->board->whosOnBox(posX+1,posY)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY));
            if(this->board->whosOnBox(posX+1,posY)>= 6)
                this->validMoves.append(BoardPosition(posX+1,posY));
        }
        if(posX<7 && posY<7){
            if(this->board->whosOnBox(posX+1,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY+1));
            if(this->board->whosOnBox(posX+1,posY+1)>= 6)
                this->validMoves.append(BoardPosition(posX+1,posY+1));
        }
        if(posY<7){
            if(this->board->whosOnBox(posX,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX,posY+1));
            if(this->board->whosOnBox(posX,posY+1)>= 6)
                this->validMoves.append(BoardPosition(posX,posY+1));
        }
        if(posX>0 && posY<7){
            if(this->board->whosOnBox(posX-1,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY+1));
            if(this->board->whosOnBox(posX-1,posY+1)>= 6)
                this->validMoves.append(BoardPosition(posX-1,posY+1));
        }
        if(posX>0){
            if(this->board->whosOnBox(posX-1,posY)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY));
            if(this->board->whosOnBox(posX-1,posY)>= 6)
                this->validMoves.append(BoardPosition(posX-1,posY));
        }
    }else{//its a white King

        if(posX>0 && posY>0){
            if(this->board->whosOnBox(posX-1,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY-1));
            if(this->board->whosOnBox(posX-1,posY-1) < 6)
                this->validMoves.append(BoardPosition(posX-1,posY-1));
        }
        if(posY>0){
            if(this->board->whosOnBox(posX,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX,posY-1));
            if(this->board->whosOnBox(posX,posY-1)< 6)
                this->validMoves.append(BoardPosition(posX,posY-1));
        }
        if(posX<7 && posY>0){
            if(this->board->whosOnBox(posX+1,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY-1));
            if(this->board->whosOnBox(posX+1,posY-1)< 6)
                this->validMoves.append(BoardPosition(posX+1,posY-1));
        }
        if(posX<7){
            if(this->board->whosOnBox(posX+1,posY)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY));
            if(this->board->whosOnBox(posX+1,posY)< 6)
                this->validMoves.append(BoardPosition(posX+1,posY));
        }
        if(posX<7 && posY<7){
            if(this->board->whosOnBox(posX+1,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY+1));
            if(this->board->whosOnBox(posX+1,posY+1)< 6)
                this->validMoves.append(BoardPosition(posX+1,posY+1));
        }
        if(posY<7){
            if(this->board->whosOnBox(posX,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX,posY+1));
            if(this->board->whosOnBox(posX,posY+1)< 6)
                this->validMoves.append(BoardPosition(posX,posY+1));
        }
        if(posX>0 && posY<7){
            if(this->board->whosOnBox(posX-1,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY+1));
            if(this->board->whosOnBox(posX-1,posY+1)< 6)
                this->validMoves.append(BoardPosition(posX-1,posY+1));
        }
        if(posX>0){
            if(this->board->whosOnBox(posX-1,posY)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY));
            if(this->board->whosOnBox(posX-1,posY)< 6)
                this->validMoves.append(BoardPosition(posX-1,posY));
        }
    }
}
