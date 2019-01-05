#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QString host, int port, QWidget *parent = nullptr);
    ~GameWindow();

    void connectToServer();

    void setHost(QString h) {this->ServerHost = h;}
    void setPort(quint16 p) {this->ServerPort = p;}

protected:
    QTimer * connTimeoutTimer;
    QTcpSocket * sock;

    void socketConnected();


private:
    Ui::GameWindow *ui;
    QString ServerHost;
    quint16 ServerPort;
};

#endif // GAMEWINDOW_H
