#include "game.h"
#include <QDebug>

#include "chessboard.h"
#include "player.h"
#include <algorithm>

Game::Game(QObject *parent) : QObject(parent), board{new ChessBoard}{
    this->gameMode = 0;
    this->clickedChessPiece=nullptr;
}

ChessBoard *Game::getBoard() const{
    return board;
}

void Game::setBoard(ChessBoard *value){
    board = value;
}

void Game::clearingChessBoxes(int oldY, int newX, int*** brd, int oldX, int newY){
    //Setting "from" position like empty box
    for(int i=0;i<12;i++){
        if(i==0)
            brd[oldX][oldY][i] = -1;
        else
            brd[oldX][oldY][i] = 0;
    }

    //Setting "to" position like empty box
    for(int i=0;i<12;i++){
        if(i==0)
            brd[newX][newY][i] = -1;
        else
            brd[newX][newY][i] = 0;
    }
}

void Game::kickChessPieceOut(ChessPiece* toBeKicked){
    std::vector<ChessPiece*>::iterator begin;
    std::vector<ChessPiece*>::iterator end;
    std::vector<ChessPiece*> aliveChessPieces;
    std::vector<ChessPiece*> deadChessPieces;

    //If the black player is taking the white chesspiece
    if(toBeKicked->getType() >= 6){
        begin = this->board->getChessPieceAliveWhite().begin();
        end = this->board->getChessPieceAliveWhite().end();
        deadChessPieces = this->board->getChessPieceDeadWhite();
        this->gameMode = 1;
    //If the white player is taking the black chesspiece
    }else if(toBeKicked->getType() < 6){
        begin = this->board->getChessPieceAliveBlack().begin();
        end = this->board->getChessPieceAliveBlack().end();
        deadChessPieces = this->board->getChessPieceDeadBlack();
        this->gameMode = 0;
    }

    for(; begin != end ; begin++){
        if(*begin == toBeKicked  ){
            //aliveChessPieces.erase(begin);
            if(toBeKicked->getType() >= 6)
                this->board->getChessPieceAliveWhite().erase(begin);
            else
                this->board->getChessPieceAliveBlack().erase(begin);
            this->clickedChessPiece=nullptr;
            break;
        }
    }

    deadChessPieces.push_back(toBeKicked);
    toBeKicked->setIsPlaced(false);
    toBeKicked->getPosition()->setX(-1);
    toBeKicked->getPosition()->setY(-1);
}

void Game::makeMove(ChessPiece* toBeMoved,int row,int col){

    int typeOfChessPiece = toBeMoved->getType();
    int oldX= toBeMoved->getPosition()->getX();
    int oldY= toBeMoved->getPosition()->getY();
    ChessPiece* toBeKicked = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
    int newX=row;
    int newY=col;
    int*** brd = board->getBoard();
    int whosOnBox = this->board->whosOnBox(row,col);

    //Setting "to" & "from" position like empty box
    clearingChessBoxes(oldY, newX, brd, oldX, newY);

    //One of the player is going to kick out enemy chesspiece
    //  if the clicked ("to") box wasn't empty
    if(whosOnBox != -1){
        kickChessPieceOut(toBeKicked);
    }

    //making "to" position valid
    for(int i=0;i<12;i++){
        if(i == typeOfChessPiece)
            brd[newX][newY][i] = 1;
        else
            brd[newX][newY][i]=0;
    }

    //Redefining old position atribute in chessPiece
    toBeMoved->getPosition()->setX(newX);
    toBeMoved->getPosition()->setY(newY);

    return;
}


bool Game::checkIfClickedValidMove(int row, int col){
    //I the clicked box was in valid moves of clicked chessPiece
    for(const BoardPosition &b : this->clickedChessPiece->getValidMoves()){
        if(b.getX() == row && b.getY() == col)
            return true;
    }
    //Cant find right boarPosition
    return false;
}

void Game::solveClick(int row, int col){

    int whoWasClicked = this->board->whosOnBox(row,col);

    //If the place where i clicked whas empty box
    if (whoWasClicked == -1){
        //If my chesspiece was chosen and i want to move on empty box
        if(gameMode == 2 || gameMode ==3){
            //Finding valid moves for clicked Chesspiece
            this->clickedChessPiece->findValidMoves();
            //Drawing valid moves
            emit validMoves(this->clickedChessPiece->getValidMoves());

            if( checkIfClickedValidMove(row,col) ){
                makeMove(this->clickedChessPiece, row, col);

                //Switching gamemode for opponents turn
                if(this->gameMode == 2)
                    this->gameMode = 1;
                else
                    this->gameMode = 0;

                //Unclick my actual Chesspiece
                this->clickedChessPiece = nullptr;
                //Redrawing the chessBoard
                emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());

                return;
            }
        }
        //Click on empty box
        return;
    }

    //if i am black and i choose 1st chesspiece white or if i am white and i choose 1st chesspiece black
    if( (gameMode == 0 && whoWasClicked>=6) || (gameMode == 1 && whoWasClicked<6) ){
        return;
    }

    //Its a Black turn
    if(this->gameMode == 0 || gameMode == 2){

        //if I am black and i clicked on black chesspiece which i want to move
        if(whoWasClicked<6 && this->clickedChessPiece == nullptr){
            this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
            this->clickedChessPiece->findValidMoves();
            emit appendLog(this->clickedChessPiece->getValidMoves());

            //If i cicked corectly, but my chosen chesspiece got no validmoves
            if(this->clickedChessPiece->getValidMoves().size()<=0){
                this->clickedChessPiece=nullptr;
                return;
            }

            //If i clicked corectly and there are valid moves
            //Inicialization of clicked chesspiese and changing the gameMode
            this->gameMode = this->gameMode+2;
            emit validMoves(this->clickedChessPiece->getValidMoves());
            return;
        }

        //if i clicked same chesspiece twice
        if(this->gameMode == 2 && this->clickedChessPiece->getPosition()->getX() == row && this->clickedChessPiece->getPosition()->getY() == col ){
            this->clickedChessPiece=nullptr;
            this->gameMode= this->gameMode-2;
            return;
        }

    //Its a White Turn
    }else if(this->gameMode == 1 || gameMode == 3){

        //if I am white and i clicked on white chesspiece which i want to move
        if(whoWasClicked>=6 && this->clickedChessPiece==nullptr){
            this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
            this->clickedChessPiece->findValidMoves();
            emit appendLog(this->clickedChessPiece->getValidMoves());

            //If i cicked corectly, but my chosen chesspiece got no validmoves
            if(this->clickedChessPiece->getValidMoves().size()<=0){
                this->clickedChessPiece=nullptr;
                return;
            }

            //If i clicked corectly and there are valid moves
            //Inicialization of clicked chesspiese and changing the gameMode
            this->gameMode = this->gameMode+2;
            emit validMoves(this->clickedChessPiece->getValidMoves());
            return;
        }

        //if i clicked same chesspiece twice
        if(this->gameMode == 3 && this->clickedChessPiece->getPosition()->getX() == row && this->clickedChessPiece->getPosition()->getY() == col ){
            this->clickedChessPiece=nullptr;
            this->gameMode= this->gameMode-2;
            return;
        }
    }

    //If this game is in state of chosen chesspiece and recieving click on enemy chessPiece
    if( (this->gameMode == 2 && whoWasClicked >= 6) || (this->gameMode == 3 && whoWasClicked < 6)){

        //Checking if I click valid move from choices, if yes then making move
        if( !checkIfClickedValidMove(row, col) )
            return;
        else{
            makeMove(this->clickedChessPiece, row, col);
            emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
        }
    }
}
