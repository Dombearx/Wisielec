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

void MainWindow::waitForServer() {
    int i = 0;
    while(!this->isHidden()) {
        if(i < serverCount) {
            Server* server = new Server(ports.at(i));
            servers.append(server);
            std::thread(&Server::run, server).detach();
            i=i+1;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    terminate();
}

void MainWindow::newGameBtnHit() {
    int port = ui->portSpinBox_2->value();
    const char * str = ui->portSpinBox_2->text().toStdString().c_str();
    bool exist = false;
    for(int i = 0; i < servers.size(); i++) {
        if(servers.at(i)->getPort() == str) exist = true;
    }
    if(exist) {
        QMessageBox::warning(this, "Błąd", "Port jest zajęty przez inny serwer!");
    } else {
        ports.append((char*) str);
        serverCount++;
        GameWindow* game1 = new GameWindow(this, "localhost", port, true);
        windows.append(game1);
        game1->show();
    }
}

void MainWindow::joinGameBtnHit() {
    auto host = ui->hostLineEdit->text();
    int port = ui->portSpinBox->value();
    GameWindow* game2 = new GameWindow(this, host, port, false);
    windows.append(game2);
    game2->show();
}
