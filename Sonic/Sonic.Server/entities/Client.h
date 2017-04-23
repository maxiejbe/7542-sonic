#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <iostream>

using namespace std;

class Server;
class Client {
public:
	Client(Server*, SOCKET, sockaddr_in);

private:
	SOCKET socket;
	Server* server;
	struct sockaddr_in address;
	DWORD threadId;
};

#endif
