#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>
#include <vector>
#include <Logger.h>

#include "Client.h"
#include "entities/Player.h"
#include "protocol/ServerMessage.h"

#include "entities/Window.h"
#include "entities/Configuration.h"
#include "entities/Scenario.h"
#include "common/ServerConfiguration.h"

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

using namespace std;

class Client;
class Server {

public:
	~Server();
	Server(ServerConfiguration* serverConfig, string fileContent, Window* window, Configuration* config, Scenario* scenario);
	bool validate();
	void waitForClientConnections();
	void sendBroadcast(char* message);
	void removeClientConnection(int clientNumber);

	SOCKET getSocket();
	string getFileContent();

	Window* getWindow();
	Configuration* getConfiguration();
	Scenario* getScenario();

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

	void acceptClientConnection();
	ServerMessage* makePlayersStatusUpdateMessage();
	
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

	vector<Client*> clients;
};

#endif
