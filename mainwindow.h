#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "game.h"
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Game g;
    void initBoard();
    void drawBoard(const std::vector<ChessPiece*>&, const std::vector<ChessPiece*>& );
signals:
    void deadPieceSelectedSignal(QString);
private slots:
    void appendLog(QString);
    void appendLog(const QList<BoardPosition>&);
    void appendLog(int,int);
    void appendFen(QString fen);
    void drawValidMoves(const QList<BoardPosition>&);
    void updateChessboardSlot(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w);
    void updateKickedPiecesSlot(const std::vector<ChessPiece*> &b, const std::vector<ChessPiece*> &w);

    void on_list_white_kickout_itemClicked(QListWidgetItem *item);
    void on_list_black_kickout_itemClicked(QListWidgetItem *item);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
