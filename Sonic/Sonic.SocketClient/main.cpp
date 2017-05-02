#include "SocketClient.h"
#include <time.h>   

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
using namespace std;

int main(int argc, char* argv[])
{
	SocketClient* sc = new SocketClient("127.0.0.1", 5000);
	int reconectionAttemps = 10;
	int i = 1;

	if (!sc->isInitialized()) {
		delete sc;
		return 0;
	}
	if (sc->isConnected()) {
		/*printf("listening for messages\n");
		printf("time: %f\n", double(clock() - begin_time) / CLOCKS_PER_SEC);
		Sleep(5000);
		printf("time: %f\n", double(clock() - begin_time) / CLOCKS_PER_SEC);*/
		char message[1024];
		int msgLength = 1024;
		sc->receiveMessage(message, msgLength);
		printf("received msg: %s", message);
	}
	else {
		printf("cant connect to Socket\n");
	}

	char finish;
	cin >> finish;
	delete sc;
}
