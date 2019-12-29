#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

signals:

public slots:

    void vyriesPohybStrelca(int,int);
};

#endif // GAME_H
