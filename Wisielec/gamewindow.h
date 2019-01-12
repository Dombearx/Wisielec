#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>


#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>
#include <QObject>
#include <QProcess>
#include <QDateTime>

using namespace std;

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
    //void sendToServer(QString t);

    void startGame(QString word);
    void newRound(QString word);
    void inGame(char c);
    void updateWord(QString word);
    void endGame();

private slots:
    void on_letterBtn_clicked();

private:
    Ui::GameWindow *ui;
    int desc;
    QString ServerHost;
    quint16 ServerPort;
    string hostServer;
    int portServer;
    int serverFd;
    bool s; //Zmienna informujaca czy dany klient jest odpowiedzialny za stworzenie serwera dla gry w ktorej uczestniczy
    bool end;
};

#endif // GAMEWINDOW_H
