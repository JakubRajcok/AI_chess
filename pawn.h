#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn:public ChessPiece
{
public:
    Pawn(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
};

#endif // PAWN_H
