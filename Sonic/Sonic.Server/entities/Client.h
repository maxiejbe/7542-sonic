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
#include "Timer.h"
#include <limits>
#include <mutex>

using namespace std;

class Server;

class Client {
public:
	Client(Server*);
	~Client();
	int getClientNumber();

	bool acceptSocket();
	bool welcome(int, Player*);
	void closeSocket();
	
	void terminateThreads();

	bool sendMessage(const char*, bool);
	bool sendHeartBeat();
	bool sendClientNumber();
	bool sendLevels();
	bool sendLevelStart();
	bool sendLevelFinish();
	bool sendGameFinish();
	bool sendStatus();
	bool sendEntitiesStatus();
	
	bool refreshPlayer();
	bool notifyLevelFinished();
	bool notifyStartNewLevel();
	bool notifyGameFinished();
	
	void setClientNumber(int);

	Player* getPlayer();
	void setPlayer(Player*);
	Message* getLastMessage();

	SOCKET getSocket();
private:
	int clientNumber;
	Player* player;
	Message * lastReceivedMessage;
	bool gameStartSent;

	SOCKET socket;
	Server* server;
	struct sockaddr_in address;
	DWORD threadId;
	HANDLE recvThreadHandle;

	Timer timer;
	

	//recieve handler
	static DWORD WINAPI runReceiveSocketHandler(void* args);
	DWORD receiveSocketHandler();
	bool parseReceivedMessage();
	void handleReceivedMessage(char* recievedMessage);
	void startRefereshing();
	void startSending();
	void startSendingEntities();
	void startHeartBeating();
	bool continueReceiving;

	//refresh handler
	DWORD refreshThreadId;
	HANDLE refreshThreadHandle;
	static DWORD WINAPI refreshSocketHandler(void* args);
	DWORD refreshSocketHandler();
	bool continueRefreshing;
	
	//send handler
	DWORD sendThreadId;
	HANDLE sendThreadHandle;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
	bool continueSending;
	
	mutex playerMutex;
	mutex sendMutex;

	//send handler
	DWORD sendEntitiesThreadId;
	HANDLE sendEntitiesThreadHandle;
	static DWORD WINAPI runSendEntitiesSocketHandler(void* args);
	DWORD sendEntitiesSocketHandler();
	bool continueSendingEntites;

	//Connection check
	HANDLE heartBeatThreadHandle;
	DWORD heartBeatThreadId;
	static DWORD WINAPI runHeartBeatSocketHandler(void* args);
	DWORD heartBeatSocketHandler();
	bool continueHeartBeating;
};

#endif
