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
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <mutex>

#include "player.h"

using namespace std;

class Server {

public:
    Server(char * p);
    ~Server();

    void run();
    uint16_t readPort(char * txt);
    void setReuseAddr(int sock);
    void closeServer();

    void sendToAll(char* txt, int l);
    void sendToOther(int clientFd, char* txt, int l);

    void waitForPlayers();
    void connectPlayerToServer(int fd);
    void sortPlayers();
    bool compare(Player* p1, Player* p2);

    void readMessage(int fd, int nr);
    int updateWord(char c);
    bool checkWord();
    void sendWord(char c, int fd, bool all);
    void nextRound();
    void endGame();

    const char* getPort() {return prt;}
    string intToString(int n);
private:
    char * prt;

    int serverFd;
    unordered_set<int> clientFds;
    int clientServFd;

    int playersNumber;
    int round;
    string word[5];
    char actualWord[255];

    bool ready;
    bool end;
    bool wait;

    vector<Player*> players; //Wektor graczy
    vector<Player*> sorted; //Posortowany wektor graczy, będący ich rankingiem
    mutex syncMutex;
};

#endif // SERVER_H
