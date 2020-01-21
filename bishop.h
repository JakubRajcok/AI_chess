#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop:public ChessPiece
{
public:
    Bishop(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
};

#endif // BISHOP_H
