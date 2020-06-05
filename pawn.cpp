#include "pawn.h"

//potrebujem invoke of ChessPiece(BoardPosition &pos, ChessBoard *board);

bool Pawn::getBoardEnd() const
{
    return boardEnd;
}

void Pawn::setBoardEnd(bool value)
{
    boardEnd = value;
}

Pawn::Pawn(BoardPosition *pos, ChessBoard *board): ChessPiece(pos,board)
{
    findValidMoves();
    if(this->type == 0){//black bishop
        this->iconName = "pawn0.png";
    }else{
        this->iconName = "pawn1.png";
    }
}

void Pawn::findValidMoves(){
    int posX=this->position->getX();
    int posY=this->position->getY();

    //If I am on the end of the board
    if(posX == 6 && this->color == 0)
        this->boardEnd = true;
    else if(posX == 1 && this->color == 1)
        this->boardEnd = true;

    //there was change, we need to clear data from vector
    this->validMoves.clear();

    if(this->type == 0){// if it is black pawn, or we can say if it is black chesspiece too
        //If its 1st move, then we can move two boxes forward
        if(posX == 1){
            if( this->board->whosOnBox(posX+1,posY) == -1 && this->board->whosOnBox(posX+2,posY) == -1 ){
                this->validMoves.append(BoardPosition(posX+2,posY));
            }
        }
        //is place in front free?
        if(posX < 7 && this->board->whosOnBox(posX+1,posY)==-1){
            this->validMoves.append(BoardPosition(posX+1,posY));
        }
        //may I attack someone?
        if(posX<7 && posY<7 && this->board->whosOnBox(posX+1,posY+1)>5){
            this->validMoves.append(BoardPosition(posX+1,posY+1));
        }
        //may I attack someone?
        if(posX<7 && posY>0 && this->board->whosOnBox(posX+1,posY-1)>5){
            this->validMoves.append(BoardPosition(posX+1,posY-1));
        }

    }else{// chesspiece is white pawn
        if(posX == 6){
            if( this->board->whosOnBox(posX-1,posY) == -1 && this->board->whosOnBox(posX-2,posY) == -1 ){
                this->validMoves.append(BoardPosition(posX-2,posY));
            }
        }
        //is place before free?
        if(posX>0 && this->board->whosOnBox(posX-1,posY)==-1){
            this->validMoves.append(BoardPosition(posX-1,posY));
        }
        //may I attack someone SZ?
        if(posX>0 && posY>0 && this->board->whosOnBox(posX-1,posY-1)<=5 && this->board->whosOnBox(posX-1,posY-1)!=-1){
            this->validMoves.append(BoardPosition(posX-1,posY-1));
        }
        //may I attack someone?
        if(posX>0 && posY<7 && this->board->whosOnBox(posX-1,posY+1)<=5 && this->board->whosOnBox(posX-1,posY+1)!=-1){
            this->validMoves.append(BoardPosition(posX-1,posY+1));
        }
    }

    //am I checking?
    this->checking = this->amIChecking();
}
