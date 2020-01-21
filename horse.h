#ifndef HORSE_H
#define HORSE_H

#include "chesspiece.h"

class Horse:public ChessPiece
{
public:
    Horse(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
};

#endif // HORSE_H
