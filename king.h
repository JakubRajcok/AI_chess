#ifndef KING_H
#define KING_H

#include "boardposition.h"

class King{
    int color;//0-black, 1-white
    bool check;//if checked
    BoardPosition position;//where is he?
public:
    King();
    King(int color,BoardPosition position);
};

#endif // KING_H
