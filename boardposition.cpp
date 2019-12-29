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

BoardPosition::getX(){
    return this->posX;
}

BoardPosition::getY(){
    return this->posY;
}
