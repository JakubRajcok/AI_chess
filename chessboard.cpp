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
 *  *Spravne volad destruktory
 *  *Make the chess more responsible
 *  *Ciernobiele vykreslovanie policok
 *  *pesiak prechod na koniec sachovnice
 *  *Rosada
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

ChessBoard::ChessBoard(QString fen){
    if(board != nullptr)
        deleteBoard();

    //Safely dealocating memmory of all chessboard members
    while( !this->getChessPieceAliveBlack().empty() ){
        delete this->getChessPieceAliveBlack().at(0);
        this->getChessPieceAliveBlack().erase(this->getChessPieceAliveBlack().begin());
    }
    while( !this->getChessPieceDeadBlack().empty() ){
        delete this->getChessPieceDeadBlack().at(0);
        this->getChessPieceDeadBlack().erase(this->getChessPieceDeadBlack().begin());
    }
    while( !this->getChessPieceAliveWhite().empty() ){
        delete this->getChessPieceAliveWhite().at(0);
        this->getChessPieceAliveWhite().erase(this->getChessPieceAliveWhite().begin());
    }
    while( !this->getChessPieceDeadWhite().empty() ){
        delete this->getChessPieceDeadWhite().at(0);
        this->getChessPieceDeadWhite().erase(this->getChessPieceDeadWhite().begin());
    }

    QString inFen = fen.left(44);
    int inFenLen = inFen.length();

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

    int ch=0;
    //Inicializing the board based on fen string
    for(int i=0; i<8; i++){
        for ( int j=0; j<8;j++){
            //if its slash, than ignore it
            if(inFen[ch] == '/'){
                ch++;
            //if its number, than make another loop and make empty boxes
            }else if(inFen[ch].isDigit()){
                //these are empty boxes, so i just move 2nd dimension by oofset and give -1 to 0. index of 3rd dimension
                for(int tmpNo = 0; tmpNo < inFen[ch].digitValue(); tmpNo++){
                    this->board[i][j+tmpNo][0] = -1;
                }
                ch++;
            //If it is letter, get its code and write it dawn to the board
            }else if(inFen[ch].isLetter()){
                int typeOfFenLetter = evaluateFenLetToType(inFen[ch]);
                this->board[i][j][typeOfFenLetter] = 1;
                ch++;
            }
        }
    }

    int noOfBPawn,noOfWPawn = 0;
    int noOfBKnight,noOfWKnight = 0;
    int noOfBBishop, noOfWBishop = 0;
    int noOfBRook,noOfWRook = 0;
    int noOfBQueen,noOfWQueen = 0;

    for(int i = 0; i< 8;i++){
        for (int j=0;j<8;j++){
            int typePiece = whosOnBox(i,j);

            switch (typePiece){
                case 0:
                    this->ChessPieceAliveBlack.push_back(new Pawn(new BoardPosition(i,j),this));
                    noOfBPawn++;
                    break;
                case 1:
                    this->ChessPieceAliveBlack.push_back(new Horse(new BoardPosition(i,j),this));
                    noOfBKnight++;
                    break;
                case 2:
                    this->ChessPieceAliveBlack.push_back(new Bishop(new BoardPosition(i,j),this));
                    noOfBBishop++;
                    break;
                case 3:
                    this->ChessPieceAliveBlack.push_back(new Rook(new BoardPosition(i,j),this));
                    noOfBRook++;
                    break;
                case 4:
                    this->ChessPieceAliveBlack.push_back(new Queen(new BoardPosition(i,j),this));
                    noOfBQueen++;
                    break;
                case 5:
                    this->ChessPieceAliveBlack.push_back(new King(new BoardPosition(i,j),this));
                    break;
                //white one
                case 6:
                    this->ChessPieceAliveWhite.push_back(new Pawn(new BoardPosition(i,j),this));
                    noOfWPawn++;
                    break;
                case 7:
                    this->ChessPieceAliveWhite.push_back(new Horse(new BoardPosition(i,j),this));
                    noOfWKnight++;
                    break;
                case 8:
                    this->ChessPieceAliveWhite.push_back(new Bishop(new BoardPosition(i,j),this));
                    noOfWBishop++;
                    break;
                case 9:
                    this->ChessPieceAliveWhite.push_back(new Rook(new BoardPosition(i,j),this));
                    noOfWRook++;
                    break;
                case 10:
                    this->ChessPieceAliveWhite.push_back(new Queen(new BoardPosition(i,j),this));
                    noOfWQueen++;
                    break;
                case 11:
                    this->ChessPieceAliveWhite.push_back(new King(new BoardPosition(i,j),this));
                    break;
            }
        }
    }
    //Appending array of dead chesspieces based on live ones
    while(noOfBPawn != 8 && noOfWPawn != 8 && noOfBKnight != 2 && noOfWKnight != 2 && noOfBBishop != 2 && noOfWBishop != 2 && noOfBRook != 2 && noOfWRook != 2 && noOfBQueen != 1 && noOfWQueen != 1 ){

        if(noOfBPawn != 8){
            this->ChessPieceDeadBlack.push_back(new Pawn());
            this->ChessPieceDeadBlack.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadBlack.back()->setColor(0);
            this->ChessPieceDeadBlack.back()->setIsPlaced(false);
            this->ChessPieceDeadBlack.back()->setType(0);
            this->ChessPieceDeadBlack.back()->setBoard(this);
            noOfBPawn++;
        }
        if(noOfWPawn != 8){
            this->ChessPieceDeadWhite.push_back(new Pawn());
            this->ChessPieceDeadWhite.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadWhite.back()->setColor(1);
            this->ChessPieceDeadWhite.back()->setIsPlaced(false);
            this->ChessPieceDeadWhite.back()->setType(6);
            this->ChessPieceDeadWhite.back()->setBoard(this);
            noOfWPawn++;
        }
        if(noOfBKnight != 2){
            this->ChessPieceDeadBlack.push_back(new Horse());
            this->ChessPieceDeadBlack.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadBlack.back()->setColor(0);
            this->ChessPieceDeadBlack.back()->setIsPlaced(false);
            this->ChessPieceDeadBlack.back()->setType(1);
            this->ChessPieceDeadBlack.back()->setBoard(this);
            noOfBKnight++;
        }
        if(noOfWKnight != 2){
            this->ChessPieceDeadWhite.push_back(new Horse());
            this->ChessPieceDeadWhite.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadWhite.back()->setColor(1);
            this->ChessPieceDeadWhite.back()->setIsPlaced(false);
            this->ChessPieceDeadWhite.back()->setType(7);
            this->ChessPieceDeadWhite.back()->setBoard(this);
            noOfWKnight++;
        }
        if(noOfBBishop != 2){
            this->ChessPieceDeadBlack.push_back(new Bishop());
            this->ChessPieceDeadBlack.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadBlack.back()->setColor(0);
            this->ChessPieceDeadBlack.back()->setIsPlaced(false);
            this->ChessPieceDeadBlack.back()->setType(2);
            this->ChessPieceDeadBlack.back()->setBoard(this);
            noOfBBishop++;
        }
        if(noOfWBishop != 2){
            this->ChessPieceDeadWhite.push_back(new Bishop());
            this->ChessPieceDeadWhite.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadWhite.back()->setColor(1);
            this->ChessPieceDeadWhite.back()->setIsPlaced(false);
            this->ChessPieceDeadWhite.back()->setType(8);
            this->ChessPieceDeadWhite.back()->setBoard(this);
            noOfWBishop++;
        }
        if(noOfBRook != 2){
            this->ChessPieceDeadBlack.push_back(new Rook());
            this->ChessPieceDeadBlack.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadBlack.back()->setColor(0);
            this->ChessPieceDeadBlack.back()->setIsPlaced(false);
            this->ChessPieceDeadBlack.back()->setType(3);
            this->ChessPieceDeadBlack.back()->setBoard(this);
            noOfBRook++;
        }
        if(noOfWRook != 2){
            this->ChessPieceDeadWhite.push_back(new Rook());
            this->ChessPieceDeadWhite.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadWhite.back()->setColor(1);
            this->ChessPieceDeadWhite.back()->setIsPlaced(false);
            this->ChessPieceDeadWhite.back()->setType(9);
            this->ChessPieceDeadWhite.back()->setBoard(this);
            noOfWRook++;
        }
        if(noOfBQueen != 1){
            this->ChessPieceDeadBlack.push_back(new Queen());
            this->ChessPieceDeadBlack.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadBlack.back()->setColor(0);
            this->ChessPieceDeadBlack.back()->setIsPlaced(false);
            this->ChessPieceDeadBlack.back()->setType(4);
            this->ChessPieceDeadBlack.back()->setBoard(this);
            noOfBQueen++;
        }
        if(noOfWQueen != 1){
            this->ChessPieceDeadWhite.push_back(new Queen());
            this->ChessPieceDeadWhite.back()->setPosition(new BoardPosition(0,0));
            this->ChessPieceDeadWhite.back()->setColor(1);
            this->ChessPieceDeadWhite.back()->setIsPlaced(false);
            this->ChessPieceDeadWhite.back()->setType(10);
            this->ChessPieceDeadWhite.back()->setBoard(this);
            noOfWQueen++;
        }
    }

}

int ChessBoard::evaluateFenLetToType(QChar ch){
    if(ch == 'p')
        return 0;
    if(ch == 'n')
        return 1;
    if(ch == 'b')
        return 2;
    if(ch == 'r')
        return 3;
    if(ch == 'q')
        return 4;
    if(ch == 'k')
        return 5;
    if(ch == 'P')
        return 6;
    if(ch == 'N')
        return 7;
    if(ch == 'B')
        return 8;
    if(ch == 'R')
        return 9;
    if(ch == 'Q')
        return 10;
    if(ch == 'K')
        return 11;
    return -1;
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
                    //this->setBlackKing(new King(new BoardPosition(i,j),this));
                    //this->ChessPieceAliveBlack.push_back(this->getBlackKing());
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
                        //this->setWhiteKing(new King(new BoardPosition(i,j),this));
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
    this->board = nullptr;
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
