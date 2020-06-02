#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chesspiece.h"
#include "boardposition.h"
#include <vector>

class ChessPiece;
class ChessBoard{

private:
     int ***board;
     int actualChessPiece;
     std::vector<BoardPosition> validMoves;
     std::vector<ChessPiece*> ChessPieceAliveWhite;
     std::vector<ChessPiece*> ChessPieceAliveBlack;
     std::vector<ChessPiece*> ChessPieceDeadWhite{};
     std::vector<ChessPiece*> ChessPieceDeadBlack{};
public:
    ChessBoard();
    ChessBoard(QString fen);
    void draw_board();
    void draw_pawns();
    int*** getBoard();
    std::vector<BoardPosition> *findValidMoves(int posX,int posY);
    int whosOnBox( int posX, int posY);
    void deleteBoard();
    void validMovesBlackPawn(int posX, int posY, std::vector<BoardPosition> *out, BoardPosition &position);
    void validMovesWhitePawn(int posX, int posY, std::vector<BoardPosition> *out, BoardPosition &position);
    void validMovesBlackRook(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesWhiteRook(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesBlackHorseman(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesWhiteHorseman(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesBlackBishop(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesWhiteBishop(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesBlackQueen(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesWhiteQueen(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesBlackKing(int posX, int posY, std::vector<BoardPosition> *out);
    void validMovesWhiteKing(int posX, int posY, std::vector<BoardPosition> *out);
    ~ChessBoard();
    std::vector<ChessPiece *> &getChessPieceAliveWhite();
    std::vector<ChessPiece *> &getChessPieceAliveBlack();
    std::vector<ChessPiece *> &getChessPieceDeadBlack();
    std::vector<ChessPiece *> &getChessPieceDeadWhite();
    ChessPiece* chesspieceOnBox(const BoardPosition&, int);
    int evaluateFenLetToType(QChar ch);
};

#endif // CHESSBOARD_H
