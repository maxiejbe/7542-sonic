#pragma once
#include "SocketClient.h"
#include "entities/Player.h"
#include "protocol/Message.h"
#include "../views/PlayerView.h"
#include "protocol/ServerMessage.h"

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
	vector<PlayerView*> getPlayerViews();

	int getPlayerNumber();
	string getFileContent();
private:
	NetworkManager();
	static NetworkManager * instance;
	SocketClient * client;
	vector<PlayerView*> playerViews;

	int playerNumber;
	string fileContent;

	void updatePlayerViews(vector<Player*> playerStatus);
	void freePlayerViews();
	/*HANDLERS*/
	void startConnectionHandlers();

	//receive handler
	DWORD recvThreadId;
	static DWORD WINAPI runRecvSocketHandler(void* args);
	DWORD recvSocketHandler();
	void handleMessage(char*);
	void playerAssignment(vector<Player*> playerStatus);
	void updateRival(Message * message);

	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
};

