#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King:public ChessPiece
{
public:
    King();

    void findValidMoves(BoardPosition &pos);
};

#endif // KING_H
