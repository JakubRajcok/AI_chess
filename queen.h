#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen:public ChessPiece
{
public:
    Queen();

    void findValidMoves(BoardPosition& pos);
};

#endif // QUEEN_H
