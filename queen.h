#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen:public ChessPiece
{
public:
    Queen(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
};

#endif // QUEEN_H
