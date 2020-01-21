#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

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
    void pohniStrelcom(int, int);
private slots:
    void appendLog(int,int);
    void drawValidMoves(const QList<BoardPosition>&);
};
#endif // MAINWINDOW_H
