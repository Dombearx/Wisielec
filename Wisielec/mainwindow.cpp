#include <iostream>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->joinGameBtn, &QPushButton::clicked, this, &MainWindow::joinGameBtnHit);
    connect(ui->newGameBtn, &QPushButton::clicked, this, &MainWindow::newGameBtnHit);
}

MainWindow::~MainWindow(){
    delete ui;
    delete game;
    this->destroy(true,true);
}

void MainWindow::newGameBtnHit(){
    int port = ui->portSpinBox->value();
    cout << "elo" << endl;
    system(SHELLSCRIPT);
    game = new GameWindow("localhost", port);
    game->show();
}

void MainWindow::joinGameBtnHit(){
    auto host = ui->hostLineEdit->text();
    int port = ui->portSpinBox_2->value();
    game = new GameWindow(host, port);
    game->show();
}
