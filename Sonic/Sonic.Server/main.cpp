#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

DWORD WINAPI SocketHandler(void*);

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

	int addressSize = sizeof(clientAddress);
	
	while (true) {
		printf("waiting for a connection\n");
		
		SOCKET sd = accept(listenFd, (struct sockaddr *)&clientAddress, &addressSize);
		if (sd == INVALID_SOCKET) {
			fprintf(stderr, "Error accepting %d\n", WSAGetLastError());
			return 0;
		}

		char stringIp[sizeof(clientAddress)];
		inet_ntop(AF_INET, &(clientAddress.sin_addr), stringIp, INET_ADDRSTRLEN);
		cout << "Recieved connection from " << stringIp << endl;

		DWORD threadId;
		CreateThread(0, 0, &SocketHandler, (void*)sd, 0, &threadId);
	}
}

DWORD WINAPI SocketHandler(void* cs){
	SOCKET clientSocket = (SOCKET) cs;

	char buffer[1024];
	int buffer_len = 1024;
	int bytecount;

	do {
		memset(buffer, 0, buffer_len);
		if ((bytecount = recv(clientSocket, buffer, buffer_len, 0)) == SOCKET_ERROR) {
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			return 0;
		}
		printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);

		if ((bytecount = send(clientSocket, buffer, strlen(buffer), 0)) == SOCKET_ERROR) {
			fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
			return 0;
		}

		printf("Sent bytes %d\n", bytecount);

	} while (bytecount > 0);

	cout << "Connection closed." << endl;
	return 0;
}
