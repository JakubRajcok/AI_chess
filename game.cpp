#include "game.h"
#include <QDebug>
#include "chessboard.h"
#include "player.h"
#include <algorithm>
#include <QProcess>
#include <QTime> // for Sleep
#include <QCoreApplication>

//white is going first
Game::Game(QObject *parent) : QObject(parent), board{new ChessBoard}{
    this->gameMode = 1;
    this->clickedChessPiece=nullptr;
    this->moveCounter=1;
    this->fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    emit appendFen(this->fen);

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
    if(this->gameMode == 0 || this->gameMode == 2){
        this->gameMode = 2;
        this->pawnChange = true;
    }else if (this->gameMode == 1 || this->gameMode == 3){
        this->gameMode=3;
        this->pawnChange = true;
    }
}

void Game::kickChessPieceOut(ChessPiece* toBeKicked){
    std::vector<ChessPiece*>::iterator begin;
    std::vector<ChessPiece*>::iterator end;

    //If the black player is taking the white chesspiece
    if(toBeKicked->getType() >= 6){
        begin = this->board->getChessPieceAliveWhite().begin();
        end = this->board->getChessPieceAliveWhite().end();

        this->gameMode = 1;
        this->board->getChessPieceDeadWhite().push_back(toBeKicked);

        //If the white player is taking the black chesspiece
    }else if(toBeKicked->getType() < 6){
        begin = this->board->getChessPieceAliveBlack().begin();
        end = this->board->getChessPieceAliveBlack().end();

        this->gameMode = 0;
        this->board->getChessPieceDeadBlack().push_back(toBeKicked);
    }

    for(; begin != end ; begin++){
        if(*begin == toBeKicked  ){
            if(toBeKicked->getType() >= 6)
                this->board->getChessPieceAliveWhite().erase(begin);
            else
                this->board->getChessPieceAliveBlack().erase(begin);
            this->clickedChessPiece=nullptr;
            break;
        }
    }


    toBeKicked->setIsPlaced(false);
    toBeKicked->getPosition()->setX(-1);
    toBeKicked->getPosition()->setY(-1);
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
            brd[0][3][0] = 0;
            brd[0][3][3] = 1;

            rook->getPosition()->setX(0);
            rook->getPosition()->setY(3);
        }else if(row == 0 && col == 6){
            //Settig our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(0,7),0);
            //Clearing of kings and rooks position
            clearingChessBoxes(7,0,brd,0,4);
            //Making "to" position valid Black Rook
            brd[0][5][0] = 0;
            brd[0][5][3] = 1;

            rook->getPosition()->setX(0);
            rook->getPosition()->setY(5);
        }

        //Making "to" position valid King
        brd[row][col][0] = 0;
        brd[row][col][5] = 1;
        //Updating pos of the king
        king->getPosition()->setX(row);
        king->getPosition()->setY(col);
        this->blackKingSideCastling = false;
        this->blackQueenSideCastling = false;
    }else if(typeOfChessPiece == 11){
        //clearing box of king and rook, because everything other is empty
        if(row == 7 && col == 2){
            //Setting our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(7,0),1);
            //Clearing of kings and rooks position
            clearingChessBoxes(0,7,brd,7,4);
            //Making "to" position valid White Rook
            brd[7][3][0] = 0;
            brd[7][3][9] = 1;

            rook->getPosition()->setX(7);
            rook->getPosition()->setY(3);
        }else if(row == 7 && col == 6){
            //Settig our rook which will be moved
            //I have to change gamemode becouse its special situation
            rook = this->board->chesspieceOnBox(BoardPosition(7,7),1);
            //Clearing of kings and rooks position
            clearingChessBoxes(7,7,brd,7,4);
            //Making "to" position valid White Rook //(int oldY, int newX, int*** brd, int oldX, int newY){
            brd[7][5][0] = 0;
            brd[7][5][9] = 1;

            rook->getPosition()->setX(7);
            rook->getPosition()->setY(5);
        }

        //Making "to" position valid King
        brd[row][col][0] = 0;
        brd[row][col][11] = 1;
        //Updating pos of the king
        king->getPosition()->setX(row);
        king->getPosition()->setY(col);
        this->whiteKingSideCastling = false;
        this->whiteQueenSideCastling = false;
    }

    //Incrementing full move counter
    //Incerementing half move counter, becouse its not pawn advence or capture
    halfMoveCounter ++;
    if(typeOfChessPiece == 5)
        moveCounter++;

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
    if(typeOfChessPiece == 0 || typeOfChessPiece == 6 || whosOnBox != -1)
        halfMoveCounter = 0;
    else
        halfMoveCounter ++;

    if(typeOfChessPiece == 0)
        moveCounter++;

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
    if(typeOfChessPiece<6)
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

    //Check if was moved rook, or king to cancel castling options
    updateBlackCastling(oldY, typeOfChessPiece, oldX);
    updateWhiteCastling(typeOfChessPiece, oldX, oldY);

    generateFEN();

    if(pawnChange){
        kickChessPieceOut(toBeMoved);
        if(toBeMoved->getType() == 6)
            this->gameMode = 1;
        else
            this->gameMode = 0;
        solvePawnChange();
    }

    return;
}

