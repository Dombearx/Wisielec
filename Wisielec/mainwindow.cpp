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
    windows.append(game1);
    game1->show();
}

void MainWindow::joinGameBtnHit() {
    auto host = ui->hostLineEdit->text();
    int port = ui->portSpinBox->value();
    GameWindow* game2 = new GameWindow(host, port, false);
    windows.append(game2);
    game2->show();
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
        for(int j = 0; j < windows.size(); j++) {
            if(windows.at(j)->isHidden() && !windows.at(j)->isEnd() && windows.at(j)->isActive())
                windows.at(j)->endClient();
            if(!windows.at(j)->isHidden() && windows.at(j)->isEnd()) {
                windows.at(j)->destroyWindow();
            }
        }
    }
    for(int i = 0; i < windows.size(); i++) {
        if(windows.at(i)->isHidden() && windows.at(i)->isActive()) windows.at(i)->destroyWindow();
        windows.at(i)->close();
    }
    terminate();
}
