#include <iostream>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    finish = false;
    serverCount = 0;
    ui->setupUi(this);
    connect(ui->joinGameBtn, &QPushButton::clicked, this, &MainWindow::joinGameBtnHit);
    connect(ui->newGameBtn, &QPushButton::clicked, this, &MainWindow::newGameBtnHit);
}

MainWindow::~MainWindow() {
    finish = true;
    delete ui;
    this->destroy(true,true);
}

void MainWindow::newGameBtnHit() {
    int port = ui->portSpinBox_2->value();
    const char * str = ui->portSpinBox_2->text().toStdString().c_str();
    ports.append((char*) str);
    serverCount++;
    GameWindow* game1 = new GameWindow("localhost", port, true);
    game1->show();
}

void MainWindow::joinGameBtnHit() {
    auto host = ui->hostLineEdit->text();
    int port = ui->portSpinBox->value();
    GameWindow* game2 = new GameWindow(host, port, false);
    game2->show();
}

void MainWindow::waitForServer() {
    int i = 0;
    while(!this->finish) {
        if(i < serverCount) {
            Server* server = new Server(ports.at(i));
            std::thread(&Server::run, server).detach();
            i=i+1;
        }
    }
}
