#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Signal for solving the click event on our chessBoard
    connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)), &g, SLOT(solveClick(int,int)) );
    //Signal for writeing to our log, including ovveriding of in params
    connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(appendLog(int,int)));
    connect(&g, SIGNAL(appendLog(const QList<BoardPosition>&)),this, SLOT(appendLog(const QList<BoardPosition>&)));
    connect(&g, SIGNAL(validMoves(const QList<BoardPosition>&)),this, SLOT(drawValidMoves(const QList<BoardPosition>&)));
    connect(&g, SIGNAL(updateChessboardSignal(std::vector<ChessPiece*>,std::vector<ChessPiece*>)), this, SLOT(updateChessboardSlot(std::vector<ChessPiece*>,std::vector<ChessPiece*>)));
    connect(&g, SIGNAL(updateKickedPiecesSignal(std::vector<ChessPiece*>,std::vector<ChessPiece*>)), this, SLOT(updateKickedPiecesSlot(std::vector<ChessPiece*>,std::vector<ChessPiece*>)));

    initBoard();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initBoard(){

    // Setup of our gui chessBoard
    for(int i = 0; i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setRowHeight(i,60);
    }

    for(int i = 0; i<ui->tableWidget->columnCount();i++){
        ui->tableWidget->setColumnWidth(i,0);
    }

    for(int i = 0;i<ui->tableWidget->rowCount();i++){
        for(int j = 0;j<ui->tableWidget->columnCount();j++){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem);
            ui->tableWidget->item(i,j)->setFlags( ui->tableWidget->item(i,j)->flags()^(Qt::ItemIsEditable));
        }
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setIconSize(QSize(55,55));
    drawBoard(g.getBoard()->getChessPieceAliveBlack(),g.getBoard()->getChessPieceAliveWhite());
}

//Drawing out bord with valid chessPieces
void MainWindow::drawBoard(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w){

    //Hiding of "dead" chessPieces
    for(int i = 0;i<ui->tableWidget->rowCount();i++){
        for(int j = 0;j<ui->tableWidget->columnCount();j++){
            if(ui->tableWidget->item(i,j)){
                ui->tableWidget->item(i,j)->setIcon(QIcon());
                ui->tableWidget->item(i,j)->setSelected(false);
            }
        }
    }

    for(auto& cp : b){
        ui->tableWidget->item(cp->getPosition()->getX(),cp->getPosition()->getY())->setIcon(QIcon(PRO_PWD+ QString("\\icons\\") + cp->getIconName()));
    }

    for(auto& cp : w){
        ui->tableWidget->item(cp->getPosition()->getX(),cp->getPosition()->getY())->setIcon(QIcon(PRO_PWD+ QString("\\icons\\") + cp->getIconName()));
    }
}

void MainWindow::appendLog(const QString s){
    ui->log->append(s);
}

void MainWindow::appendLog(const QList<BoardPosition> & validMoves){
    for(const auto& c: validMoves){
        ui->log->append("("+QString('A' + c.getY()) + "," + QString::number(1 +c.getX())+  ")");
    }
}

void MainWindow::appendLog(int row, int col){
    ui->log->append(QString::number(row) + " " + QString::number(col) + "Gamemode: " + QString::number(this->g.gameMode) );
}

void MainWindow::drawValidMoves(const QList<BoardPosition> & vm){
    for(const BoardPosition&  bp: vm){
        ui->tableWidget->item(bp.getX(),bp.getY())->setSelected(true);
    }
}

void MainWindow::updateChessboardSlot(const std::vector<ChessPiece *> &b, const std::vector<ChessPiece *> &w){
    drawBoard(b,w);
}

void MainWindow::updateKickedPiecesSlot(const std::vector<ChessPiece *> &b, const std::vector<ChessPiece *> &w)
{
    ui->list_black_kickout->clear();
    ui->list_white_kickout->clear();
    for(ChessPiece* i : b){
        ui->list_black_kickout->addItem(i->getIconName());
    }
    for(ChessPiece* i : w){
        ui->list_white_kickout->addItem(i->getIconName());
    }
}


void MainWindow::on_list_black_kickout_itemClicked(QListWidgetItem *item)
{
    emit deadPieceSelectedSignal(item->text());
}
