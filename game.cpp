#include "game.h"
#include <QDebug>
Game::Game(QObject *parent) : QObject(parent)
{

}

void Game::vyriesPohybStrelca(int s, int e)
{
 qDebug() << s << " " << e;
}
