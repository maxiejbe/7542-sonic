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

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

using namespace std;

class Client;
class Server {

public:
	~Server();
	Server(int portNumber, int maxAllowedClients, string fileContent);
	bool validate();
	void waitForClientConnections();
	void sendBroadcast(char* message);
	void removeClientConnection(int clientNumber);

	SOCKET getSocket();
	string getFileContent();

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
	
	bool isValid;
	SOCKET _socket;
	struct sockaddr_in address;
	int portNumber;

	int maxAllowedClients;
	int connectedClients;
	string fileContent;

	vector<Client*> clients;
};

#endif
