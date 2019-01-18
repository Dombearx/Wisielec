#include "server.h"
#include <algorithm>
using namespace std;

Server::Server(char * p) {
    prt = p;
    serverFd = 0;
    clientServFd = 0;
    playersNumber = 0;
    round = 0;
    ready = false;
    wait = true;
}

Server::~Server() {
    closeServer();
}



void Server::run() {
    cout << prt << endl;
    auto port = readPort(prt);
    int servFd = socket(AF_INET, SOCK_STREAM, 0);
    serverFd = servFd;
    if(servFd == -1) error(1, errno, "socket failed");

    // graceful ctrl+c exit
    //signal(SIGINT, ctrl_c);
    // prevent dead sockets from throwing pipe errors on write
    signal(SIGPIPE, SIG_IGN);

    setReuseAddr(servFd);

    // bind to any address and port provided in arguments
    sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons((short)port), .sin_addr={INADDR_ANY}};
    int res = bind(servFd, (sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res) error(1, errno, "bind failed");

    // enter listening mode
    res = listen(servFd, 1);
    if(res) error(1, errno, "listen failed");

    /****************************/
    end = false;

    std::thread(&Server::waitForPlayers, this).detach();

    while(playersNumber < 10 && !end){
        connectPlayerToServer(servFd);
    }
}

void Server::connectPlayerToServer(int servFd) {
    // prepare placeholders for client address
    sockaddr_in clientAddr{0};
    socklen_t clientAddrSize = sizeof(clientAddr);

    // accept new connection
    int clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
    if(clientFd == -1) error(1, errno, "accept failed");

    // add client to all clients set
    playersNumber++;
    if(playersNumber == 1) clientServFd = clientFd; //Zapisanie fd gracza odpowiedzialnego za stworzenie gry
    clientFds.insert(clientFd);

    string name = "player";
    if(playersNumber < 10) {
        name.append("0");
        name.append(intToString(playersNumber));
    } else name.append(intToString(playersNumber));
    Player* player = new Player(clientFd, name, playersNumber, round - 1);
    players.push_back(player);
    sorted.push_back(player);

    std::thread(&Server::readMessage, this, clientFd, playersNumber).detach();
}

void Server::waitForPlayers() {
    this_thread::sleep_for(chrono::milliseconds(15000));
    round = 1;
    ready = true;
    for(int i = 0; i < word[round-1].size(); i++)
        actualWord[i] = '_';
    wait = false;
}

uint16_t Server::readPort(char * txt){
    char * ptr;
    auto port = strtol(txt, &ptr, 10);
    if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
    return port;
}

void Server::setReuseAddr(int sock){
    const int one = 1;
    int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1,errno, "setsockopt failed");
}

void Server::closeServer(){
    for(int clientFd : clientFds)
        close(clientFd);
    close(serverFd);
    cout << "Server closed" << endl;
    terminate();
}

void Server::sendToOne(int fd, char* buffer, int length) {
    ssize_t res = write(fd, buffer, length);
    if(res != length)
        printf("Usuwanie %d\n", fd);
        clientFds.erase(fd);
        close(fd);
}

void Server::sendToAll(char* buffer, int length){
    ssize_t res;
    for(int fd : clientFds){
        res = write(fd, buffer, length);
        if(res != length) {
            printf("Usuwanie %d\n", fd);
        }
    }
}

void Server::sendToOther(int client, char* buffer, int length){
    ssize_t res;
    for(int fd : clientFds){
        if(client != fd) {
            res = write(fd, buffer, length);
            if(res != length) {
                printf("Usuwanie %d\n", fd);
            }
        }
    }
}

