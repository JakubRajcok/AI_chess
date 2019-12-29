#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include "boardposition.h"
#include "chessboard.h"

class ChessPiece:public QGraphicsPixmapItem
{
public:

    ChessPiece();
    ChessPiece(BoardPosition &pos, ChessBoard *board);


    void setPosition(BoardPosition *position);
    BoardPosition* getBoardPosition();

    void setColor(int color);
    int getColor();

    void setIsPlaced(bool placed);
    bool getIsPlaced();

    void findValidMoves();
    QList<BoardPosition>* getValidMoves();

    int whosOnBox(BoardPosition &pos);
    ~ChessPiece();

protected:

    /*

    */
    int type; // number from 0 to 11 representing exact type of chesspiece
    BoardPosition *position;
    int color; //0-black, 1-white
    bool isPlaced;
    QList <BoardPosition> validMoves;
    ChessBoard *board;

};

#endif // CHESSPIECE_H
