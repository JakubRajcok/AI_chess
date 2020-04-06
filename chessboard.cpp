#include "chessboard.h"
#include "rook.h"
#include "horse.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <QDebug>

/*
 * Sekcia v ktorej su implementove funkcie na zistovanie validnych tahov
 * TODO
 *  *game a vyhadzocanie
 *  *Prezentacia
 *  *Sprav Spolocny .h file pre vsetky classy
 *  *Spravne volad destruktory
 *  *Make the chess more responsible
 *  *Vycentrovat figutky v bunkach
 *  *Ciernobiele vykreslovanie policok
 *  *Make player viable
 *  *Pozri sa na konkretne figurky sa skus spravit ich optimalizaciu
 *  *kedy je pesiak na konci (cekuj posY aby nesiel tam kam nema)
 *  *vymena figyrky za novy
 *  *Rosada
 *  *asi potrebujes zadefinovat sach premenu boolean, aby si nerobil rosadu po sachu..
 *  *NAJVACIS PRUSER, NEMOZES SA POHNUT, AK ODOKRYJES KRALA A MAS AUTOMATICKY SACH, (PRED CLICK ECENT ZISTI, CI MOZES POHNUT)
 *      -mozno sa skus pytat od krala a vo funkcii volaj vsetky pohyby ostatnych figurok, kore koliduju s tym polickom
 *  *Kingovia neriesia ziadne sachy paty ani maty... dorob
 *
*/

std::vector<ChessPiece *>& ChessBoard::getChessPieceAliveWhite(){
    return ChessPieceAliveWhite;
}

std::vector<ChessPiece *>& ChessBoard::getChessPieceAliveBlack(){
    return ChessPieceAliveBlack;
}

std::vector<ChessPiece *>& ChessBoard::getChessPieceDeadBlack(){
    return this->ChessPieceDeadBlack;
}

std::vector<ChessPiece *>& ChessBoard::getChessPieceDeadWhite(){
    return this->ChessPieceDeadWhite;
}

