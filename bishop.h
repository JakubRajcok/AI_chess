#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop:public ChessPiece
{
public:
    Bishop();

    void findValidMoves(BoardPosition& pos);
};

#endif // BISHOP_H