QString Game::giveMePos(QString in){
    if(in == "a1")
        return "70";
    if(in == "b1")
        return "71";
    if(in == "c1")
        return "72";
    if(in == "d1")
        return "73";
    if(in == "e1")
        return "74";
    if(in == "f1")
        return "75";
    if(in == "g1")
        return "76";
    if(in == "h1")
        return "77";

    if(in == "a2")
        return "60";
    if(in == "b2")
        return "61";
    if(in == "c2")
        return "62";
    if(in == "d2")
        return "63";
    if(in == "e2")
        return "64";
    if(in == "f2")
        return "65";
    if(in == "g2")
        return "66";
    if(in == "h2")
        return "67";

    if(in == "a3")
        return "50";
    if(in == "b3")
        return "51";
    if(in == "c3")
        return "52";
    if(in == "d3")
        return "53";
    if(in == "e3")
        return "54";
    if(in == "f3")
        return "55";
    if(in == "g3")
        return "56";
    if(in == "h3")
        return "57";

    if(in == "a4")
        return "40";
    if(in == "b4")
        return "41";
    if(in == "c4")
        return "42";
    if(in == "d4")
        return "43";
    if(in == "e4")
        return "44";
    if(in == "f4")
        return "45";
    if(in == "g4")
        return "46";
    if(in == "h4")
        return "47";

    if(in == "a5")
        return "30";
    if(in == "b5")
        return "31";
    if(in == "c5")
        return "32";
    if(in == "d5")
        return "33";
    if(in == "e5")
        return "34";
    if(in == "f5")
        return "35";
    if(in == "g5")
        return "36";
    if(in == "h5")
        return "37";

    if(in == "a6")
        return "20";
    if(in == "b6")
        return "21";
    if(in == "c6")
        return "22";
    if(in == "d6")
        return "23";
    if(in == "e6")
        return "24";
    if(in == "f6")
        return "25";
    if(in == "g6")
        return "26";
    if(in == "h6")
        return "27";

    if(in == "a7")
        return "10";
    if(in == "b7")
        return "11";
    if(in == "c7")
        return "12";
    if(in == "d7")
        return "13";
    if(in == "e7")
        return "14";
    if(in == "f7")
        return "15";
    if(in == "g7")
        return "16";
    if(in == "h7")
        return "17";

    if(in == "a8")
        return "00";
    if(in == "b8")
        return "01";
    if(in == "c8")
        return "02";
    if(in == "d8")
        return "03";
    if(in == "e8")
        return "04";
    if(in == "f8")
        return "05";
    if(in == "g8")
        return "06";
    if(in == "h8")
        return "07";

    return " ";
}

void Game::computerVsComputer(){
    bool gameover=false;
    QString pcColor = "w";
    QString lastMove = "d2d4";
    QString fenBefore = this->fen;

    //d2 d4
    /////////pomimo d7 d5
    //63 43

    solveClick(giveMePos(lastMove).at(0).digitValue() ,giveMePos(lastMove).at(1).digitValue() );
    solveClick(giveMePos(lastMove).at(2).digitValue() ,giveMePos(lastMove).at(3).digitValue() );



    while(1){

        if(pcColor == "w")
            pcColor = "b";
        else
            pcColor = "w";

        QString fenFromBestMove = getBestMove(lastMove, pcColor, fenBefore).left(4).remove(0, 2);
        lastMove = getBestMove(lastMove, pcColor, fenBefore).left(4);   // move made based on actual chessboard
        QString fenBefore = this->fen;                                  // actual chessboard before fen


        qDebug() << " ";
        qDebug() << "Situation before executing latest move";
        qDebug() << "FEN before the move: "<< fenBefore;
        qDebug() << "Last made move: "<<lastMove;
        qDebug() << "Color of PC: " << pcColor;

        solveClick(giveMePos(lastMove).at(0).digitValue() ,giveMePos(lastMove).at(1).digitValue() );
        solveClick(giveMePos(lastMove).at(2).digitValue() ,giveMePos(lastMove).at(3).digitValue() );

        qDebug() << "----------------------------------------";
        qDebug() << "FEN from the best move: " << fenFromBestMove;
        qDebug() << "The FEN game generated: " << this->fen;

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

        QTime dieTime = QTime::currentTime().addMSecs( 500 );
        while( QTime::currentTime() < dieTime ){
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }

        if(gameover)
            break;
    }

}

