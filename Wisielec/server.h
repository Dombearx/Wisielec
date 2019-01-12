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
#include <string.h>
#include <vector>

#include "player.h"

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
    void sendToOne(int clientFd, char* txt, int l);
    void sendToAll(char* txt, int l);
    void readMessage(int fd, int nr);
    void closeServer();
    void connectPlayerToServer(int fd);
    void waitForPlayers();
    int updateWord(char c);
    bool checkWord();
    void nextRound();
    void endGame();

    string intToString(int n);
private:
    char * prt;
    int serverFd;
    unordered_set<int> clientFds;
    int clientServFd;
    int playersNumber;
    int round;

    string word[5] = {"JEBACJEBACZ", "STUDIA", "NADCHODZI", "SESJA", "WARUNY"};
    char actualWord[255];
    bool ready;
    bool end;
    bool wait;

    vector<Player*> players;
};




#endif // SERVER_H
