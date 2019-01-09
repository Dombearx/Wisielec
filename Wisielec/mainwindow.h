#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <stdlib.h>

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QtWidgets>
#include <QVector>

#include "gamewindow.h"
#include "server.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void waitForServer();

protected:
    QTimer * connTimeoutTimer;
    void newGameBtnHit();
    void joinGameBtnHit();

private:
    Ui::MainWindow *ui;
    bool finish;
    int serverCount;
    QList<char*> ports;
};

#endif // MAINWINDOW_H
