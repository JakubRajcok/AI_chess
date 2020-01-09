#include "chessboard.h"

/*TODO
 * urob magiu a napoj sa na table
 * findValidmoves-> ked mas tabulku, tak vysviet policka moznych tahov a potom ho vrat
 * sprav spravny vypis
 * bool chooseChessPiece(BoardPosition position){}
 * void makeMove(BoardPosition from, BoardPosition to){}
*/
ChessBoard::ChessBoard(){
    this->actualChessPiece=-1;
    //DYNAMIC ALLOC FOR LATER GETTER
    int ***arr = new int**[8];
    for (int i = 0; i < 8; ++i) {
        arr[i] = new int*[8];
        for (int j = 0; j < 8; ++j)
            arr[i][j] = new int[12];
    }this->board=arr;

    //INICIIALIZACIA:
    //Pre buducu lahsiu validaciu su pri polickach bez figurky na zaciatku -1
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(i==0){
                //Rad nepesiakov BLACK
                switch (j){
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
                else if(i==6){//White Pawns
                        this->board[i][j][6]=1;
                        ChessPieceAliveWhite.push_back(new Pawn(new BoardPosition(i,j),this));
                        }
                //Rad nepesiakov WHITE
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

/*//____________________________________________________________________________________________________________________________hier liebes
void ChessBoard::draw_board(){
    for(int i=0;i<8;i++){
        if(i>0)cout<<endl;
        for(int j=0;j<8;j++){
            if(this->board[i][j][0]!=-1)
                cout<< 1 << " " << flush;
            else
                cout<< 0 << " " << flush;
        }
    }cout<<endl<<endl;
}

void ChessBoard::draw_pawns(){
    for(int i=0;i<8;i++){
        if(i>0)cout<<endl;
        for(int j=0;j<8;j++){
            if(this->board[i][j][0]!=-1){
                for(int k=0;k<12;k++){
                    //NIEJE TU ZADRHEL BLACK PAWNS SA PROSTE NACHADZAJU NA 0. POZICII
                    if(this->board[i][j][k]==1){
                        cout<< k << " "<<flush;
                        break;
                    }
                }

            }
            else
                cout<< 0 << " " << flush;
        }
    }cout<<endl<<endl;
}
*/

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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            delete[] this->board[i][j];
        delete[] this->board[i];
    }
    delete[] getBoard();
}

//tejto funkcii postnem policko v podobe BoardPositionu alebo posX a posY a ona mi povie
//ako na tom dane policko je
int ChessBoard::whosOnBox(int posX, int posY){//Ked Kliknes odpoveda ti board
    /*******************
     * ret> ID of pawn *
     * ret -1 > Empty  *
     *******************/
    const int posZ=0;
    //v poli  sa nachadzaju jednotky a nuly, TAKZE NEVIES co konkretne to je

    //If teh box is empty
    if(this->board[posX][posY][posZ] == -1){
        return -1;
    }

    //vratim index kde je figurka ulozena a tym viem, o co sa jedna
    //cize nula je black pesiak, 1 black horseman . . .
    for(int i=0;i<12;i++){
        if(this->board[posX][posY][posZ+i] > 0)
                //returne mi cislo v intervale <0,11>
                return i;
    }
}

/*
 * Sekcia v ktorej su implementove funkcie na zistovanie validnych tahov
 * TODO
 *  *pesiak vyhadzovanie do kriza
 *  *kedy je pesiak na konci (cekuj posY aby nesiel tam kam nema)
 *  *vymena figyrky za novy
 *  *nevyhadzujes VLASTNE figurky
 *  *  *Nezabudaj ze pri vyhadzovani davas do pola aj poziciu figurky na vyhodnie
 *  *Horseman ta vola
 *  *toto si si nasiel pri vezi?  'i=1, tmpY=posY;' to sa da?
 *  *asi potrebujes zadefinovat sach premenu boolean, aby si nerobil rosadu po sachu..
 *  *NAJVACIS PRUSER, NEMOZES SA POHNUT, AK ODOKRYJES KRALA A MAS AUTOMATICKY SACH, (PRED CLICK ECENT ZISTI, CI MOZES POHNUT)
 *      -mozno sa skus pytat od krala a vo funkcii volaj vsetky pohyby ostatnych figurok, kore koliduju s tym polickom
 *  *Kingovia neriesia ziadne sachy paty ani maty... dorob
 *  */

/*
std::vector<BoardPosition>* ChessBoard::findValidMoves(int posX,int posY){
    //return array which contains pairs of positions and len of array

    int chessPiece=whosOnBox(posX,posY);
    std::vector<BoardPosition> *out = new std::vector<BoardPosition>();//pozor, treba v cas aj dealokovat______________________________VELKE POZOR!
    BoardPosition position;
    switch (chessPiece){
        case(-1):
            delete[]out;//__________________________________________________________________________________________________opat delete a free
            return nullptr;
        case (0)://Pawn black

        case 6://Pawn white

        case (3)://Rook black

        case 9://Rook white

        case (1)://Horseman black

        case 7://Horseman white

        case (2)://Bishop black

        case 8://bishop White

        case (4)://Queen black

        case 10://Queen white

        case (5)://king black

        case 11://King white

        default:
            //cerr<<"findValidErr";//_____________________________________________________________________________________definuj NEDEFINOVANE
            break;
    }
}
*/
