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
    void clearingChessBoxes(int oldY, int newX, int*** brd, int oldX, int newY);
    void kickChessPieceOut(ChessPiece* toBeKicked);
    
    bool checkIfClickedValidMove(int col, int row);

private:

    ChessBoard* board;
    ChessPiece* clickedChessPiece;

signals:
    void appendLog(const QList<BoardPosition>&);
    void validMoves(const QList<BoardPosition>&);
    void updateChessboardSignal(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w);
public slots:

    void solveClick(int,int);
};

#endif // GAME_H
