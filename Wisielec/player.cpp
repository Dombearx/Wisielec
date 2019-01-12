#include "player.h"

Player::Player(int fd, string n, int nr, int r) {
    playerFd = fd;
    name = n;
    number = nr;
    int live[5] = {9, 9, 9, 9, 9};
    points = 0;
    endRound = false;
    connected = true;
    round = r;
}

Player::~Player() {

}

void Player::add(int p) {
    points += p;
}

void Player::hangPoint(int round) {
    if(live[round-1] > 0)
        live[round-1] = live[round - 1];
    if(live[round-1] == 0)
        endRound = true;
}

void Player::newRound(int r) {
    endRound = false;
    round = r;
    endRound = false;
}
