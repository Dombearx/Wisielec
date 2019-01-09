#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>
#include <QObject>
#include <QProcess>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QString host, int port,  bool ser, QWidget *parent = nullptr);
    ~GameWindow();

    void connectToServer();
    void destroyWindow();

    void setHost(QString h) {this->ServerHost = h;}
    void setPort(quint16 p) {this->ServerPort = p;}

    void setServer() {this->s = true;}
    bool isServer() {return this->s;}


protected:
    QTimer * connTimeoutTimer;
    QTcpSocket * sock;

    void socketConnected();
    void readFromServer();
    void sendToServer(char c);

    void startGame();
    void newRound(QByteArray date);
    void inGame();


private:
    Ui::GameWindow *ui;
    QString ServerHost;
    quint16 ServerPort;
    bool s; //Zmienna informujaca czy dany klient jest odpowiedzialny za stworzenie serwera dla gry w ktorej uczestniczy
};

#endif // GAMEWINDOW_H
