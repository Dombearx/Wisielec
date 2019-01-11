#include "server.h"

using namespace std;

Server::Server(char * p) {
    prt = p;
    word = "HASLOO";
}

Server::~Server() {
    closeServer();
}

void Server::run() {
    cout << prt << endl;
    auto port = readPort(prt);
    cout << "NO ELO3" << endl;
    int servFd = socket(AF_INET, SOCK_STREAM, 0);
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
    endGame = false;

    while(!endGame){
        cout << "Jestem w petli" << endl;
        // prepare placeholders for client address
        sockaddr_in clientAddr{0};
        socklen_t clientAddrSize = sizeof(clientAddr);

        // accept new connection
        auto clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
        if(clientFd == -1) error(1, errno, "accept failed");

        // add client to all clients set
        clientFds.insert(clientFd);

        // tell who has connected
        //printf("new connection from: %s:%hu (fd: %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

        thread(&Server::readMessage, this, clientFd).detach();
        cout << "utworzylem watek" << endl;
    }
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
    close(servFd);
    terminate();
    printf("Server closed\n");
}

void Server::sendToAll(int senderFd, char * buffer, int count){
    int res;
    decltype(clientFds) bad;
    for(int clientFd : clientFds){
        if(clientFd == senderFd){
            buffer[2] = 'T'; //powinien dostać punkt
        } else {
            buffer[2] = 'N'; //nie powinien dostać punktu
        }
        cout << "Sending..." << endl;
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

void Server::readMessage(int clientFd){
    while(!endGame) {
        // read a message
        cout << "IM THERE" << endl;
        char buffer[1];
        char bufferToSend[3];
        int count = read(clientFd, buffer, 1);
        bool flag = false;
        if (count < 1) {
            printf("removing %d\n", clientFd);
            clientFds.erase(clientFd);
            close(clientFd);
            continue;
        } else {
            unsigned int i = 0;
            if(buffer[0] == '0') { //Koniec gry
                endGame = true;
                bufferToSend[0] = buffer[0];
                bufferToSend[1] = '0';
                sendToAll(clientFd, bufferToSend, 3);
                flag = true;
            } else if(buffer[0] == '1') { //Prośba o dołączenie do gry
                cout << "prośba o dołączenie do gry" << endl;
                bufferToSend[0] = '6';
                bufferToSend[1] = '0';
                sendToAll(clientFd, bufferToSend, 3);
                flag = true;
            }
            while(i < word.size()){
                if (word[i] == buffer[0]){
                   bufferToSend[0] = buffer[0];
                   bufferToSend[1] = i; //i jako char więc trzeba potem konwertować na inta jako index litery w haśle
                   cout << "punkt w miejscu: " << i << endl;
                   sendToAll(clientFd, bufferToSend, 3);
                   flag = true;
                }
                i++;
            }
        }
        if(!flag){
            bufferToSend[2] = '7'; //nie było wystąpienia litery - punkt karny
            int res = write(clientFd, bufferToSend, 3);
        }
    }
}
