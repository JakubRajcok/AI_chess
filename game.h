#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "chessboard.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

    int gameMode;//////////////////////////////////////////////////////////////


private:
    int getGameMode();
    void setGameMode(int i);

signals:

public slots:

    void vyriesPohybStrelca(int,int);
};

#endif // GAME_H
