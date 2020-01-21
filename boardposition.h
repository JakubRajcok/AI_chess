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
    int getX() const;
    int getY() const ;
    bool operator==(const BoardPosition& rhs);
};

#endif // BOARDPOSITION_H