/*
farba sa nastavi na bielu
do *lastmove* si zapamatame tah
zapamatame si fen

vykoname tah z      solveClick(giveMePos(lastMove).at(0) ,giveMePos(lastMove).at(1) );
vykoname tah na     solveClick(giveMePos(lastMove).at(2) ,giveMePos(lastMove).at(3) );

farba sa otoci
do *lastmove* posleme *lastMove* *pcColor* *fenBefore*
do *fenBefore* nastavime aktualnu fen

vykoname tah z      solveClick(giveMePos(lastMove).at(0) ,giveMePos(lastMove).at(1) );
vykoname tah na     solveClick(giveMePos(lastMove).at(2) ,giveMePos(lastMove).at(3) );

skontrolujeme sach
*/

QString Game::getChesspieceToChange() const
{
    return chesspieceToChange;
}

void Game::setChesspieceToChange(const QString &value)
{
    chesspieceToChange = value;
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
            if( !this->fen.at(this->fen.length()-2).isDigit() )
                FEN = this->fen.right(6);
            else if ( !this->fen.at(this->fen.length()-5).isDigit() )
                FEN = this->fen.right(7);
            else
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
            if( !this->fen.at(this->fen.length()-2).isDigit() )
                FEN = this->fen.right(6);
            else if ( !this->fen.at(this->fen.length()-5).isDigit() )
                FEN = this->fen.right(7);
            else
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

QString Game::getBestMove(QString fromToPos, QString pcColor, QString fenBeforeMove){

    //inserted putty code
    //Here I am working with tranined NN based on Python
    QProcess p;
    p.setWorkingDirectory("/home/jrajcok/chess_tensorflow/Predicting-Pro-Chess-Moves");
    //p.start("python", QStringList()<< "go.py" << "b" << "d2d4" << "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    p.start("python", QStringList()<< "go.py" << pcColor << fromToPos << fenBeforeMove);

    QByteArray ba = p.readAllStandardOutput();
    QList<QByteArray> nn_output = ba.split('\n');

    //Appending actual fen string and outputing result best move of our NN
    emit appendLog(nn_output.at(1));
    emit appendFen(nn_output.at(0));
    //exit(0);


    return QString::fromStdString(nn_output.at(1).toStdString()).append(nn_output.at(0));
}

void Game::solveClick(int row, int col){
    qDebug()<<"Clicked (row,col) in gamemode: ("<<row<<","<<col<<") in gm: "<<this->gameMode;
    //computerVsComputer();///////////////////////////////////////////////

    int arr[64]{};
    int k=0;
    for( int i=0;i<8;i++){
        for (int j = 0; j<8;j++){
            arr[k]= this->board->whosOnBox(i,j);
            k++;
        }
    }


    if(this->pawnChange){
        /*Here is actually set the board to position like empty, if there was chesspiece
         *then it was legitible kicked and moved to kickedchesspieces, it is same with
         *our moved Pawn. It means, that now
         * we have to:
         * 1) move our pawn to our deadchesspieces ,DONE
         * 2) emit signal of opening new interface with players dead chesspieces
         * 3) choosing my prefered one //eventualy keep eye, if player can see his 1st line on chessboard
         * 4) then player has to click on one of the free boxes (if there is not then just change gamemode)
         * 5) redefinig vector of the new box
         * 6) inicializing atributes of reborn chesspiece
         * 7) changing gamemode
        */

        //Here we are w8ing 4 the click on kicked chesspiece to its revieve
        if(!this->chesspieceToChange.isEmpty() && this->chesspieceToChange.at( this->chesspieceToChange.indexOf(".")-1 ).digitValue() == 0){
            for(std::vector<ChessPiece*>::iterator it = this->board->getChessPieceDeadBlack().begin();it!=this->board->getChessPieceDeadBlack().end();it++){
                if((*it)->getIconName() == chesspieceToChange){
                    this->board->getChessPieceAliveBlack().push_back((*it));
                    this->board->getChessPieceDeadBlack().erase(it);

                    for(int i =0; i<8;i++){
                        if(this->board->whosOnBox(0,i)==-1)
                            this->board->getChessPieceAliveBlack().back()->getValidMoves().push_back(BoardPosition(0,i));
                    }
                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
                    emit updateKickedPiecesSignal(this->board->getChessPieceDeadBlack(), this->board->getChessPieceDeadWhite());

                    this->pawnChange = false;
                    this->chesspieceToChange = "";
                    break;
                }
            }
        }else if(!this->chesspieceToChange.isEmpty() && this->chesspieceToChange.at( this->chesspieceToChange.indexOf(".")-1 ).digitValue() == 1){
            for(std::vector<ChessPiece*>::iterator it = this->board->getChessPieceDeadWhite().begin();it!=this->board->getChessPieceDeadWhite().end();it++){
                if((*it)->getIconName() == chesspieceToChange){
                    this->board->getChessPieceAliveWhite().push_back((*it));
                    this->board->getChessPieceDeadWhite().erase(it);

                    for(int i =0; i<8;i++){
                        if(this->board->whosOnBox(7,i)==-1)
                            this->board->getChessPieceAliveWhite().back()->getValidMoves().push_back(BoardPosition(7,i));
                    }
                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
                    emit updateKickedPiecesSignal(this->board->getChessPieceDeadBlack(), this->board->getChessPieceDeadWhite());

                    this->pawnChange = false;
                    this->chesspieceToChange = "";
                    break;
                }
            }
        }
        //este ju musis polozit
        //aktualizovat jej suradnice a premenne
        //a dalej len zmenit gamemode
        return;
    }

    int whoWasClicked = this->board->whosOnBox(row,col);

    //If the place where i clicked whas empty box
    if (whoWasClicked == -1){
        //If my chesspiece was chosen and i want to move on empty box
        if(gameMode == 2 || gameMode ==3){

            //If peasent was clicked and now Iam clicking empty box
            if( (clickedChessPiece->getType() == 0 ) || (clickedChessPiece->getType() == 6)){
                bool enPassant = false;

                //if got min one move, if its not ours, then check for another possible
                if(clickedChessPiece->getValidMoves().size() > 0){
                    int oldY = clickedChessPiece->getPosition()->getY();
                    int newY = clickedChessPiece->getValidMoves().at(0).getY();

                    if( oldY != newY && this->board->whosOnBox(clickedChessPiece->getValidMoves().at(0).getX(),newY) == -1 )
                        enPassant = true;
                    else if(clickedChessPiece->getValidMoves().size() == 2){
                        oldY = clickedChessPiece->getPosition()->getY();
                        newY = clickedChessPiece->getValidMoves().at(1).getY();
                        if( oldY != newY && this->board->whosOnBox(clickedChessPiece->getValidMoves().at(1).getX(),newY) == -1)
                            enPassant = true;
                    }else if(clickedChessPiece->getValidMoves().size() > 2){
                        oldY = clickedChessPiece->getPosition()->getY();
                        newY = clickedChessPiece->getValidMoves().at(2).getY();
                        if( oldY != newY && this->board->whosOnBox(clickedChessPiece->getValidMoves().at(2).getX(),newY) == -1)
                            enPassant = true;
                    }
                }

                //Checking if I click valid move from choices, if yes then making move
                if(enPassant && ( (row == 5 && this->board->whosOnBox(row-1,col) == 6) || (row == 2 && this->board->whosOnBox(row+1,col) == 0) ) ){
                    makeEnPassant(this->clickedChessPiece, row, col);
                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
                    emit updateKickedPiecesSignal(this->board->getChessPieceDeadBlack(), this->board->getChessPieceDeadWhite());
                    return;
                }
            }

            //The king was clicked and now is player looking for empty boxes/castling
            if( (clickedChessPiece->getType() == 5 ) || (clickedChessPiece->getType() == 11)){
                if( (row ==0 && col ==2 ) || (row ==0 && col ==6) || (row ==7 && col ==2) || (row ==7 && col ==6) ){
                    makeCastling(row, col);
                    emit updateChessboardSignal(this->board->getChessPieceAliveBlack(), this->board->getChessPieceAliveWhite());
                    emit updateKickedPiecesSignal(this->board->getChessPieceDeadBlack(), this->board->getChessPieceDeadWhite());
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
                emit updateKickedPiecesSignal(this->board->getChessPieceDeadBlack(), this->board->getChessPieceDeadWhite());

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
            emit updateKickedPiecesSignal(this->board->getChessPieceDeadBlack(), this->board->getChessPieceDeadWhite());

        }
    }
}

void Game::deadPieceSelectedSlot(QString pieceName){
    this->chesspieceToChange = pieceName;
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
    FEN.append( QString::number ((int) halfMoveCounter ));
    FEN.append(" ");

    //Full move number
    FEN.append( QString::number ((int)moveCounter) );

    this->fen = FEN;
    emit appendFen(this->fen);
    return FEN;
}
