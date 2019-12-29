#include "King.h"

King::King(){
    this->color=-1;
}

King::King(int color,BoardPosition position){
    this->color=color;
    this->position=position;
    this->check=false;
}

