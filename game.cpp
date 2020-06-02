#include "game.h"
#include <QDebug>
#include "chessboard.h"
#include "player.h"
#include <algorithm>


//white is going first
Game::Game(QObject *parent) : QObject(parent), board{new ChessBoard}{
    this->gameMode = 1;
    this->clickedChessPiece=nullptr;
    this->moveCounter=1;

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

void Game::clearingChessBoxes(int oldY, int newX, int*** brd, int oldX, int newY, int enPassX, int enPassY){
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

    //Setting "to" position like empty box
    for(int i=0;i<12;i++){
        if(i==0)
            brd[enPassX][enPassY][i] = -1;
        else
            brd[enPassX][enPassY][i] = 0;
    }
}

void Game::solvePawnChange(){
    /*Here is actually set the board to position like empty, if there was chesspiece
     *then it was legitible kicked and moved to kickedchesspieces it means, that now
     * we have to:
     * 1) move our pawn to our deadchesspieces
     * 2) emit signal of opening new interface with players dead chesspieces
     * 3) choosing my prefered one //eventualy keep eye, if player can see his 1st line on chessboard
     * 4) then player has to click on one of the free boxes (if there is not then just change gamemode)
     * 5) redefinig vector of the new box
     * 6) inicializing atributes of reborn chesspiece
     * 7) changing gamemode
    */
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

        //aliveChessPieces = this->board->getChessPieceAliveWhite();/**/

        deadChessPieces = this->board->getChessPieceDeadWhite();
        this->gameMode = 1;
    //If the white player is taking the black chesspiece
    }else if(toBeKicked->getType() < 6){
        begin = this->board->getChessPieceAliveBlack().begin();
        end = this->board->getChessPieceAliveBlack().end();

        //aliveChessPieces = this->board->getChessPieceAliveBlack();/**/

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

void Game::makeToPosValid(int row, int col, int*** brd, int typeOfChessPiece)
{
    for(int i=0;i<12;i++){
        if(i == typeOfChessPiece)
            brd[row][col][i] = 1;
        else
            brd[row][col][i]=0;
    }
}

void Game::makeCastling(int row,int col){
    int typeOfChessPiece = this->clickedChessPiece->getType();
    int*** brd = board->getBoard();
    ChessPiece* king = this->clickedChessPiece;
    ChessPiece* rook;

    if(typeOfChessPiece == 5){
        //clearing box of king and rook, because everything other is empty
        if(row == 0 && col == 2){
            //Settig our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(0,0),0);
            //Clearing of kings and rooks position
            clearingChessBoxes(0,0,brd,0,4);
            //Making "to" position valid Black Rook
            makeToPosValid(0, 3, brd, 3);

            rook->getPosition()->setX(0);
            rook->getPosition()->setY(3);
        }else if(row == 0 && col == 6){
            //Settig our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(0,7),0);
            //Clearing of kings and rooks position
            clearingChessBoxes(0,7,brd,0,4);
            //Making "to" position valid Black Rook
            makeToPosValid(0, 5, brd, 3);

            rook->getPosition()->setX(0);
            rook->getPosition()->setY(5);
        }

        //Making "to" position valid King
        makeToPosValid(row, col, brd, typeOfChessPiece);
        //Updating pos of the king
        king->getPosition()->setX(row);
        king->getPosition()->setY(col);

    }else if(typeOfChessPiece == 11){
        //clearing box of king and rook, because everything other is empty
        if(row == 7 && col == 2){
            //Settig our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(7,0),1);
            //Clearing of kings and rooks position
            clearingChessBoxes(7,0,brd,7,4);
            //Making "to" position valid White Rook
            makeToPosValid(7, 3, brd, 9);

            rook->getPosition()->setX(7);
            rook->getPosition()->setY(3);
        }else if(row == 7 && col == 6){
            //Settig our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(7,7),1);
            //Clearing of kings and rooks position
            clearingChessBoxes(7,7,brd,7,4);
            //Making "to" position valid White Rook
            makeToPosValid(7, 5, brd, 9);

            rook->getPosition()->setX(7);
            rook->getPosition()->setY(5);
        }

        //Making "to" position valid King
        makeToPosValid(row, col, brd, typeOfChessPiece);
        //Updating pos of the king
        king->getPosition()->setX(row);
        king->getPosition()->setY(col);
    }

    //Incrementing full move counter
    //Incerementing half move counter, it resetes after move of Pawn or any kind of capture
    this->moveCounter ++;
    if(typeOfChessPiece == 0 || typeOfChessPiece == 6 || this->board->whosOnBox(row, col) != -1)
        halfMoveCounter = 0;
    else
        halfMoveCounter ++;

    if(this->gameMode == 2)
        this->gameMode = 1;
    else if(this->gameMode == 3)
        this->gameMode = 0;

    this->clickedChessPiece = nullptr;

    generateFEN();

}

void Game::makeEnPassant(ChessPiece* toBeMoved,int row,int col){
    int typeOfChessPiece = toBeMoved->getType();
    int oldX= toBeMoved->getPosition()->getX();
    int oldY= toBeMoved->getPosition()->getY();
    int newX=row;
    int newY=col;
    ChessPiece* toBeKicked;

    int enPassantX = oldX;
    int enPassantY = newY;
    if(typeOfChessPiece == 0){
        toBeKicked = this->board->chesspieceOnBox(BoardPosition(enPassantX,enPassantY),this->gameMode);
    }else if(typeOfChessPiece == 6){
        toBeKicked = this->board->chesspieceOnBox(BoardPosition(enPassantX,enPassantY),this->gameMode);
    }

    int*** brd = board->getBoard();
    int whosOnBox = this->board->whosOnBox(row,col);

    //Setting "to", "from" & "enPassant" position like empty box
    clearingChessBoxes(oldY, newX, brd, oldX, newY, enPassantX, enPassantY);

    //Making "to" position valid
    for(int i=0;i<12;i++){
        if(i == typeOfChessPiece)
            brd[newX][newY][i] = 1;
        else
            brd[newX][newY][i]=0;
    }

    //kicking enPassant-ed pawn
    kickChessPieceOut(toBeKicked);

    //Redefining old position atribute in chessPiece
    toBeMoved->getPosition()->setX(newX);
    toBeMoved->getPosition()->setY(newY);

    //Incrementing full move counter
    //Incerementing half move counter, it resetes after move of Pawn or any kind of capture
    this->moveCounter ++;
    if(typeOfChessPiece == 0 || typeOfChessPiece == 6 || whosOnBox != -1)
        halfMoveCounter = 0;
    else
        halfMoveCounter ++;

    generateFEN();

    this->clickedChessPiece = nullptr;
    return;

}

void Game::updateBlackCastling(int oldY, int typeOfChessPiece, int oldX)
{
    if(typeOfChessPiece == 5){
        this->blackKingSideCastling = false;
        this->blackQueenSideCastling = false;
    }else if(oldX == 0 && oldY == 0)
        this->blackQueenSideCastling = false;
    else if(oldX == 0 && oldY == 7)
        this->blackKingSideCastling = false;
}

void Game::updateWhiteCastling(int typeOfChessPiece, int oldX, int oldY)
{
    if(typeOfChessPiece == 11){
        this->whiteKingSideCastling = false;
        this->whiteQueenSideCastling = false;
    }else if(oldX == 7 && oldY == 0)
        this->whiteQueenSideCastling = false;
    else if(oldX == 7 && oldY == 7)
        this->whiteKingSideCastling = false;
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
    bool pawnChange = false;


    //Setting "to" & "from" position like empty box
    clearingChessBoxes(oldY, newX, brd, oldX, newY);

    //One of the player is going to kick out enemy chesspiece
    //  if the clicked ("to") box wasn't empty
    if(whosOnBox != -1 ){
        kickChessPieceOut(toBeKicked);
    }

    //making "to" position valid
    //If black pawn reached end of the chessboard
    if( typeOfChessPiece == 0 && oldX == 6){
        pawnChange = true;
    }else if(typeOfChessPiece == 6 && oldX == 1){
    //If white pawn reached end of the chessboard
        pawnChange = true;
    }else{
        //if its normal move
        for(int i=0;i<12;i++){
            if(i == typeOfChessPiece)
                brd[newX][newY][i] = 1;
            else
                brd[newX][newY][i]=0;
        }
    }

    //Redefining old position atribute in chessPiece
    toBeMoved->getPosition()->setX(newX);
    toBeMoved->getPosition()->setY(newY);

    //Incrementing full move counter
    //Incerementing half move counter, it resetes after move of Pawn or any kind of capture
    this->moveCounter ++;
    if(typeOfChessPiece == 0 || typeOfChessPiece == 6 || whosOnBox != -1)
        halfMoveCounter = 0;
    else
        halfMoveCounter ++;

    //where was last move made, 65 -> row 6 col 5
    this->movedChessPiece = row*10 + col;

    if( (typeOfChessPiece == 6 && oldX == 6) || (typeOfChessPiece == 0 && oldX == 1) )
        startPosPawn = true;
    else
        startPosPawn = false;

    if(pawnChange)
        solvePawnChange();

    //Check if was moved rook, or king to cancel castling options
    updateBlackCastling(oldY, typeOfChessPiece, oldX);
    updateWhiteCastling(typeOfChessPiece, oldX, oldY);

    generateFEN();

    return;
}

void Game::computerVsComputer(){
    bool gameover=false;

    while(1){
        //White wins
        for(unsigned int i=0; i < board->getChessPieceDeadBlack().size();i++ ){
            if(board->getChessPieceDeadBlack().at(i)->getType()==5)
                gameover=true;
        }
        //Black wins
        for(unsigned int i=0; i < board->getChessPieceDeadWhite().size();i++ ){
            if(board->getChessPieceDeadWhite().at(i)->getType()==11)
                gameover=true;
        }

        /*
        engineGetMove(this.fen);
        fenNotationToBoardPostion();
        solveClick(fenNotationToBoardPostion().posx,fenNotationToBoardPostion().posy);
        */

        if(gameover)
            break;
    }

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

int Game::convertChessAnotationPos1(QChar n){

    if(n == 'a')
        return 0;
    if(n == 'b')
        return 1;
    if(n == 'c')
        return 2;
    if(n == 'd')
        return 3;
    if(n == 'e')
        return 4;
    if(n == 'f')
        return 5;
    if(n == 'g')
        return 6;
    if(n == 'h')
        return 7;
    return 0;
}

void Game::solveEnPassant(int whoWasClicked, int col, int row){
    QString FEN;
    if(whoWasClicked == 0 && row == 4){
        this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
        //if is enpassant in fen
        if(!this->fen.right(7).contains('-')){
            if(this->moveCounter<10 && this->fen.length()>6)
                FEN = this->fen.right(6);
            else if (this->moveCounter>10 && this->halfMoveCounter<10 && this->fen.length()>7)
                FEN = this->fen.right(7);
            else if(this->fen.length()>8)
                FEN = this->fen.right(8);

            this->clickedChessPiece->findValidMoves();
            QChar A = FEN[1] ;
            BoardPosition outA =  BoardPosition( A.digitValue()-1, convertChessAnotationPos1(FEN[0]));
            this->clickedChessPiece->getValidMoves().append( outA );
            //emit validMoves(this->clickedChessPiece->getValidMoves());
        }

    }else if (whoWasClicked == 6 && row == 3){
        this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
        //if is enpassant in fen
        if(!this->fen.right(7).contains('-')){
            if(this->moveCounter<10 && this->fen.length()>7)
                FEN = this->fen.right(6);
            else if (this->moveCounter>10 && this->halfMoveCounter<10 && this->fen.length()>8)
                FEN = this->fen.right(7);
            else if(this->fen.length()>9)
                FEN = this->fen.right(8);
            this->clickedChessPiece->findValidMoves();
            QChar B = FEN[1] ;
            BoardPosition outB =  BoardPosition( B.digitValue()-1,convertChessAnotationPos1(FEN[0]));
            this->clickedChessPiece->getValidMoves().append( outB );
            //emit validMoves(this->clickedChessPiece->getValidMoves());
        }

    }
}

void Game::solveCastling(int col, int row){
    //Inic of fen string with the part of castlings
    //check if the FEN exist, mind that 20 is totaly random ;)
    if(clickedChessPiece->getType() == 11 && row == 4 && col == 7 && this->fen.length() > 20){
       QString FEN = this->fen.right(13);

       //getting the part of string, where is castling info stored
       /*on the end is everytime info of the actual turn, thats our position
                //but there is exception of b3 and b6 enpassant situation      */
       if( FEN.lastIndexOf('b') != -1 && !FEN.contains("b3") && !FEN.contains("b6"))
           FEN = FEN.mid(FEN.lastIndexOf('b'));
       else
           FEN = FEN.mid(FEN.lastIndexOf('w'));


       //if there is white queen side castling possible, add it to valid moves
       if(FEN.contains('Q') && this->board->whosOnBox(7,0)== 9 && this->board->whosOnBox(7,1)==-1 && this->board->whosOnBox(7,2)==-1 && this->board->whosOnBox(7,3)==-1){
           this->clickedChessPiece->getValidMoves().append(BoardPosition(7,2));
       }

       //if there is white king side castling possible, add it to valid moves
       if(FEN.contains('K') && this->board->whosOnBox(7,7)== 9 && this->board->whosOnBox(7,6)==-1 && this->board->whosOnBox(7,5)==-1){
           this->clickedChessPiece->getValidMoves().append(BoardPosition(7,6));
       }

    }else if(clickedChessPiece->getType() == 5 && row == 4 && col == 0 && this->fen.length() > 20){
        QString FEN = this->fen.right(13);
        //getting the part of string, where is castling info stored
        /*on the end is everytime info of the actual turn, thats our position
                 //but there is exception of b3 and b6 enpassant situation      */
        if( FEN.lastIndexOf('b') != -1 && !FEN.contains("b3") && !FEN.contains("b6"))
            FEN = FEN.mid(FEN.lastIndexOf('b'));
        else
            FEN = FEN.mid(FEN.lastIndexOf('w'));

            //if there is black queen side csatling possible, add it to valid moves
        if(FEN.contains('q') && this->board->whosOnBox(0,0)== 3 && this->board->whosOnBox(0,1)==-1 && this->board->whosOnBox(0,2)==-1 && this->board->whosOnBox(0,3)==-1){
            this->clickedChessPiece->getValidMoves().append(BoardPosition(0,2));
        }
        //if there is black king side castling possible, add it to valid moves
        if(FEN.contains('k') && this->board->whosOnBox(0,7)== 3 && this->board->whosOnBox(0,6)==-1 && this->board->whosOnBox(0,5)==-1){
            this->clickedChessPiece->getValidMoves().append(BoardPosition(0,6));
        }

    }
}

void Game::solveClick(int row, int col){

    int whoWasClicked = this->board->whosOnBox(row,col);
    /*
    int arr[64]{};
    int k=0;
    for( int i=0;i<8;i++){
        for (int j = 0; j<8;j++){
            arr[k]= this->board->whosOnBox(i,j);
            k++;
        }
    }
    */

    //If the place where i clicked whas empty box
    if (whoWasClicked == -1){
        //If my chesspiece was chosen and i want to move on empty box
        if(gameMode == 2 || gameMode ==3){

            //If peasent was clicked and now Iam clicking empty box
            if( (clickedChessPiece->getType() == 0 ) || (clickedChessPiece->getType() == 6)){
                bool enPassant = false;

                //if got peasant min one move, if its not ours, then check for another possible
                if(clickedChessPiece->getValidMoves().size() > 0){
                    int oldY = clickedChessPiece->getPosition()->getY();
                    int newY = clickedChessPiece->getValidMoves().at(0).getY();
                    if( oldY != newY && this->board->whosOnBox(clickedChessPiece->getValidMoves().at(0).getX(),newY) == -1 )
                        enPassant = true;
                    else if(clickedChessPiece->getValidMoves().size() > 1){
                        oldY = clickedChessPiece->getPosition()->getY();
                        newY = clickedChessPiece->getValidMoves().at(1).getY();
                        if( oldY != newY && this->board->whosOnBox(clickedChessPiece->getValidMoves().at(1).getX(),newY) == -1)
                            enPassant = true;
                    }
                }
                //Checking if I click valid move from choices, if yes then making move
                if(enPassant){
                    makeEnPassant(this->clickedChessPiece, row, col);
                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
                    return;
                }
            }

            //The king was clicked and now is player looking for empty boxes/castling
            if( (clickedChessPiece->getType() == 5 ) || (clickedChessPiece->getType() == 11)){
                if( (row ==0 && col ==2 ) || (row ==0 && col ==6) || (row ==7 && col ==2) || (row ==7 && col ==6) ){
                    int gmode = this->gameMode;
                    makeCastling(row, col);
                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
                    return;
                }
            }
            //The king was clicked and now is player looking for empty boxes/castling

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
            if(clickedChessPiece->getType() == 0)
                solveEnPassant(whoWasClicked, col, row);
            solveCastling(row, col);

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
            if(clickedChessPiece->getType() == 6)
                solveEnPassant(whoWasClicked, col, row);
            //if we clicked white king and if he is on the right starting position
            solveCastling(row, col);

            //If i cicked corectly, but my chosen chesspiece got no validmoves
            if(this->clickedChessPiece->getValidMoves().size()<=0){
                this->clickedChessPiece=nullptr;
                return;
            }

            //If i clicked corectly and there are valid moves
            //Inicialization of clicked chesspiese and changing the gameMode
            this->gameMode = this->gameMode+2;
            emit validMoves(this->clickedChessPiece->getValidMoves());/*CRAAAAAAAAAAASHSHSAHAHAHA po vela tahoch je problem s pesiakom*/
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

BoardPosition Game::fenNotationToBoardPostion(QString fenNot){
    QChar letter = fenNot[0];
    int row = fenNot[1].digitValue();
    return BoardPosition( row ,convertChessAnotationPos1(letter) );
}

//Generating one letter from official FEN notation, in case of empty box, it returns 1
QChar Game::intToLetter(int chessId){
    switch(chessId){
        case -1:
            return '1';
        case 0:
            return 'p';
        case 1:
            return 'n';
        case 2:
            return 'b';
        case 3:
            return 'r';
        case 4:
            return 'q';
        case 5:
            return 'k';
        case 6:
            return 'P';
        case 7:
            return 'N';
        case 8:
            return 'B';
        case 9:
            return 'R';
        case 10:
            return 'Q';
        case 11:
            return 'K';
        default:
            return ' ';
    }

    return ' ';
}

//this function creates entire FEN notation
QString Game::createLetterFromRow(int pos){

    switch(pos){
        case 30:
            return(" a3");
        case 31:
            return(" b3");
        case 32:
            return(" c3");
        case 33:
            return( "d3");
        case 34:
            return(" e3");
        case 35:
            return(" f3");
        case 36:
            return(" g3");
        case 37:
            return(" h3");
        case 40:
            return(" a6");
        case 41:
            return(" b6");
        case 42:
            return(" c6");
        case 43:
            return(" d6");
        case 44:
            return(" e6");
        case 45:
            return(" f6");
        case 46:
            return(" g6");
        case 47:
            return(" h6");
        }
        return " ";
}

QString Game::generateFEN(){
    QString FEN = "";
    int emptyBoxes = 0;

    //we are iterating our entire board 8x8
    for (int i=0; i<8; i++){
        for (int j=0;j<8;j++){

            //here Im returning the character of boardPosition
            QChar sign= intToLetter( this->board->whosOnBox(i,j) );

            //do I have chesspiece or empty box?
            if( emptyBoxes != 0 ){
                //am I on the end of embeded for?
                if(j == 7){
                    //then write string, because the for is ending
                    FEN.append( QString::number(++emptyBoxes) );
                    emptyBoxes = 0;
                    continue;
                }else if( sign.digitValue() == -1 ){
                    //is there another chessPiece after empty boxes? write it down
                    FEN.append( QString::number(emptyBoxes) );
                    emptyBoxes = 0;
                    FEN.append(sign);
                    continue;
                }
                emptyBoxes++;
            //if there is any chessPiece, write it down!
            }else if (sign.digitValue() == -1){
                FEN.append(sign);
            //if there is another empty box, incerement emptyBoxes
            }else{
                emptyBoxes++;
            }
        }

        //If there is end of 1st 8 strings, write down "/" else it is " "
        if( i< 7)
            FEN.append('/');
        emptyBoxes = 0;
    }

    //whos turn it is?
    if(this->gameMode == 2 || this->gameMode == 0)
        FEN.append(" w ");
    else
        FEN.append(" b ");

    //Queen castling and king castling for both players
    if(this->whiteKingSideCastling)
        FEN.append("K");
    if(this->whiteQueenSideCastling)
        FEN.append("Q");
    if(this->blackKingSideCastling)
        FEN.append("k");
    if(this->blackQueenSideCastling)
        FEN.append("q");
    if(!this->whiteKingSideCastling && !this->whiteQueenSideCastling && !this->blackQueenSideCastling && !this->blackQueenSideCastling)
        FEN.append("-");

    //Finding out, if there is valid en'passant situation eg. if was pawn moved 2 boxes ahead
    int row = (int)this->movedChessPiece/10;
    int col = (int)this->movedChessPiece - row*10;
    if( row == 3 && this->board->whosOnBox(row,col) == 0 ){
        FEN.append( createLetterFromRow(this->movedChessPiece) );
    }else if(row == 4 && this->board->whosOnBox(row,col) == 6){
        FEN.append( createLetterFromRow(this->movedChessPiece) );
    }else
        FEN.append(" -");
    FEN.append(" ");

    //Half move number
    FEN.append( QString::number ((int)halfMoveCounter));
    FEN.append(" ");

    //Full move number
    FEN.append( QString::number ((int)moveCounter/2) );

    this->fen = FEN;
    return FEN;
}
