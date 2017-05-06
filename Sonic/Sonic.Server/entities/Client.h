#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <iostream>
#include "Server.h"
#include "protocol/Message.h"
#include "entities/Player.h"
#include "../utils/SocketUtils.h"
#include "../controllers/PlayerController.h"
#include <limits>

using namespace std;

class Server;

class Client {
public:
	Client(Server*, int);
	~Client();
	int getClientNumber();

	bool acceptSocket();
	void closeSocket();
	
	bool sendClientNumber();
	bool sendFileContent();

	Player* getPlayer();

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
	Player* player;
	
	SOCKET socket;
	Server* server;
	struct sockaddr_in address;
	DWORD threadId;
};

#endif
