#ifndef HORSE_H
#define HORSE_H

#include "chesspiece.h"

class Horse:public ChessPiece
{
public:
    Horse();

    void findValidMoves(BoardPosition &pos);
};

#endif // HORSE_H
