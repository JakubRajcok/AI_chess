#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook:public ChessPiece
{
public:
    Rook();

    void findValidMoves(BoardPosition& pos);
};

#endif // ROOK_H
