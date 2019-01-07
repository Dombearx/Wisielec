#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <poll.h> 
#include <thread>
#include <cstdio>



using namespace std;


int points;

GameWindow::GameWindow(QString host, int port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setHost(host);
    this->setPort(port);
	this->points = 0;
}



GameWindow::~GameWindow()
{
    delete ui;
}



void GameWindow::connectToServer(){
    // Resolve arguments to IPv4 address with a port number
	addrinfo *resolved, hints={.ai_flags=0, .ai_family=AF_INET, .ai_socktype=SOCK_STREAM};
	int res = getaddrinfo(localhost, 27001, &hints, &resolved);
	if(res || !resolved) error(1, 0, "getaddrinfo: %s", gai_strerror(res));
	
	// create socket
	int sock = socket(resolved->ai_family, resolved->ai_socktype, 0);
	if(sock == -1) error(1, errno, "socket failed");
	
	// attept to connect
	res = connect(sock, resolved->ai_addr, resolved->ai_addrlen);
	if(res) error(1, errno, "connect failed");
	
	// free memory
	freeaddrinfo(resolved);
	
	// read from stdin, write to socket
	thread t1(listenToKeyboard, sock);
	t1.detach();

/****************************/
	while(true) {
		// read from socket, write to stdout
		ssize_t bufsize1 = 255, received1;
		char buffer1[bufsize1];
		received1 = readData(sock, buffer1, bufsize1);
		if(buffer1[2] == 'T'){
			//Trzeba dodać punkty
			//Odkryć literę buffer1[0] o indexie (int) buffer1[1]
		}
		if(buffer1[2] == 'K'){
			//Trzeba zwiększyć wisielca
		}
		writeData(1, buffer1, received1);
	}
/****************************/
	
	close(sock);

}


/**
Dodać do przycisku
**/

void GameWindow::socketConnected() {
    connTimeoutTimer->stop();
    connTimeoutTimer->deleteLater();
}

ssize_t readData(int fd, char * buffer, ssize_t buffsize){
	auto ret = read(fd, buffer, buffsize);
	if(ret==-1) error(1,errno, "read failed on descriptor %d", fd);
	return ret;
}

void writeData(int fd, char * buffer, ssize_t count){
	auto ret = write(fd, buffer, count);
	if(ret==-1) error(1, errno, "write failed on descriptor %d", fd);
	if(ret!=count) error(0, errno, "wrote less than requested to descriptor %d (%ld/%ld)", fd, count, ret);
}

void listenToKeyboard(int sock){
	while(true) {
		ssize_t bufsize2 = 255, received2;
		char buffer2[bufsize2];
		received2 = readData(0, buffer2, bufsize2);
		if(buffer2[2] == 'T'){
			//Trzeba dodać punkty
		}
		if(buffer2[2] == 'K'){
			//Trzeba zwiększyć wisielca
		}
		writeData(sock, buffer2, received2);
	}
}