ChessBoard::ChessBoard(){
    this->actualChessPiece=-1;
    //DYNAMIC ALLOC for my main chessBoard
    int ***arr = new int**[8];
    for (int i = 0; i < 8; ++i) {
        arr[i] = new int*[8];
        for (int j = 0; j < 8; ++j)
            arr[i][j] = new int[12];
    }
    this->board=arr;

    //Filling my board with zeros
    for(int i=0; i<8; i++){
        for (int j=0;j<8;j++){
            for (int k=0;k<12;k++){
                board[i][j][k]=0;
            }
        }
    }

    //INICIALIZATION board:
    //For future, i set -1 at the start of 3rd layer in my boar fo EMPTY box
    //Here Im setting every chessBox for riht chessPiece ID/Type, which contains this chessBox
    //There are ones in specific position of 3rd board layer, which represents chessPiece on it
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(i==0){
                switch (j){
                case 0://BLACK Rook
                    this->board[i][j][3]=1;
                    this->board[i][7][3]=1;

                    break;
                case 1://BLACK Horseman
                    this->board[i][j][1]=1;
                    this->board[i][6][1]=1;
                    break;
                case 2://BLACK Bishop
                    this->board[i][j][2]=1;
                    this->board[i][5][2]=1;
                    break;
                case 3://BLACK Queen
                    this->board[i][j][4]=1;
                    break;
                case 4://BLACK King
                    this->board[i][j][5]=1;
                    break;
                }
            }
            else
                if(i==1){//BLACK Pawns
                    this->board[i][j][0]=1;

                }
                else if(i==6){//White Pawns
                    this->board[i][j][6]=1;

                }
            //Rad nepesiakov WHITE
                else if(i==7){
                    switch (j){
                    case 0://WHITE Rook
                        this->board[i][j][3+6]=1;
                        this->board[i][7][3+6]=1;
                        break;
                    case 1://WHITE Horseman
                        this->board[i][j][1+6]=1;
                        this->board[i][6][1+6]=1;
                        break;
                    case 2://WHITE Bishop
                        this->board[i][j][2+6]=1;
                        this->board[i][5][2+6]=1;
                        break;
                    case 3://WHITE Queen
                        this->board[i][j][4+6]=1;
                        break;
                    case 4://WHITE King
                        this->board[i][j][5+6]=1;
                        break;
                    }
                }else
                    this->board[i][j][0]=-1;
        }
    }

    //INICIALIZATION alive chessPieces:
    //Here Im inicializing new chesspieces of specific type
    //  and im filling the aliveChesspieces containers
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(i==0){
                switch (j){
                /*Black chessPieces*/
                case 0://BLACK Rook
                    this->board[i][j][3]=1;
                    this->board[i][7][3]=1;
                    this->ChessPieceAliveBlack.push_back(new Rook(new BoardPosition(i,j),this));
                    this->ChessPieceAliveBlack.push_back(new Rook(new BoardPosition(i,7),this));
                    break;
                case 1://BLACK Horseman
                    this->board[i][j][1]=1;
                    this->board[i][6][1]=1;
                    this->ChessPieceAliveBlack.push_back(new Horse(new BoardPosition(i,j),this));
                    this->ChessPieceAliveBlack.push_back(new Horse(new BoardPosition(i,6),this));
                    break;
                case 2://BLACK Bishop
                    this->board[i][j][2]=1;
                    this->board[i][5][2]=1;
                    this->ChessPieceAliveBlack.push_back(new Bishop(new BoardPosition(i,j),this));
                    this->ChessPieceAliveBlack.push_back(new Bishop(new BoardPosition(i,5),this));
                    break;
                case 3://BLACK Queen
                    this->board[i][j][4]=1;
                    this->ChessPieceAliveBlack.push_back(new Queen(new BoardPosition(i,j),this));
                    break;
                case 4://BLACK King
                    this->board[i][j][5]=1;
                    this->ChessPieceAliveBlack.push_back(new King(new BoardPosition(i,j),this));
                    break;
                }
            }
            else
                if(i==1){//BLACK Pawns
                    this->board[i][j][0]=1;
                    this->ChessPieceAliveBlack.push_back(new Pawn(new BoardPosition(i,j),this));
                }
                /*White Chesspieces*/
                else if(i==6){//White Pawns
                    this->board[i][j][6]=1;
                    ChessPieceAliveWhite.push_back(new Pawn(new BoardPosition(i,j),this));
                }
                else if(i==7){
                    switch (j){
                    case 0://WHITE Rook
                        this->board[i][j][3+6]=1;
                        this->board[i][7][3+6]=1;
                        ChessPieceAliveWhite.push_back(new Rook(new BoardPosition(i,j),this));
                        ChessPieceAliveWhite.push_back(new Rook(new BoardPosition(i,7),this));
                        break;
                    case 1://WHITE Horseman
                        this->board[i][j][1+6]=1;
                        this->board[i][6][1+6]=1;
                        ChessPieceAliveWhite.push_back(new Horse(new BoardPosition(i,j),this));
                        ChessPieceAliveWhite.push_back(new Horse(new BoardPosition(i,6),this));
                        break;
                    case 2://WHITE Bishop
                        this->board[i][j][2+6]=1;
                        this->board[i][5][2+6]=1;
                        ChessPieceAliveWhite.push_back(new Bishop(new BoardPosition(i,j),this));
                        ChessPieceAliveWhite.push_back(new Bishop(new BoardPosition(i,5),this));
                        break;
                    case 3://WHITE Queen
                        this->board[i][j][4+6]=1;
                        ChessPieceAliveWhite.push_back(new Queen(new BoardPosition(i,j),this));
                        break;
                    case 4://WHITE King
                        this->board[i][j][5+6]=1;
                        ChessPieceAliveWhite.push_back(new King(new BoardPosition(i,j),this));
                        break;
                    }
                }else
                    this->board[i][j][0]=-1;
        }
    }
}

int*** ChessBoard::getBoard(){
    return this->board;
}

void ChessBoard::deleteBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            delete[] this->board[i][j];
        delete[] this->board[i];
    }
    delete[] getBoard();
}

ChessBoard::~ChessBoard(){
    deleteBoard();
}

//This function returns the specific type of chessPiece base on board position
int ChessBoard::whosOnBox(int posX, int posY){//Ked Kliknes odpoveda ti board
    /********************
     * ret> ID of piece *
     * ret -1 > Empty   *
     ********************/
    const int posZ=0;

    //If chess box is empty
    if(this->board[posX][posY][posZ] == -1){
        return -1;
    }

    //returning index, where is one, thats ID of my chesspiece
    //for example "0" is black pawn, "6" is white pawn etc.
    for(int i=0;i<12;i++){
        if(this->board[posX][posY][posZ+i] > 0)
            //Return of int in interval <0,11>
            return i;
    }

    throw("Invalid 3rd layer array in board -> chessBoard");
}

//Function which returns Chesspiece based on posted gameMode
//If its gameMode == 0 (it means that its black turn), then im looking in black chessPieces
ChessPiece* ChessBoard::chesspieceOnBox(const BoardPosition &bp, int mode){

    //Im looking for chesspiece to move or chesspiece to kickOut (black's move or white kicking)
    if(mode==0 || mode==3){
        for(auto &cp : this->ChessPieceAliveBlack ){
            if(cp->getPosition()->getX() == bp.getX() && cp->getPosition()->getY() == bp.getY())
                return cp;
        }
    //Im looking for chesspiece to move or chesspiece to kickOut (white's move or black kicking)
    }else if(mode == 1 || mode==2){
        for(auto &cp : this->ChessPieceAliveWhite ){
            if(cp->getPosition()->getX() == bp.getX() && cp->getPosition()->getY() == bp.getY())
                return cp;
        }
    }
    return nullptr;

}
