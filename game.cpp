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

    return;

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

    generateFEN();

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

    if(whoWasClicked == 0 && row == 4){
        this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
        //if is enpassant in fen
        if(!this->fen.right(6).contains('-')){
            QString FEN = this->fen.right(6);
            this->clickedChessPiece->findValidMoves();
            QChar A = FEN[1] ;
            BoardPosition outA =  BoardPosition( A.digitValue()-1, convertChessAnotationPos1(FEN[0]));
            this->clickedChessPiece->getValidMoves().append( outA );
            //emit validMoves(this->clickedChessPiece->getValidMoves());
        }
        //this->gameMode++;
        //return;
    }else if (whoWasClicked == 6 && row == 3){
        this->clickedChessPiece = this->board->chesspieceOnBox(BoardPosition(row,col),this->gameMode);
        //if is enpassant in fen
        if(!this->fen.right(6).contains('-')){
            QString FEN = this->fen.right(6);
            this->clickedChessPiece->findValidMoves();
            QChar B = FEN[1] ;
            BoardPosition outB =  BoardPosition( B.digitValue()-1,convertChessAnotationPos1(FEN[0]));
            this->clickedChessPiece->getValidMoves().append( outB );
            //emit validMoves(this->clickedChessPiece->getValidMoves());
        }
        //this->gameMode++;
        //return;
    }
}

void Game::solveClick(int row, int col){

    int whoWasClicked = this->board->whosOnBox(row,col);

    //If the place where i clicked whas empty box
    if (whoWasClicked == -1){
        //If my chesspiece was chosen and i want to move on empty box
        if(gameMode == 2 || gameMode ==3){


            if( (clickedChessPiece->getType() == 0 ) || (clickedChessPiece->getType() == 6)){
                bool enPassant = false;

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
            solveEnPassant(whoWasClicked, col, row);

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
            solveEnPassant(whoWasClicked, col, row);

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
        FEN.append(" ");

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
