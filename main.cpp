#include <iostream>

using namespace std;

class chess_board{
    private:
        int ***board;
    public:

    chess_board(){

        //DYNAMIC ALLOC FOR LATER GETTER
        int ***arr = new int**[8];
        for (int i = 0; i < 8; ++i) {/////____________________________12 old
            arr[i] = new int*[8];
            for (int j = 0; j < 8; ++j)//________________________8 old
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

};

int main() {
    //QT

    chess_board board;
    board.draw_board();
    board.draw_pawns();
    board.deleteBoard();
    return 0;
}