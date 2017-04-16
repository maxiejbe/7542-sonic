#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
//#include <Ws2tcpip.h>

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

DWORD WINAPI SocketHandler(void*);

static int connFd;

int main(int argc, char* argv[])
{
	int portNumber = 65535;
	int listenFd;

	struct sockaddr_in serverAddress, clientAddress;

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

	//create socket
	listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listenFd < 0)
	{
		cout << "Cannot open socket" << endl;
		cout << WSAGetLastError() << endl;
		return 0;
	}

	//Take a look at: http://stackoverflow.com/questions/3492647/what-are-the-alternative-for-win32-to-alarm-bzero-bcopy-when-porting-c-code
	bzero((char*)&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNumber);

	//bind socket
	if (bind(listenFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		cerr << "Cannot bind" << endl;
		return 0;
	}

	if (listen(listenFd, 5) < 0) {
		fprintf(stderr, "Error listening %d\n", WSAGetLastError());
		return 0;
	}

	//Now lets to the server stuff
	int addressSize = sizeof(clientAddress);
	
	while (true) {
		printf("waiting for a connection\n");
		
		connFd = accept(listenFd, (struct sockaddr *)&clientAddress, &addressSize);
		if (connFd != INVALID_SOCKET) {
			cout << "Recieved connection" << endl;
			//printf("Received connection from %s", clientAddress.sin_addr));
			//CreateThread(0, 0, &SocketHandler, (void*)csock, 0, 0);
		}
		else {
			fprintf(stderr, "Error accepting %d\n", WSAGetLastError());	
		}
	}
}

/*DWORD WINAPI SocketHandler(void* lp){
	int *csock = (int*)lp;

	char buffer[1024];
	int buffer_len = 1024;
	int bytecount;

	memset(buffer, 0, buffer_len);
	if((bytecount = recv(*csock, buffer, buffer_len, 0))==SOCKET_ERROR){
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		goto FINISH;
	}
	printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);
	strcat(buffer, " SERVER ECHO");

	if((bytecount = send(*csock, buffer, strlen(buffer), 0))==SOCKET_ERROR){
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		goto FINISH;
	}

	printf("Sent bytes %d\n", bytecount);

	FINISH:
	free(csock);
	
	return 0;
}*/
