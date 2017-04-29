#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <Ws2tcpip.h>
#include "SocketClient.h"

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

int main(int argc, char* argv[])
{
	/*bool shutdown = false;
	int bytecount = 0;
	char buffer[1024];
	int buffer_len = 1024;

	//Initialize socket support WINDOWS ONLY!
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 ||
	HIBYTE(wsaData.wVersion) != 2)) {
	fprintf(stderr, "Could not find useable sock dll %d\n", WSAGetLastError());
	return 0;
	}

	struct addrinfo *result = NULL,
	*ptr = NULL,
	hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	err = getaddrinfo("127.0.0.1", "5000", &hints, &result);
	if (err != 0) {
	printf("getaddrinfo failed: %d\n", err);
	WSACleanup();
	return 1;
	}

	SOCKET connectSocket = INVALID_SOCKET;

	connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (connectSocket == INVALID_SOCKET) {
	printf("Error at socket(): %ld\n", WSAGetLastError());
	freeaddrinfo(result);
	WSACleanup();
	return 1;
	}


	if (connect(connectSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
	cerr << "Cannot bind" << endl;
	closesocket(connectSocket);
	connectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);


	do {
	memset(buffer, 0, buffer_len);
	printf("Ingresa un texto:\n");
	cin >> buffer;

	if (strcmp(buffer, ":q") != 0) {
	bytecount = send(connectSocket, buffer, buffer_len, 0);
	if (bytecount == SOCKET_ERROR) {
	fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
	}

	bytecount = recv(connectSocket, buffer, buffer_len, 0);
	if (bytecount == SOCKET_ERROR) {
	fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
	}

	printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);
	}
	else {
	shutdown = true;
	}


	} while (!shutdown &&  bytecount > 0);*/

	SocketClient* sc = new SocketClient("127.0.0.1", 5000);
	bool socketConnected = sc->isConnected();
	int reconectionAttemps = 10;
	int i = 1;

	if (!sc->isInitialized()) {
		delete sc;
		return 0;
	}

	while (!socketConnected && i <= reconectionAttemps) {
		printf("Attempting reconection: %d\n", i);
		Sleep(5000);
		sc->reconnect();
		socketConnected = sc->isConnected();
		i++;
	}

	
	if (socketConnected) {
		printf("Socket connected\n");
		sc->sendMessage("sarlanga");
	}
	else {
		printf("cant connect to Socket\n");
	}
	
	delete sc;
}
