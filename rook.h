#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook:public ChessPiece
{
public:
    Rook(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
};

#endif // ROOK_H
