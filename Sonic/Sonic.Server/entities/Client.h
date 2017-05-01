#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <iostream>
#include "Server.h"
#include "entities/Message.h"
#include "../utils/SocketUtils.h"

using namespace std;

class Server;

class Client {
public:
	Client(Server*, int);
	int getClientNumber();

	bool acceptSocket();
	void closeSocket();
	
	SOCKET getSocket();
private:
	bool parseRecievedMessage();
	void handleRecievedMessage(char* recievedMessage);

	static DWORD WINAPI runSocketHandler(void* args)
	{
		Client* pclient = (Client*) args;
		return pclient->socketHandler();
	}
	DWORD socketHandler();

	int clientNumber;
	SOCKET socket;
	Server* server;
	struct sockaddr_in address;
	DWORD threadId;
};

#endif
