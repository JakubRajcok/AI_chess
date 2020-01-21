#include "boardposition.h"

BoardPosition::BoardPosition(){
    this->posX=-1;
    this->posY=-1;
}

BoardPosition::BoardPosition (int x, int y){
    this->posX=x;
    this->posY=y;
}

void BoardPosition::setX(int x){
    this->posX=x;
}

void BoardPosition::setY(int y){
    this->posY=y;
}

int BoardPosition::getX() const {
    return this->posX;
}

int BoardPosition::getY()const {
    return this->posY;
}

bool BoardPosition::operator==(const BoardPosition &rhs)
{
    return(posX == rhs.posX && posY == rhs.posY);
}
