#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SHELLSCRIPT "\
#/bin/bash \n\
./server.o \n\
clear\
"


#include <stdio.h>
#include <stdlib.h>
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
