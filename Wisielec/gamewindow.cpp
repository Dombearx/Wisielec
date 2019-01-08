#include <iostream>
#include <QMessageBox>

#include "gamewindow.h"
#include "ui_gamewindow.h"

using namespace std;

GameWindow::GameWindow(QString host, int port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setHost(host);
    this->setPort(port);
    connectToServer();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::connectToServer(){
    sock = new QTcpSocket(this);
    sock->connectToHost(ServerHost, ServerPort);

    connect(sock, &QTcpSocket::connected, this, &GameWindow::socketConnected);

    connTimeoutTimer = new QTimer(this);
    connTimeoutTimer->setSingleShot(true);
    connect(connTimeoutTimer, &QTimer::timeout, [&]{
        connTimeoutTimer->deleteLater();
        QMessageBox::critical(this, "Error", "Connect timed out");
        this->destroy(true,true);
    });
    connTimeoutTimer->start(3000);

}

void GameWindow::socketConnected() {
    connTimeoutTimer->stop();
    connTimeoutTimer->deleteLater();
    cout << "NO ELO" << endl;
}
