#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player {
public:
    Player(int p, string n, int nr, int r);
    ~Player();
    int getFd() {return playerFd;}
    int getNumber() {return number;}
    void setNumber(int n) {number = n;}
    void setName(string n) {name = n;}
    string getName() {return name;}
    void hangPoint(int round);
    void connect() {connected = true;}
    void disconnect() {connected = false;}
    int getLives(int round) {return live[round-1];}
    bool hasLives() {return !endRound;}
    bool isConnected() {return connected;}
    void newRound(int r);
    void addPoints(int p);
    int getPoints() {return points;}
    bool operator > (Player* p1);
private:
    int playerFd;
    int number;
    string name;
    bool connected;
    bool endRound;
    int live[5];
    int points;
    int round;
};

#endif // PLAYER_H
