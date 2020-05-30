#ifndef GAME_H
#define GAME_H


#include <QObject>
#include "chessboard.h"
#include <QChar>
#include <QString>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game( QObject *parent = nullptr);
    int gameMode;
    int getGameMode();
    void setGameMode(int i);
    ChessBoard *getBoard() const;
    void setBoard(ChessBoard *value);
    void makeMove(ChessPiece* toByMoved,int row,int col);
    void clearingChessBoxes(int oldY, int newX, int*** brd, int oldX, int newY);
    void kickChessPieceOut(ChessPiece* toBeKicked);
    
    bool checkIfClickedValidMove(int col, int row);

    QString generateFEN();
    QChar intToLetter(int chessId);

    QString createLetterFromRow(int pos);
    void solvePawnChange();
    int convertChessAnotationPos1(QChar n);

    void solveEnPassant(int whoWasClicked, int col, int row);
    void makeEnPassant(ChessPiece* toBeMoved,int row,int col);
    void clearingChessBoxes(int oldY, int newX, int*** brd, int oldX, int newY, int enPassY, int enPassX);


private:
    int moveCounter;
    int halfMoveCounter=0;
    bool startPosPawn=false;
    bool blackKingSideCastling=true;
    bool blackQueenSideCastling=true;
    bool whiteKingSideCastling=true;
    bool whiteQueenSideCastling=true;
    int movedChessPiece;
    ChessBoard* board;
    ChessPiece* clickedChessPiece;
    QString fen;

signals:
    void appendLog(QString s);
    void appendLog(const QList<BoardPosition>&);
    void validMoves(const QList<BoardPosition>&);
    void updateChessboardSignal(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w);
public slots:

    void solveClick(int,int);
};

#endif // GAME_H
