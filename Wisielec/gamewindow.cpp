#include <iostream>
#include <unistd.h>
#include <QMessageBox>

#include "gamewindow.h"
#include "ui_gamewindow.h"

using namespace std;

GameWindow::GameWindow(QString host, int port, bool ser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    s = ser;
    ui->setupUi(this);
    ServerHost = host;
    ServerPort = port;
    if(s) this_thread::sleep_for(chrono::milliseconds(1000));

    connectToServer();
}

GameWindow::~GameWindow()
{
    delete ui;
    cout << "Koniec" << endl;
    if(this->s) {
        sendToServer('0'); //Zamknięcie serwera
        //tserver.join();
    }
}

void GameWindow::connectToServer(){
    sock = new QTcpSocket(this);
    sock->connectToHost(ServerHost, ServerPort);

    connect(sock, &QTcpSocket::connected, this, &GameWindow::socketConnected);
    connect(sock, &QTcpSocket::readyRead, this, &GameWindow::readFromServer);

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
    cout << "Connected" << endl;
    sendToServer('1'); //Prosba o dolaczenie (jesli dolaczy w momencie kiedy gra juz trwa)
}

void GameWindow::readFromServer() {
    QByteArray date = sock->read(512);
    if(date[0] == '1')
        startGame();
    else if(date[0] == '2' || date[0] == '3' || date[0] == '4' || date[0] == '5')
        newRound(date);
    else if(date[0] == '6')
        inGame();
    else if(date[0] >= 'A' && date[0] <= 'Z')
        cout << date[0] << endl;
}

void GameWindow::sendToServer(char c) {
    QString str = QChar(c);
    QByteArray text = str.toUtf8();
    sock->write(text);
}

void GameWindow::startGame() {
    ui->textEdit->setEnabled(true);
    ui->letterEdit->setEnabled(true);
    ui->letterBtn->setEnabled(true);
    ui->textEdit->setText("Podaj litere");
    ui->label->setText("Runda 1");
}

void GameWindow::newRound(QByteArray d) {
    QString round = "Runda ";
    round.append(d.at(0));
    ui->letterBtn->setEnabled(true);
    ui->label->setText(round);
}

void GameWindow::inGame() {
    ui->label->setText("Połączono. Oczekiwanie na graczy.");
}

void GameWindow::destroyWindow() {
    this->destroy(true,true);
}
