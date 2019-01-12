#include <QMessageBox>

#include "gamewindow.h"
#include "ui_gamewindow.h"

using namespace std;

GameWindow::GameWindow(QString host, int port, bool ser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    end = false;
    s = ser;
    ui->setupUi(this);
    ServerHost = host;
    ServerPort = port;
    hostServer = host.toStdString();
    portServer = port;
    if(s) this_thread::sleep_for(chrono::milliseconds(1000));

    connectToServer();
}

GameWindow::~GameWindow()
{
    end = true;
    delete ui;
    if(s) {
        s = false;
        sendToServer('0');
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
    sendToServer('1');
}

void GameWindow::readFromServer() {
    QByteArray date = sock->read(512);
        cout << date[0] << endl;

    if(date[0] == '0' && !end) {
        QMessageBox::critical(this, "Błąd", "Brak połączenia");
        this->~GameWindow();
    } else if(date[0] == '1')
        startGame(date);
    else if(date[0] == '2' || date[0] == '3' || date[0] == '4' || date[0] == '5')
        newRound(date);
    else if(date[0] == '6') {
        inGame(date[1]);
        sendToServer('2');
    } else if(date[0] == '7') {
        updateWord(date.remove(0, 1));
    } else if(date[0] == '8') {
        const QString c = "";
        ui->letterEdit->setText(c);
    } else if(date[0] == '9') {
        endGame();
    } else if(date[0] >= 'A' && date[0] <= 'Z')
        cout << date[0] << endl;
}

void GameWindow::sendToServer(char c) {
    QString str = QChar(c);
    QByteArray text = str.toUtf8();
    sock->write(text);
}

void GameWindow::startGame(QString word) {
    ui->textEdit->setEnabled(true);
    ui->letterEdit->setEnabled(true);
    ui->letterBtn->setEnabled(true);
    updateWord(word.remove(0, 1));
    ui->label->setText("Runda 1");
}

void GameWindow::newRound(QString word) {
    QString round = "Runda ";
    round.append(word[0]);
    const QString c = "";
    ui->letterEdit->setText(c);
    ui->letterBtn->setEnabled(true);
    ui->label->setText(round);
    updateWord(word.remove(0, 1));
}

void GameWindow::inGame(char c) {
    ui->label->setText("Połączono. Oczekiwanie na graczy.");
    int nr = c;
    cout << "player" << nr << endl;
    if(nr > 9) {
        QString name = "player";
        name.append(QString::number(c));
        ui->userEdit->setText(name);
    } else {
        QString name = "player0";
        name.append(QString::number(c));
        ui->userEdit->setText(name);
    }
}

void GameWindow::updateWord(QString word) {
    QString wordShow = "";
    for(int i = 0; i < word.size() - 1; i++) {
        wordShow.append(word.at(i));
        wordShow.append(" ");
    }
    wordShow.append(word.at(word.size()-1));
    ui->textEdit->setHtml("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\
                          p, li { white-space: pre-wrap; }\
                          </style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\
                          <p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\
                          font-size:20pt;\">"+wordShow+"</span></p></body></html>");
}

void GameWindow::endGame() {
    updateWord(" Koniec gry");
    const QString c = "";
    ui->letterBtn->setEnabled(false);
    ui->letterEdit->setText(c);
    ui->letterEdit->setEnabled(false);
}

void GameWindow::on_letterBtn_clicked()
{
    char *letter = ((QByteArray) ui->letterEdit->text().toLocal8Bit()).toUpper().data();

    sendToServer(letter[0]);
}

void GameWindow::destroyWindow() {
    this->destroy(true,true);
}
