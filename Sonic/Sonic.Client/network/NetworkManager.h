#pragma once
#include "SocketClient.h"
#include "entities/Player.h"
#include "protocol/Message.h"
#include "../views/PlayerView.h"
#include "protocol/ServerMessage.h"

#include <iostream>
#include <map>
#include <unordered_map>

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
	unordered_map<int, PlayerView*> getPlayerViews();

	PlayerView* getOwnPlayerView();

	int getPlayerNumber();
	string getFileContent();
private:
	NetworkManager();
	static NetworkManager * instance;
	SocketClient * client;
	unordered_map<int, PlayerView*> playerViews;

	int playerNumber;
	string fileContent;

	void updatePlayerViews(vector<Player*> playerStatus);
	
	/*HANDLERS*/
	void startConnectionHandlers();

	//receive handler
	DWORD recvThreadId;
	static DWORD WINAPI runRecvSocketHandler(void* args);
	DWORD recvSocketHandler();
	void handleMessage(char*);
	
	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
};

