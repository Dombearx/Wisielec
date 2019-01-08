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

using namespace std;

// server socket
int servFd;

// client sockets
unordered_set<int> clientFds;


string word = "PASSWORD";

// handles SIGINT
void ctrl_c(int);

// sends data to clientFds excluding fd
void sendToAllBut(int fd, char * buffer, int count);

// converts cstring to port
uint16_t readPort(const char * txt);

// sets SO_REUSEADDR
void setReuseAddr(int sock);

void sendToAll(int fd, char * buffer, int count);

void readMessage(int fd);




int main(int argc, char ** argv){
	// get and validate port number
    string p = "27001";
    auto port = readPort(p.c_str());
	
	// create socket
	servFd = socket(AF_INET, SOCK_STREAM, 0);
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

	while(true){
		// prepare placeholders for client address
		sockaddr_in clientAddr{0};
		socklen_t clientAddrSize = sizeof(clientAddr);

		// accept new connection
		auto clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
		if(clientFd == -1) error(1, errno, "accept failed");

		// add client to all clients set
		clientFds.insert(clientFd);

		// tell who has connected
		printf("new connection from: %s:%hu (fd: %d)\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

/****************************/
		thread(readMessage, clientFd).detach();

		
	}
	
/****************************/
}

uint16_t readPort(const char * txt){
	char * ptr;
	auto port = strtol(txt, &ptr, 10);
	if(*ptr!=0 || port<1 || (port>((1<<16)-1))) error(1,0,"illegal argument %s", txt);
	return port;
}

void setReuseAddr(int sock){
	const int one = 1;
	int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	if(res) error(1,errno, "setsockopt failed");
}

void closeServer(int fd){
	for(int clientFd : clientFds)
		close(clientFd);
	close(servFd);
	printf("Closing server\n");
	exit(0);
}

void sendToAll(int senderFd, char * buffer, int count){
	int res;
	decltype(clientFds) bad;
	for(int clientFd : clientFds){
		if(clientFd == senderFd){
            buffer[2] = 'T'; //powinien dostać punkt
		} else {
            buffer[2] = 'N'; //nie powinien dostać punktu
		}
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

void readMessage(int clientFd){
    while(true) {
        // read a message
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
            while(i < word.size()){
                if (word[i] == buffer[0]);
                bufferToSend[0] = buffer[0];
                bufferToSend[1] = i; //i jako char więc trzeba potem konwertować na inta jako index litery w haśle
                sendToAll(clientFd, bufferToSend, 3);
                flag = true;
            }
        }
        if(!flag){
            bufferToSend[2] = 'K'; //nie było wystąpienia litery - punkt karny
            int res = write(clientFd, bufferToSend, 3);
        }
    }
}
