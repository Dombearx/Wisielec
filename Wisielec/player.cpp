#include "player.h"

Player::Player(int fd, string n, int nr, int r) {
    playerFd = fd;
    name = n;
    number = nr;
    live[0] = 12;
    live[1] = 12;
    live[2] = 12;
    live[3] = 12;
    live[4] = 12;
    points = 0;
    endRound = false;
    connected = true;
    round = r;
}

Player::~Player() {

}

void Player::addPoints(int p) {
    points += p;
}

void Player::hangPoint(int round) {
    if(live[round-1] > 0)
        live[round-1] = live[round-1] - 1;
    if(live[round-1] == 0)
        endRound = true;
}

void Player::newRound(int r) {
    endRound = false;
    round = r;
    endRound = false;
}

bool Player::operator > (Player* player) {
    if(points == player->points ) {
        if(connected && !player->connected) return true;
        else if(!connected && player->connected) return false;
        else {
            int sumlive1 = 0, sumlive2 = 0;
            for(int i = 0; i < 5; i++) {
                sumlive1 += live[i];
                sumlive2 += player->live[i];
            }
            if(sumlive1 > sumlive2) return true;
            else return false;
        }
    } else {
        return (points > player->points);
    }
}
