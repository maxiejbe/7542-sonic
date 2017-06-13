#pragma once
#include "SocketClient.h"
#include "entities/Player.h"
#include "protocol/Message.h"
#include "../views/PlayerView.h"
#include "../views/EntityView.h"
#include "../views/common/EntityViewResolver.h"
#include "protocol/ServerMessage.h"
#include "entities/ServerConfiguration.h"

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
	bool reconnect();
	void disconnect();
	void sendMessage(Message * message);
	void sendMessage(Message * message, bool disconnect);
	Camera * getCamera();
	unordered_map<int, PlayerView*> getPlayerViews();
	unordered_map<int, EntityView*> getEntityViews();

	PlayerView* getOwnPlayerView();
	bool canStartGame();

	int getPlayerNumber();

	vector<Level>* getLevels();

	bool connectToServer(ServerConfiguration serverConfig);

private:
	NetworkManager();
	static NetworkManager * instance;
	SocketClient * client;
	Camera * camera;
	unordered_map<int, PlayerView*> playerViews;
	unordered_map<int, EntityView*> entityViews;
	bool startGame;

	int playerNumber;
	vector<Level> * gameLevels;

	void updatePlayerViews(vector<Player*> playerStatus);
	void updateEntityViews(vector<Entity*> entities);
	void updateCamera(Camera* camera);
	
	/*HANDLERS*/
	void startConnectionHandlers();
	void stopConnectionHandlers();

	//receive handler
	HANDLE recvThreadHandle;
	DWORD recvThreadId;
	static DWORD WINAPI runRecvSocketHandler(void* args);
	DWORD recvSocketHandler();
	void handleMessage(char*);
	bool continueReceiving;

	//Connection check
	HANDLE heartBeatThreadHandle;
	DWORD heartBeatThreadId;
	static DWORD WINAPI runHeartBeatSocketHandler(void* args);
	DWORD heartBeatSocketHandler();
	bool continueHeartBeating;

	time_t lastHeartBeat;
};

