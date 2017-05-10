#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <iostream>
#include "Server.h"
#include "protocol/ServerMessage.h"
#include "protocol/Message.h"
#include "entities/Player.h"
#include "../utils/SocketUtils.h"
#include "../controllers/PlayerController.h"
#include <limits>
#include <mutex>

using namespace std;

class Server;

class Client {
public:
	Client(Server*, Player*);
	~Client();
	int getClientNumber();

	bool acceptSocket();
	bool welcome(int, Player*);
	void closeSocket();
	
	bool sendClientNumber();
	bool sendFileContent();
	bool sendPlayersStatus();

	Player* getPlayer();
	Message* getLastMessage();

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
	Message * lastReceivedMessage;

	SOCKET socket;
	Server* server;
	struct sockaddr_in address;
	DWORD threadId;

	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();

	mutex clientMutex;
};

#endif
