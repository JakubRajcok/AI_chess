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




    ChessBoard *getBoard() const;
    void setBoard(ChessBoard *value);

private:
    int getGameMode();
    void setGameMode(int i);
    ChessBoard* board;

signals:
    void validMoves(const QList<BoardPosition>&);
public slots:

    void vyriesKlik(int,int);
};

#endif // GAME_H
