#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <thread>
#include <unordered_set>
#include <signal.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}


// client sockets
std::unordered_set<int> clientFds;

void sendToAllBut(int fd, char * buffer, int count){
    int res;
    decltype(clientFds) bad;
    for(int clientFd : clientFds){
        if(clientFd == fd) continue;
        res = write(clientFd, buffer, count);
        if(res!=count)
            bad.insert(clientFd);
    }
    for(int clientFd : bad){
        printf("removing %d\n", clientFd);
        clientFds.erase(clientFd);
        close(clientFd);
    }
}
