#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King:public ChessPiece
{
public:
    King(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
};

#endif // KING_H
