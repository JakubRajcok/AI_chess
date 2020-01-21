#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include "boardposition.h"
#include "chessboard.h"

class ChessBoard;
class ChessPiece:public QGraphicsPixmapItem
{

protected:

    /*

    */
    int type; // number from 0 to 11 representing exact type of chesspiece
    BoardPosition *position;
    int color; //0-black, 1-white
    bool isPlaced;
    QList <BoardPosition> validMoves;
    ChessBoard *board;

public:

    ChessPiece(BoardPosition *pos = nullptr, ChessBoard *board = nullptr);

    void setColor(int color);
    int getColor();

    void setIsPlaced(bool placed);
    bool getIsPlaced();

    const QList<BoardPosition> &getValidMoves();

    int whosOnBox(BoardPosition &pos);
    ~ChessPiece();


    int getType() const;
    BoardPosition *getPosition() const;
    void setPosition(BoardPosition *value);


};

#endif // CHESSPIECE_H
