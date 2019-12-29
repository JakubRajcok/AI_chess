#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H


class BoardPosition{
    int posX;
    int posY;
public:
    BoardPosition();
    BoardPosition(int x, int y);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
};

#endif // BOARDPOSITION_H