void Server::readMessage(int clientFd, int nr) {
    while(!end) {
        // read a message
        char buffer[1] = "";
        char bufferToSend[3] = "";
        ssize_t count = read(clientFd, buffer, 1);
        if (count < 1) {
            count = 1;
            buffer[1] = '0';
        }

        if(buffer[0] == '0') {
            players.at(nr-1)->disconnect();
            bufferToSend[0] = buffer[0];
            bufferToSend[1] = '0';
            if(clientServFd == clientFd) {
                end = true;
                sendToAll(bufferToSend, 3);
                terminate();
            } else {
                write(clientFd, bufferToSend, 3);
            }
            clientFds.erase(clientFd);
            close(clientFd);
        } else if(buffer[0] == '1') { //Prośba o dołączenie do gry
            bufferToSend[0] = '6';
            bufferToSend[1] = nr;
            write(clientFd, bufferToSend, 3);
        } else if(buffer[0] == '2') { //Czekanie na rozpoczęcie gry
            if(!ready) {
                while(!ready) {this_thread::sleep_for(chrono::milliseconds(1000));}
                sendWord('1', clientFd, false);
            } else {
                sendWord('1', clientFd, false);
                sendWord('7', clientFd, true);
            }
        } else if(buffer[0] >= 'A' && buffer[0] <= 'Z' && !wait) {
            int score = updateWord(buffer[0]);
            if(score > 0) {
                players.at(nr-1)->addPoints(score);
                sendWord('7', 0, true);
                if(checkWord()) nextRound();
            } else { //Jeśli gracz popełni błąd
                players.at(nr-1)->hangPoint(round); //Odjęcie życia w rundzie
                bufferToSend[0] = '+';
                bufferToSend[1] = players.at(nr-1)->getLives(round);
                write(clientFd, bufferToSend, 3);
                bool next = true; //Sprawdzenie wszystkich aktywnych graczy, czy mają jeszcze życia
                for(Player* player: players)
                    if(player->isConnected())
                        if(player->hasLives()) next = false;
                if(next) nextRound(); //Zainicjowanie następnej rundy, jeśli wszyscy są w dupie
            }
            this_thread::sleep_for(chrono::milliseconds(60));
            write(clientFd, "8", 1); //Prośba o wyczyszczenie pola do wypisywania liter
        }
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void Server::sendWord(char c, int fd, bool all) {
    syncMutex.lock();
    sortPlayers();

    //Długość buffa do wysłania
    int l = word[round-1].size()+2; //Dodajemy 2 znaki na początku
    for(int i = 0; i < sorted.size(); i++)
        l += to_string(sorted.at(i)->getPoints()).length()+3;

    //Dodanie znaków do buffa
    char buff[l];
    buff[0] = c; //Znak informacyjny
    for(int i = 0; i < word[round-1].size(); i++)
        buff[i+1] = actualWord[i]; //Aktualne hasło
    buff[word[round-1].size()+1] = '-'; //Znak informacyjny o przejściu do rankingu i następnego grazca

    int k = 2;
    for(int i = 0; i < sorted.size(); i++) {
        const char* nr = to_string(sorted.at(i)->getNumber()).c_str();
        if(sorted.at(i)->getNumber() > 9) buff[word[round-1].size()+k] = nr[1];
        else buff[word[round-1].size()+k] = nr[0];
        k++;

        const char* c = to_string(sorted.at(i)->getPoints()).c_str();
        for(int j = 0; j < strlen(c); j++) {
            buff[word[round-1].size()+k] = c[j];
            k++;
        }
        buff[word[round-1].size()+k] = '-'; //Żeby na końcu nie było minusa
        k++;
    }

    //Wysłanie buffa
    if(all && fd == 0) {
        sendToAll(buff, l);
    } else if(all && fd != 0) {
        sendToOther(fd, buff, l);
    } else {
        write(fd, buff, l);
    }
    this_thread::sleep_for(chrono::milliseconds(100));
    syncMutex.unlock();
}

void Server::nextRound() {
    round++;
    wait = true;
    std::this_thread::sleep_for(chrono::milliseconds(2500));
    if(round == 6) {
        endGame();
    } else {
        for(int i = 0; i < word[round-1].size(); i++)
            actualWord[i] = '_';
        for (Player* player: players)
            player->newRound(round);
        sendWord(round+'0', 0, true);
        wait = false;
    }
}

void Server::endGame() {
    sendToAll("9", 2);
}

int Server::updateWord(char c) { //Aktualizuje zgadywane słowo o nowe litery
    int score = 0;
    int l = word[round-1].size();
    for(int i = 0; i < l; i++) {
        if(word[round-1].at(i) == c && actualWord[i] == '_') {
            actualWord[i] = word[round-1].at(i);
            score++;
        }
    }
    return score;
}

bool Server::checkWord() { //Sprawdza czy mamy koniec rundy
    for(int i = 0; i < word[round-1].size(); i++)
        if(actualWord[i] == '_') return 0;
    return 1;
}

void Server::sortPlayers() {
    sort(sorted.begin(), sorted.end(), [this](Player* a, Player*b) {return compare(a, b);});
}

bool Server::compare(Player* p1, Player* p2) {
    if(p1->getPoints() == p2->getPoints() ) {
        if(p1->isConnected() && !p2->isConnected()) return true;
        else if(!p1->isConnected() && p2->isConnected()) return false;
        else {
            int sumlive1 = 0, sumlive2 = 0;
            for(int i = 0; i < 5; i++) {
                sumlive1 += p1->getLives(i);
                sumlive2 += p2->getLives(i);
            }
            if(sumlive1 > sumlive2) return true;
            else return false;
        }
    } else {
        return (p1->getPoints() > p2->getPoints());
    }
}

string Server::intToString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}
