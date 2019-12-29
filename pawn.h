#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn:public ChessPiece
{
public:
    Pawn();

    void findValidMoves(BoardPosition &pos);
};

#endif // PAWN_H
