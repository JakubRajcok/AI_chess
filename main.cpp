#include "mainwindow.h"

#include <QApplication>
#include <vector>

using namespace std;

typedef struct Point{
private:
    int posX;
    int posY;

public:
    Point(){
        this->posX=-1;
        this->posY=-1;
    }
    Point(int x, int y){
        this->posX=x;
        this->posY=y;
    }
    void setX(int x){
        this->posX=x;
    }
    void setY(int y){
        this->posY=y;
    }
    int getX(){
        return this->posX;
    }
    int getY(){
        return this->posY;
    }
}Point;

class King{
    int color;//0-black, 1-white
    bool check;//if checked
    Point position;//where is he?

public:
    King(){
        color=-1;
    }
    King (int color,Point position){
        this->color=color;
        this->position=position;
        this->check=false;
    }
};

class chess_board{
    private:
        int ***board;
        King kingBlack;
        King kingWhite;
    public:

    chess_board(){

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
                            this->kingBlack=King(0,Point(i,j));
                            break;
                    }
                }
                else
                    if(i==1)//BLACK Pawns
                        this->board[i][j][0]=1;
                    else if(i==6)//White Pawns
                        this->board[i][j][6]=1;
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
                                this->kingWhite=King(0,Point(i,j));
                                break;
                        }
                    }else
                        this->board[i][j][0]=-1;
            }
        }
    }

    void draw_board(){
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

    void draw_pawns(){
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


    int*** getBoard(){
        return this->board;
    }

    void deleteBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                delete[] this->board[i][j];
            delete[] this->board[i];
        }
        delete[] getBoard();
    }

    int whosOnBox(  int posX, int posY){//Ked Kliknes odpoveda ti board
        /*******************
         * ret> ID of pawn *
         * ret -1 > Empty  *
         *******************/
        int posZ=0;
        //v poli  sa nachadzaju jednotky a nuly, TAKZE NEVIES co konkretne to je
        if(this->board[posX][posY][posZ] == -1){
            return -1;
        }

        //vratim index kde je figurka ulozena a tym viem, o co sa jedna
        for(int i=0;i<12;i++){
            if(this->board[posX][posY][posZ+i] > 0)
                    //return this->board[posX][posY][posZ+i];
                    return i;
        }
    }

    vector<Point> *findValidMoves(int posX,int posY){
        //return array which contains pairs of positions and len of array

        int chessPiece=whosOnBox(posX,posY);
        vector<Point> *out = new vector<Point>();
        Point position;
        switch (chessPiece){
            case (0)://Pawn black
                validMovesBlackPawn(posX, posY, out, position);
                return out;
            case 6://Pawn white
                validMovesWhitePawn(posX, posY, out, position);
                return out;
            case (3)://Rook black
                validMovesBlackRook(posX, posY, out);
                return out;
            case 9://Rook white
                validMovesWhiteRook(posX,posY, out);
                return out;
            case (1)://Horseman black
                validMovesBlackHorseman(posX,posY, out);
                return out;
            case 7://Horseman white
                validMovesWhiteHorseman(posX,posY, out);
                return out;
            case (2)://Bishop black
                validMovesBlackBishop(posX,posY, out);
                return out;
            case 8://bishop White
                validMovesWhiteBishop(posX,posY, out);
                return out;
            case (4)://Queen black
                validMovesBlackQueen(posX,posY, out);
                return out;
            case 10://Queen white
                validMovesWhiteQueen(posX,posY, out);
                return out;
            case (5)://king black
                validMovesBlackKing(posX,posY, out);
                return out;
            case 11://King white
                validMovesWhiteKing(posX,posY, out);
                return out;
            default:
                cerr<<"findValidErr";
                break;

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

    /**
     * DONE
     * Pozor na zacinajucu otazku, pytas sa ci je prvotna pozicia rozna, to znamena ze sa mozes dostat za pole (horne ohranicenie)
     * => while(posX!=6) upravene na horne ohranicenie (posX<7)
     * ......................................................
     */

    //_________________________________________________...............................) const{________________preco?????
    void validMovesBlackPawn(int posX, int posY, vector<Point> *out, Point &position) {
        //Pokial to je prvy tah a pesiak sa moze pohnut o dve policka
        if(posY == 1){//______________________________________________________bolo tu posX, mozno len bluznis tak sa k tomu vrat
            out->resize(2);
            for(int i=0+1;i<2+1;i++){
                if( whosOnBox(posX,posY+i) == -1){
                    //V ceste je figurka
                    break;
                }
                position=Point(posX,posY+i);
                out->push_back(position);
                }
            }else{
                //opytam sa ci je policko pred volne
                if(whosOnBox(posX,posY+1)==-1){
                    out->resize(1);
                    out->push_back(Point(posX,posY+1));
                }
            }
    }

    void validMovesWhitePawn(int posX, int posY, vector<Point> *out, Point &position){
        if(posY == 1){
            out->resize(2);
            for(int i=0+1;i<2+1;i++){
                if(whosOnBox(posX,posY-i) == -1){
                    //v ceste je figurka
                    break;
                }
                position=Point(posX,posY-i);
                out->push_back(position);
            }
        }else{
            if(whosOnBox(posX,posY-1)==-1){
                out->resize(1);
                out->push_back(Point(posX,posY-1));
            }
        }
    }

    void validMovesBlackRook(int posX, int posY, vector<Point> *out) {
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        /*VSEO princip prehladavania */
        //Prezerame smer v ktorom sa moze figurka pohybovat, ak je pol volne, zapiseme ak nie, zapiseme a koncime

        while(tmpX < 7){//Prezeranie policok na pravo
            //Prezerame ten buduci, preto len do 6, kedze mame 8 policok, ideme od nuly a pozerame 1 dopredu
            if(whosOnBox(posX+i,posY)==-1){
                out->emplace_back(Point(posX+i,posY));
                i++;
                tmpX++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(whosOnBox(posX+i,posY)>=6)
                    out->emplace_back(Point(posX+i,posY));
                break;
            }
        }
        i=1;
        tmpX=posX;
        while(tmpX > 0){//Prezeranie policok na lavo
            if(whosOnBox(posX-i,posY)==-1){
                out->emplace_back(Point(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(whosOnBox(posX+i,posY)>=6)
                    out->emplace_back(Point(posX-i,posY));
                break;
            }
        }
        i=1;
        while(tmpY < 7){//Prezeranie policek pod figurkou
            if(whosOnBox(posX,posY+i)==-1){
                out->emplace_back(Point(posX,posY+i));
                i++;
                tmpY++;
            }else{
                if(whosOnBox(posX,posY+i)>=6)
                    out->emplace_back(Point(posX,posY+i));
                break;
            }
        }
        i=1; tmpY=posY;
        while(tmpY > 0){//Prezeranie policek nad figurkou
            if(whosOnBox(posX,posY-i)==-1){
                out->emplace_back(Point(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(whosOnBox(posX,posY-i)>=6)
                    out->emplace_back(Point(posX,posY-i));
                break;
            }
        }
    }

    void validMovesWhiteRook(int posX, int posY, vector<Point> *out) {
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        /*VSEO princip prehladavania */
        //Prezerame smer v ktorom sa moze figurka pohybovat, ak je pol volne, zapiseme ak nie, zapiseme a koncime

        while(tmpX < 7){//Prezeranie policok na pravo
            //Prezerame ten buduci, preto len do 6, kedze mame 8 policok, ideme od nuly a pozerame 1 dopredu
            if(whosOnBox(posX+i,posY)==-1){
                out->emplace_back(Point(posX+i,posY));
                i++;
                tmpX++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(whosOnBox(posX+i,posY)<6)
                    out->emplace_back(Point(posX+i,posY));
                break;
            }
        }
        i=1;
        tmpX=posX;
        while(tmpX > 0){//Prezeranie policok na lavo
            if(whosOnBox(posX-i,posY)==-1){
                out->emplace_back(Point(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(whosOnBox(posX+i,posY)<6)
                    out->emplace_back(Point(posX-i,posY));
                break;
            }
        }
        i=1;
        while(tmpY < 7){//Prezeranie policek pod figurkou
            if(whosOnBox(posX,posY+i)==-1){
                out->emplace_back(Point(posX,posY+i));
                i++;
                tmpY++;
            }else{
                if(whosOnBox(posX,posY+i)<6)
                    out->emplace_back(Point(posX,posY+i));
                break;
            }
        }
        i=1; tmpY=posY;
        while(tmpY > 0){//Prezeranie policek nad figurkou
            if(whosOnBox(posX,posY-i)==-1){
                out->emplace_back(Point(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(whosOnBox(posX,posY-i)<6)
                    out->emplace_back(Point(posX,posY-i));
                break;
            }
        }
    }

    void validMovesBlackHorseman(int posX, int posY, vector<Point> *out){
        if(posX-1>=0 && posY-3>=0){
            if(whosOnBox(posX-1,posY-3)==-1 || whosOnBox(posX-1,posY-3)>5)
                out->push_back(Point(posX-1,posY-3));
        }
        if(posX+1<=7 && posY-3>=0){
            if(whosOnBox(posX+1,posY-3)==-1 || whosOnBox(posX+1,posY-3)>5)
                out->push_back(Point(posX+1,posY-3));
        }
        if(posX+2<=7 && posY-1>=0){
            if(whosOnBox(posX+2,posY-1)==-1 || whosOnBox(posX+2,posY-1)>5)
                out->push_back(Point(posX+2,posY-1));
        }
        if(posX+2<=7 && posY+1<=7){
            if(whosOnBox(posX+2,posY+1)==-1 || whosOnBox(posX+2,posY+1)>5)
                out->push_back(Point(posX+2,posY+1));
        }
        if(posX+1<=7 && posY+3<=7){
            if(whosOnBox(posX+1,posY+3)==-1 || whosOnBox(posX+1,posY+3)>5)
                out->push_back(Point(posX+1,posY+3));
        }
        if(posX-1>=0 && posY+3<=7){
            if(whosOnBox(posX-1,posY+3)==-1 || whosOnBox(posX-1,posY+3)>5)
                out->push_back(Point(posX-1,posY+3));
        }
        if(posX-2>=0 && posY+1<=7){
            if(whosOnBox(posX-2,posY+1)==-1 || whosOnBox(posX-2,posY+1)>5)
                out->push_back(Point(posX-2,posY+1));
        }
        if(posX-2>=0 && posY-1>=0){
            if(whosOnBox(posX-2,posY-1)==-1 || whosOnBox(posX-2,posY-1)>5)
                out->push_back(Point(posX-2,posY-1));
        }
    }

    void validMovesWhiteHorseman(int posX, int posY, vector<Point> *out){

        if(posX-1>=0 && posY-3>=0){
            if(whosOnBox(posX-1,posY-3)==-1 || whosOnBox(posX-1,posY-3)<6)
                out->push_back(Point(posX-1,posY-3));
        }
        if(posX+1<=7 && posY-3>=0){
            if(whosOnBox(posX+1,posY-3)==-1 || whosOnBox(posX+1,posY-3)<6)
                out->push_back(Point(posX+1,posY-3));
        }
        if(posX+2<=7 && posY-1>=0){
            if(whosOnBox(posX+2,posY-1)==-1 || whosOnBox(posX+2,posY-1)<6)
                out->push_back(Point(posX+2,posY-1));
        }
        if(posX+2<=7 && posY+1<=7){
            if(whosOnBox(posX+2,posY+1)==-1 || whosOnBox(posX+2,posY+1)<6)
                out->push_back(Point(posX+2,posY+1));
        }
        if(posX+1<=7 && posY+3<=7){
            if(whosOnBox(posX+1,posY+3)==-1 || whosOnBox(posX+1,posY+3)<6)
                out->push_back(Point(posX+1,posY+3));
        }
        if(posX-1>=0 && posY+3<=7){
            if(whosOnBox(posX-1,posY+3)==-1 || whosOnBox(posX-1,posY+3)<6)
                out->push_back(Point(posX-1,posY+3));
        }
        if(posX-2>=0 && posY+1<=7){
            if(whosOnBox(posX-2,posY+1)==-1 || whosOnBox(posX-2,posY+1)<6)
                out->push_back(Point(posX-2,posY+1));
        }
        if(posX-2>=0 && posY-1>=0){
            if(whosOnBox(posX-2,posY-1)==-1 || whosOnBox(posX-2,posY-1)<6)
                out->push_back(Point(posX-2,posY-1));
        }
    }

    void validMovesBlackBishop(int posX, int posY, vector<Point> *out){
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        while(tmpX < 7 || tmpY > 0){//Pohyb na Severovychod
            if(whosOnBox(posX+i,posY-i)==-1){
                out->emplace_back(Point(posX+i,posY-i));
                i++;
                tmpX++;
                tmpY--;
            }else{
                if(whosOnBox(posX+i,posY-i)>=6)
                    out->emplace_back(Point(posX+i,posY-i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 || tmpY < 7){//Pohyb na JuhoVychod
            if(whosOnBox(posX+i,posY+i)==-1){
                out->emplace_back(Point(posX+i,posY+i));
                i++;
                tmpX++;
                tmpY++;
            }else{
                if(whosOnBox(posX+i,posY+i)>=6)
                    out->emplace_back(Point(posX+i,posY+i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY < 7){//Pohyb na JuhoZapad
            if(whosOnBox(posX-i,posY+i)== -1){
                out->emplace_back(Point(posX-i,posY+i));
                i++;
                tmpX--;
                tmpY++;
            }else {
                if (whosOnBox(posX - i, posY + i) >= 6)
                    out->emplace_back(Point(posX - i, posY + i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY > 0){//Pohyb na SeveroZapad
            if(whosOnBox(posX-i,posY-i)== -1){
                out->emplace_back(Point(posX-i,posY-i));
                i++;
                tmpX--;
                tmpY--;
            }else {
                if (whosOnBox(posX - i, posY - i) >= 6)
                    out->emplace_back(Point(posX - i, posY - i));
                break;
            }
        }
    }

    void validMovesWhiteBishop(int posX, int posY, vector<Point> *out){
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        while(tmpX < 7 || tmpY > 0){//Pohyb na Severovychod
            if(whosOnBox(posX+i,posY-i)==-1){
                out->emplace_back(Point(posX+i,posY-i));
                i++;
                tmpX++;
                tmpY--;
            }else{
                if(whosOnBox(posX+i,posY-i)<6)
                    out->emplace_back(Point(posX+i,posY-i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 || tmpY < 7){//Pohyb na JuhoVychod
            if(whosOnBox(posX+i,posY+i)==-1){
                out->emplace_back(Point(posX+i,posY+i));
                i++;
                tmpX++;
                tmpY++;
            }else{
                if(whosOnBox(posX+i,posY+i)<6)
                    out->emplace_back(Point(posX+i,posY+i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY < 7){//Pohyb na JuhoZapad
            if(whosOnBox(posX-i,posY+i)== -1){
                out->emplace_back(Point(posX-i,posY+i));
                i++;
                tmpX--;
                tmpY++;
            }else {
                if (whosOnBox(posX - i, posY + i) < 6)
                    out->emplace_back(Point(posX - i, posY + i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY > 0){//Pohyb na SeveroZapad
            if(whosOnBox(posX-i,posY-i)== -1){
                out->emplace_back(Point(posX-i,posY-i));
                i++;
                tmpX--;
                tmpY--;
            }else {
                if (whosOnBox(posX - i, posY - i) < 6)
                    out->emplace_back(Point(posX - i, posY - i));
                break;
            }
        }
    }

    void validMovesBlackQueen(int posX, int posY, vector<Point> *out){
        //Kralovna obsahuje vezu a strelca do kopy, hor sa na kopirovanie a modli sa, aby neboli strelec s konom chybne
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //Skopirovany black rook
        while(tmpX < 7){//Prezeranie policok na pravo
            if(whosOnBox(posX+i,posY)==-1){
                out->emplace_back(Point(posX+i,posY));
                i++;
                tmpX++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(whosOnBox(posX+i,posY)>=6)
                    out->emplace_back(Point(posX+i,posY));
                break;
            }
        }
        i=1;
        tmpX=posX;
        while(tmpX > 0){//Prezeranie policok na lavo
            if(whosOnBox(posX-i,posY)==-1){
                out->emplace_back(Point(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(whosOnBox(posX+i,posY)>=6)
                    out->emplace_back(Point(posX-i,posY));
                break;
            }
        }
        i=1;
        while(tmpY < 7){//Prezeranie policek pod figurkou
            if(whosOnBox(posX,posY+i)==-1){
                out->emplace_back(Point(posX,posY+i));
                i++;
                tmpY++;
            }else{
                if(whosOnBox(posX,posY+i)>=6)
                    out->emplace_back(Point(posX,posY+i));
                break;
            }
        }
        i=1; tmpY=posY;
        while(tmpY > 0){//Prezeranie policek nad figurkou
            if(whosOnBox(posX,posY-i)==-1){
                out->emplace_back(Point(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(whosOnBox(posX,posY-i)>=6)
                    out->emplace_back(Point(posX,posY-i));
                break;
            }
        }
        i=1;tmpX=posX;tmpY=posY;
        //Skopirovany black bishop
        while(tmpX < 7 || tmpY > 0){//Pohyb na Severovychod
            if(whosOnBox(posX+i,posY-i)==-1){
                out->emplace_back(Point(posX+i,posY-i));
                i++;
                tmpX++;
                tmpY--;
            }else{
                if(whosOnBox(posX+i,posY-i)>=6)
                    out->emplace_back(Point(posX+i,posY-i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 || tmpY < 7){//Pohyb na JuhoVychod
            if(whosOnBox(posX+i,posY+i)==-1){
                out->emplace_back(Point(posX+i,posY+i));
                i++;
                tmpX++;
                tmpY++;
            }else{
                if(whosOnBox(posX+i,posY+i)>=6)
                    out->emplace_back(Point(posX+i,posY+i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY < 7){//Pohyb na JuhoZapad
            if(whosOnBox(posX-i,posY+i)== -1){
                out->emplace_back(Point(posX-i,posY+i));
                i++;
                tmpX--;
                tmpY++;
            }else {
                if (whosOnBox(posX - i, posY + i) >= 6)
                    out->emplace_back(Point(posX - i, posY + i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY > 0){//Pohyb na SeveroZapad
            if(whosOnBox(posX-i,posY-i)== -1){
                out->emplace_back(Point(posX-i,posY-i));
                i++;
                tmpX--;
                tmpY--;
            }else {
                if (whosOnBox(posX - i, posY - i) >= 6)
                    out->emplace_back(Point(posX - i, posY - i));
                break;
            }
        }
    }

    void validMovesWhiteQueen(int posX, int posY, vector<Point> *out){
        //Kralovna obsahuje vezu a strelca do kopy, hor sa na kopirovanie a modli sa, aby neboli strelec s konom chybne
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //skopirovany white rook
        while(tmpX < 7){//Prezeranie policok na pravo
            if(whosOnBox(posX+i,posY)==-1){
                out->emplace_back(Point(posX+i,posY));
                i++;
                tmpX++;
            }else{//jedna sa o figurku supera alebo nasu figurku?
                if(whosOnBox(posX+i,posY)<6)
                    out->emplace_back(Point(posX+i,posY));
                break;
            }
        }
        i=1;
        tmpX=posX;
        while(tmpX > 0){//Prezeranie policok na lavo
            if(whosOnBox(posX-i,posY)==-1){
                out->emplace_back(Point(posX-i,posY));
                i++;
                tmpX--;
            }else{
                if(whosOnBox(posX+i,posY)<6)
                    out->emplace_back(Point(posX-i,posY));
                break;
            }
        }
        i=1;
        while(tmpY < 7){//Prezeranie policek pod figurkou
            if(whosOnBox(posX,posY+i)==-1){
                out->emplace_back(Point(posX,posY+i));
                i++;
                tmpY++;
            }else{
                if(whosOnBox(posX,posY+i)<6)
                    out->emplace_back(Point(posX,posY+i));
                break;
            }
        }
        i=1; tmpY=posY;
        while(tmpY > 0){//Prezeranie policek nad figurkou
            if(whosOnBox(posX,posY-i)==-1){
                out->emplace_back(Point(posX,posY-i));
                i++;
                tmpY--;
            }else{
                if(whosOnBox(posX,posY-i)<6)
                    out->emplace_back(Point(posX,posY-i));
                break;
            }
        }
        i=1;tmpX=posX;tmpY=posY;

        //Skopirovany white bishop
        while(tmpX < 7 || tmpY > 0){//Pohyb na Severovychod
            if(whosOnBox(posX+i,posY-i)==-1){
                out->emplace_back(Point(posX+i,posY-i));
                i++;
                tmpX++;
                tmpY--;
            }else{
                if(whosOnBox(posX+i,posY-i)<6)
                    out->emplace_back(Point(posX+i,posY-i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX < 7 || tmpY < 7){//Pohyb na JuhoVychod
            if(whosOnBox(posX+i,posY+i)==-1){
                out->emplace_back(Point(posX+i,posY+i));
                i++;
                tmpX++;
                tmpY++;
            }else{
                if(whosOnBox(posX+i,posY+i)<6)
                    out->emplace_back(Point(posX+i,posY+i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY < 7){//Pohyb na JuhoZapad
            if(whosOnBox(posX-i,posY+i)== -1){
                out->emplace_back(Point(posX-i,posY+i));
                i++;
                tmpX--;
                tmpY++;
            }else {
                if (whosOnBox(posX - i, posY + i) < 6)
                    out->emplace_back(Point(posX - i, posY + i));
                break;
            }
        }
        i=1;
        tmpX=posX;
        tmpY=posY;
        while(tmpX > 0 || tmpY > 0){//Pohyb na SeveroZapad
            if(whosOnBox(posX-i,posY-i)== -1){
                out->emplace_back(Point(posX-i,posY-i));
                i++;
                tmpX--;
                tmpY--;
            }else {
                if (whosOnBox(posX - i, posY - i) < 6)
                    out->emplace_back(Point(posX - i, posY - i));
                break;
            }
        }
    }

    void validMovesBlackKing(int posX, int posY, vector<Point> *out){
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //No mily moj, tu potrebujes sledovat, ci ta niekto po tvojom super pohybe nebude sachovat, enjoy :)

        if(posX>0 && posY>0){
            if(whosOnBox(posX-1,posY-1)==-1)
                out->push_back(Point(posX-1,posY-1));
            if(whosOnBox(posX-1,posY-1) > 5)
                out->push_back(Point(posX-1,posY-1));
        }
        if(posY>0){
            if(whosOnBox(posX,posY-1)==-1)
                out->push_back(Point(posX,posY-1));
            if(whosOnBox(posX,posY-1)>5)
                out->push_back(Point(posX,posY-1));
        }
        if(posX<7 && posY>0){
            if(whosOnBox(posX+1,posY-1)==-1)
                out->push_back(Point(posX+1,posY-1));
            if(whosOnBox(posX+1,posY-1)>5)
                out->push_back(Point(posX+1,posY-1));
        }
        if(posX<7){
            if(whosOnBox(posX+1,posY)==-1)
                out->push_back(Point(posX+1,posY));
            if(whosOnBox(posX+1,posY)>5)
                out->push_back(Point(posX+1,posY));
        }
        if(posX<7 && posY<7){
            if(whosOnBox(posX+1,posY+1)==-1)
                out->push_back(Point(posX+1,posY+1));
            if(whosOnBox(posX+1,posY+1)>5)
                out->push_back(Point(posX+1,posY+1));
        }
        if(posY<7){
            if(whosOnBox(posX,posY+1)==-1)
                out->push_back(Point(posX,posY+1));
            if(whosOnBox(posX,posY+1)>5)
                out->push_back(Point(posX,posY+1));
        }
        if(posX>0 && posY<7){
            if(whosOnBox(posX-1,posY+1)==-1)
                out->push_back(Point(posX-1,posY+1));
            if(whosOnBox(posX-1,posY+1)>5)
                out->push_back(Point(posX-1,posY+1));
        }
        if(posX>0){
            if(whosOnBox(posX-1,posY)==-1)
                out->push_back(Point(posX-1,posY));
            if(whosOnBox(posX-1,posY)>5)
                out->push_back(Point(posX-1,posY));
        }
    }

    void validMovesWhiteKing(int posX, int posY, vector<Point> *out){
        int tmpX=posX;
        int tmpY=posY;
        int i=1;

        //No mily moj, tu potrebujes sledovat, ci ta niekto po tvojom super pohybe nebude sachovat, enjoy :)

        if(posX>0 && posY>0){
            if(whosOnBox(posX-1,posY-1)==-1)
                out->push_back(Point(posX-1,posY-1));
            if(whosOnBox(posX-1,posY-1) < 6)
                out->push_back(Point(posX-1,posY-1));
        }
        if(posY>0){
            if(whosOnBox(posX,posY-1)==-1)
                out->push_back(Point(posX,posY-1));
            if(whosOnBox(posX,posY-1)< 6)
                out->push_back(Point(posX,posY-1));
        }
        if(posX<7 && posY>0){
            if(whosOnBox(posX+1,posY-1)==-1)
                out->push_back(Point(posX+1,posY-1));
            if(whosOnBox(posX+1,posY-1)< 6)
                out->push_back(Point(posX+1,posY-1));
        }
        if(posX<7){
            if(whosOnBox(posX+1,posY)==-1)
                out->push_back(Point(posX+1,posY));
            if(whosOnBox(posX+1,posY)< 6)
                out->push_back(Point(posX+1,posY));
        }
        if(posX<7 && posY<7){
            if(whosOnBox(posX+1,posY+1)==-1)
                out->push_back(Point(posX+1,posY+1));
            if(whosOnBox(posX+1,posY+1)< 6)
                out->push_back(Point(posX+1,posY+1));
        }
        if(posY<7){
            if(whosOnBox(posX,posY+1)==-1)
                out->push_back(Point(posX,posY+1));
            if(whosOnBox(posX,posY+1)< 6)
                out->push_back(Point(posX,posY+1));
        }
        if(posX>0 && posY<7){
            if(whosOnBox(posX-1,posY+1)==-1)
                out->push_back(Point(posX-1,posY+1));
            if(whosOnBox(posX-1,posY+1)< 6)
                out->push_back(Point(posX-1,posY+1));
        }
        if(posX>0){
            if(whosOnBox(posX-1,posY)==-1)
                out->push_back(Point(posX-1,posY));
            if(whosOnBox(posX-1,posY)< 6)
                out->push_back(Point(posX-1,posY));
        }
    }
};

int main(int argc, char *argv[])
{
    /*
    chess_board board;
    board.draw_board();
    board.draw_pawns();
    board.deleteBoard();
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
