#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "chessboard.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game( QObject *parent = nullptr);

    int gameMode;//////////////////////////////////////////////////////////////



    int getGameMode();
    void setGameMode(int i);
    ChessBoard *getBoard() const;
    void setBoard(ChessBoard *value);
    void makeMove(ChessPiece* toByMoved,int row,int col);

private:

    ChessBoard* board;
    ChessPiece* clickedChessPiece;

signals:
    void validMoves(const QList<BoardPosition>&);
    void updateChessboardSignal(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w);
public slots:

    void vyriesKlik(int,int);
};

#endif // GAME_H
