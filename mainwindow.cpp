#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <Qpixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->incialized=false;

    connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)), &g, SLOT(vyriesKlik(int,int)) );
    connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(appendLog(int,int)));
    connect(&g, SIGNAL(validMoves(const QList<BoardPosition>&)),this, SLOT(drawValidMoves(const QList<BoardPosition>&)));
    connect(&g, SIGNAL(updateChessboardSignal(std::vector<ChessPiece*>,std::vector<ChessPiece*>)), this, SLOT(updateChessboardSlot(std::vector<ChessPiece*>,std::vector<ChessPiece*>)));
    initBoard();


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard()
{

    // setup table
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
    //ui->tableWidget->horizontalHeader()->setStyleSheet("margin-left: auto; text-align: center;");
    //ui->tableWidget->verticalHeader()->setStyleSheet("margin-top: auto;");
    // setup chess pieces
   std::vector<ChessPiece*> b = (g.getBoard()->getChessPieceAliveBlack());

   std::vector<ChessPiece*> w= g.getBoard()->getChessPieceAliveWhite();
   drawBoard(b,w);



}


void MainWindow::drawBoard(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w)
{


/*
    if(this->incialized == true){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(ui->tableWidget->item(i,j))
                    ui->tableWidget->item(i,j)->icon();
            }
        }
    }
*/

    for(auto& cp : b){
        ui->tableWidget->item(cp->getPosition()->getX(),cp->getPosition()->getY())->setIcon(QIcon(PRO_PWD+ QString("\\icons\\") + cp->getIconName()));
        //ui->tableWidget->item( cp->getPosition()->getX(), cp->getPosition()->getY())->setText( QString::number (cp->getType()));
        //ui->log->append("Black: " + QString::number(cp->getType()));
    }

    for(auto& cp : w){
        ui->tableWidget->item(cp->getPosition()->getX(),cp->getPosition()->getY())->setIcon(QIcon(PRO_PWD+ QString("\\icons\\") + cp->getIconName()));
        //ui->log->append("White: " + QString::number(cp->getType()));
    }

    this->incialized = true;


}


void MainWindow::appendLog(int row, int col)
{
    ui->log->append(QString::number(row) + " " + QString::number(col) + "Gamemode: " + QString::number(this->g.gameMode) );
}

void MainWindow::drawValidMoves(const QList<BoardPosition> & vm){

    for(const BoardPosition&  bp: vm){
        ui->tableWidget->item(bp.getX(),bp.getY())->setSelected(true);
    }
}

void MainWindow::updateChessboardSlot(const std::vector<ChessPiece *> &b, const std::vector<ChessPiece *> &w)
{
    drawBoard(b,w);
}


