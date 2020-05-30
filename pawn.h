#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn:public ChessPiece
{
private:
    bool boardEnd = false;

public:
    Pawn(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);


    void findValidMoves();
    bool getBoardEnd() const;
    void setBoardEnd(bool value);
};

#endif // PAWN_H
