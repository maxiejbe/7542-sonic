#pragma once
#include "entities/Player.h"
#include "SocketClient.h"
#include "protocol\Message.h"
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

	bool startClient(char * host, int port);
	bool online();
	void sendMessage(Message * message);

	int getPlayerNumber();
	string getFileContent();
private:
	NetworkManager();
	static NetworkManager * instance;
	SocketClient * client;

	int playerNumber;
	string fileContent;

	/*HANDLERS*/
	void startConnectionHandlers();

	//receive handler
	DWORD recvThreadId;
	static DWORD WINAPI runRecvSocketHandler(void* args);
	DWORD recvSocketHandler();
	void handleMessage(char*);
	void playerAssignment(Message * message);
	void updateRival(Message * message);

	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
};

