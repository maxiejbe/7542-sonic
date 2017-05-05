#pragma once
#include "entities/Player.h"
#include "SocketClient.h"
#include "entities/Message.h"
#include "Logger.h"

class NetworkManager
{
public:
	~NetworkManager();
	static NetworkManager& getInstance() {
		static NetworkManager instance;
		return instance;
	}
	void close();

	bool startClient(char * host, int port, Player * player);
	bool online();
	void sendMessage(Message * message);
private:
	NetworkManager();
	static NetworkManager * instance;
	Player * player;
	SocketClient * client;

	/*HANDLERS*/
	void startConnectionHandlers();

	//receive handler
	DWORD recvThreadId;
	static DWORD WINAPI runRecvSocketHandler(void* args);
	DWORD recvSocketHandler();
	void handleMessage(char*);
	void playerAssignment(Message * msg);
	void updateRival(Message * msg);

	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
};

