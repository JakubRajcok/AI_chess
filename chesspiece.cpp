#include "chesspiece.h"
#include "boardposition.h"
#include "chessboard.h"
#include <QDebug>

int ChessPiece::getType() const{
    return type;
}

BoardPosition *ChessPiece::getPosition() const{
    return position;
}

void ChessPiece::setPosition(BoardPosition *value){
    position = value;
}

QString ChessPiece::getIconName() const{
    return iconName;
}

void ChessPiece::setIconName(const QString &value){
    iconName = value;
}

bool ChessPiece::amIChecking(){
    //if there are valid moves, check, if enemy King is checked
    //if valid moves exists and are bigger then 0
    if(this->validMoves.size() > 0){
        for(BoardPosition &cp : this->validMoves) {
            //if my valid moves contains boardposition with oposite king
            if(this->board->whosOnBox(cp.getX(),cp.getY()) == 5 || this->board->whosOnBox(cp.getX(),cp.getY()) == 11)
                return true;
        }
    }
    return false;
}

ChessPiece::ChessPiece(BoardPosition *pos, ChessBoard *board){
    this->position=new BoardPosition(pos->getX(),pos->getY());
    this->board=board;
    this->type=this->board->whosOnBox(pos->getX(),pos->getY());
    this->isPlaced=true;
    this->checking=false;
    if(whosOnBox(*pos)<6)
        this->color=0;
    else
        this->color=1;

}

QList<BoardPosition>& ChessPiece::getValidMoves(){
    return this->validMoves;
}

ChessPiece::~ChessPiece(){
    delete(this->position);
}

//Overrided function of chessBoard, for better handling with code
int ChessPiece::whosOnBox(BoardPosition &pos){
    /*******************
     * ret> ID of pawn *
     * ret -1 > Empty  *
     *******************/
    int posX=pos.getX();
    int posY=pos.getY();

    return this->board->whosOnBox(posX,posY);
}

void ChessPiece:: setIsPlaced(bool placed){
    this->isPlaced=placed;
}
