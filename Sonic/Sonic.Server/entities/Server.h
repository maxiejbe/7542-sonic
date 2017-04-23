#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>
#include <vector>

#include "Client.h"

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

using namespace std;

class Server {

public:
	Server(int portNumber, int maxAllowedClients);
	bool validate();
	bool waitForClientConnections();

private:
	/*
	Initialize socket support WINDOWS ONLY!
	*/
	bool initializeWindowsSupport();
	bool initSocket();
	bool configureAddress();
	bool bindSocket();
	bool startListening();
	
	bool isValid;
	SOCKET _socket;
	struct sockaddr_in address;
	int portNumber;

	int maxAllowedClients;
	int connectedClients;

	vector<Client> clients;
};

#endif
