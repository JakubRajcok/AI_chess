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

    connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)), &g, SLOT(vyriesKlik(int,int)) );
    connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(appendLog(int,int)));
    connect(&g, SIGNAL(validMoves(const QList<BoardPosition>&)),this, SLOT(drawValidMoves(const QList<BoardPosition>&)));

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
        ui->tableWidget->setRowHeight(i,30);
    }
    for(int i = 0; i<ui->tableWidget->columnCount();i++){
        ui->tableWidget->setColumnWidth(i,30);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // setup chess pieces
   QVector<ChessPiece*> b = QVector<ChessPiece*>::fromStdVector(g.getBoard()->getChessPieceAliveBlack());
   for(ChessPiece*& a : b){
       qDebug() << a->getType();
   }
  std::vector<ChessPiece*> w= g.getBoard()->getChessPieceAliveWhite();
    //rawBoard(b,w);



}

void MainWindow::drawBoard(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w)
{
    for(auto& cp : b){
        ui->tableWidget->setItem(cp->getPosition()->getX(),cp->getPosition()->getY(),new QTableWidgetItem( QString::number (cp->getType()) ));
        ui->log->append("Black: " + QString::number(cp->getType()));
    }

    for(auto& cp : w){
        ui->log->append("White: " + QString::number(cp->getType()));
        ui->tableWidget->setItem(cp->getPosition()->getX(),cp->getPosition()->getY(),new QTableWidgetItem( QString::number (cp->getType()) ));
    }
}


void MainWindow::appendLog(int row, int col)
{
    ui->log->append(QString::number(row) + " " + QString::number(col));
}

void MainWindow::drawValidMoves(const QList<BoardPosition> & vm)
{
for(const BoardPosition&  bp: vm){
    ui->tableWidget->item(bp.getX(),bp.getY())->setSelected(true);
}
}


