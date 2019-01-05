#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QMessageBox>

using namespace std;

GameWindow::GameWindow(QString host, int port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setHost(host);
    this->setPort(port);
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
    });
    connTimeoutTimer->start(3000);

}

void GameWindow::socketConnected() {
    connTimeoutTimer->stop();
    connTimeoutTimer->deleteLater();
}
