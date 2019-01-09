#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <poll.h>
#include <thread>
#include <unordered_set>
#include <signal.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Server {

public:
    Server(char * p);
    ~Server();
    void ctrl_c(int);
    void run();
    void sendToAllBut(int fd, char * buffer, int count);
    uint16_t readPort(char * txt);
    void setReuseAddr(int sock);
    void sendToAll(int fd, char * buffer, int count);
    void readMessage(int fd);
    void closeServer();
private:
    char * prt;
    int servFd;
    unordered_set<int> clientFds;
    string word;
    bool endGame;
};




#endif // SERVER_H
