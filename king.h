#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King:public ChessPiece
{
public:
    King(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
    bool checking();
};

#endif // KING_H
