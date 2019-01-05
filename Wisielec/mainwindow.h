#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QtWidgets>

#include "gamewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    QTimer * connTimeoutTimer;
    void newGameBtnHit();
    void joinGameBtnHit();

private:
    Ui::MainWindow *ui;
    GameWindow *game;
};

#endif // MAINWINDOW_H
