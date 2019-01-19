#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player {
public:
    Player(int p, string n, int nr, int r);
    ~Player();

    void connect() {connected = true;}
    void disconnect() {connected = false;}

    int getFd() {return playerFd;}
    int getNumber() {return number;}
    string getName() {return name;}
    int getPoints() {return points;}
    int getLives(int round) {return live[round-1];}

    void addPoints(int p);
    void setName(string n) {name = n;}
    void setNumber(int n) {number = n;}

    bool hasLives() {return !endRound;}
    bool isConnected() {return connected;}

    void hangPoint(int round);
    void newRound(int r);

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
