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
#include "protocol/ServerMessage.h"

#include "entities/Window.h"
#include "entities/Configuration.h"
#include "entities/Scenario.h"
#include "common/ServerConfiguration.h"
#include "../controllers/CameraController.h"

#include <mutex>

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

using namespace std;

class Client;
class Server {

public:
	~Server();
	Server(ServerConfiguration* serverConfig, string fileContent, Window* window, Configuration* config, Scenario* scenario, Camera * camera);
	bool validate();
	void waitForClientConnections();
	void sendBroadcast(char*);
	void removeClientConnection(int clientNumber);

	SOCKET getSocket();
	string getFileContent();

	Window* getWindow();
	Configuration* getConfiguration();
	Scenario* getScenario();

	void lock();
	void unlock();
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

	void acceptClientConnection();
	ServerMessage* getPlayersStatusMessage();

	vector<Player*> clientsPlayers();

	bool isValid;
	SOCKET _socket;
	struct sockaddr_in address;
	int portNumber;

	int connectedClients;
	string fileContent;

	ServerConfiguration* serverConfig;
	Window* window;
	Configuration* config;
	Scenario* scenario;

	unordered_map<int, Client*> clients;
	Camera* camera;

	mutex serverMutex;

	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
};

#endif
