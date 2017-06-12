#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>
#include <vector>
#include <Logger.h>

#include <iostream>
#include <unordered_map>

#include "Client.h"
#include "entities/Player.h"
#include "entities/Camera.h"
#include "entities\enemies\Enemy.h"
#include "protocol/ServerMessage.h"

#include "entities/Window.h"
#include "entities/Configuration.h"
#include "entities/Scenario.h"
#include "entities/GameConfig.h"
#include "entities/ServerConfiguration.h"
#include "../controllers/CameraController.h"
#include "../controllers/EnemyController.h"

#include <mutex>

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

using namespace std;

class Client;
class Server {

public:
	~Server();
	Server(ServerConfiguration* serverConfig, string fileContent, Window* window, Configuration* config, GameConfig* gameConfig);
	bool validate();
	void waitForClientConnections();
	void sendBroadcast();
	void removeClientConnection(int clientNumber);
	void terminateThreads();
	void addConnectedClients();

	void resetLevel();
	vector<Level>* getLevels();

	SOCKET getSocket();
	string getFileContent();

	Window* getWindow();
	Configuration* getConfiguration();
	Scenario* getScenario();

	Camera* getCamera();

	ServerMessage* getPlayersStatusMessage();
	string getEnemiesStatusMessage();
private:
	/*
	Initialize socket support WINDOWS ONLY!
	*/
	bool initializeWindowsSupport();
	bool initSocket();
	bool configureAddress();
	bool bindSocket();
	bool startListening();

	int getAvailableIndex();
	int getDisconnectedIndex();

	/*Client getClient(int index);
	void setClient(Client*);*/

	void acceptClientConnection();

	vector<Player*> clientsPlayers();

	bool isValid;
	SOCKET _socket;
	struct sockaddr_in address;
	int portNumber;

	int connectedClients;
	string fileContent;

	bool gameStarted;
	int currentLevel;

	ServerConfiguration* serverConfig;
	Window* window;
	Configuration* config;
	
	Scenario* scenario;
	Camera* camera;

	GameConfig* gameConfig;

	unordered_map<int, Client*> clients;
	vector<Client*> disconnectedClients;
	//mutex clientMutex;

	vector<Enemy*> enemies;
	vector<Enemy*> visibleEnemies;
	mutex visibleEnemiesMutex;

	//update enemies handler
	DWORD updateEnemiesThreadId;
	HANDLE updateEnemiesThreadHandle;
	static DWORD WINAPI runUpdateEnemiesHandler(void* args);
	DWORD updateEnemiesHandler();
	bool continueUpdatingEnemies;

	//send enemies handler
	DWORD sendEnemiesThreadId;
	HANDLE sendEnemiesThreadHandle;
	static DWORD WINAPI runSendEnemiesHandler(void* args);
	DWORD sendEnemiesHandler();
	bool continueSendingEnemies;

};

#endif
