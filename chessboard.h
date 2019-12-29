#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "king.h"
#include "boardposition.h"
#include <vector>

class ChessBoard{
private:
     int ***board;
     King kingBlack;
     King kingWhite;
     int actualChessPiece;
     std::vector<BoardPosition> validMoves;
public:
    ChessBoard();
    void draw_board();
    void draw_pawns();
    int*** getBoard();
    std::vector<BoardPosition> *findValidMoves(int posX,int posY);
    int whosOnBox(  int posX, int posY);
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
};

#endif // CHESSBOARD_H
