#include "king.h"

King::King(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    findValidMoves();
}

void King::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();


    //there was change, we need to claer data from vector
    this->validMoves.clear();

    if(this->type == 1){// if it is black King, or we can say if it is black chesspiece too

        //No mily moj, tu potrebujes sledovat, ci ta niekto po tvojom super pohybe nebude sachovat, enjoy :)

        if(posX>0 && posY>0){
            if(this->board->whosOnBox(posX-1,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY-1));
            if(this->board->whosOnBox(posX-1,posY-1) > 5)
                this->validMoves.append(BoardPosition(posX-1,posY-1));
        }
        if(posY>0){
            if(this->board->whosOnBox(posX,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX,posY-1));
            if(this->board->whosOnBox(posX,posY-1)>5)
                this->validMoves.append(BoardPosition(posX,posY-1));
        }
        if(posX<7 && posY>0){
            if(this->board->whosOnBox(posX+1,posY-1)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY-1));
            if(this->board->whosOnBox(posX+1,posY-1)>5)
                this->validMoves.append(BoardPosition(posX+1,posY-1));
        }
        if(posX<7){
            if(this->board->whosOnBox(posX+1,posY)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY));
            if(this->board->whosOnBox(posX+1,posY)>5)
                this->validMoves.append(BoardPosition(posX+1,posY));
        }
        if(posX<7 && posY<7){
            if(this->board->whosOnBox(posX+1,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX+1,posY+1));
            if(this->board->whosOnBox(posX+1,posY+1)>5)
                this->validMoves.append(BoardPosition(posX+1,posY+1));
        }
        if(posY<7){
            if(this->board->whosOnBox(posX,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX,posY+1));
            if(this->board->whosOnBox(posX,posY+1)>5)
                this->validMoves.append(BoardPosition(posX,posY+1));
        }
        if(posX>0 && posY<7){
            if(this->board->whosOnBox(posX-1,posY+1)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY+1));
            if(this->board->whosOnBox(posX-1,posY+1)>5)
                this->validMoves.append(BoardPosition(posX-1,posY+1));
        }
        if(posX>0){
            if(this->board->whosOnBox(posX-1,posY)==-1)
                this->validMoves.append(BoardPosition(posX-1,posY));
            if(this->board->whosOnBox(posX-1,posY)>5)
                this->validMoves.append(BoardPosition(posX-1,posY));
        }
    }else{//its a white King

        //____________________No mily moj, tu potrebujes sledovat, ci ta niekto po tvojom super pohybe nebude sachovat, enjoy :)

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
