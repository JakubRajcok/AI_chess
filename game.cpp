#include "game.h"
#include <QDebug>

#include "chessboard.h"
#include "player.h"

Game::Game(QObject *parent) : QObject(parent)
{
/*
Nastavenie game mode 0 -> taha biely
Cakaj na signal a po klki prejdi pole figurok a porovnaj ich pozicie
Prepni gamemode na -1 a vysviet validne tahy kliknutej figurky
po kliknuti na rovnaku figurku nastav gamemode 0 (white)
po kliknuti na vlaidne policko prepis klavesnicu a nastav game mode 1 (bklack)
*/

}

void Game::vyriesPohybStrelca(int s, int e)
{
 qDebug() << s << " " << e;
}
