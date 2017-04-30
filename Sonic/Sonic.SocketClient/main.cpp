#include "SocketClient.h"
#include "SonicConnectionHandler.h"
#include <time.h>   

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
using namespace std;

int main(int argc, char* argv[])
{
	SonicConnectionHandler * scHandler = new SonicConnectionHandler();
	SocketClient* sc = new SocketClient("127.0.0.1", 5000, scHandler);
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

	const clock_t begin_time = clock();
	if (socketConnected) {
		/*printf("listening for messages\n");
		printf("time: %f\n", double(clock() - begin_time) / CLOCKS_PER_SEC);
		Sleep(5000);
		printf("time: %f\n", double(clock() - begin_time) / CLOCKS_PER_SEC);*/
		while ((double(clock() - begin_time) / CLOCKS_PER_SEC) < 120) {
			//wait for messages
		}
	}
	else {
		printf("cant connect to Socket\n");
	}

	printf("stop listening for messages\n");
	delete sc;
	delete scHandler;
}
