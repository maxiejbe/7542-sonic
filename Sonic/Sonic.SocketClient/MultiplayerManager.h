#pragma once
#include "SocketClient.h"
#include "entities\Message.h"
#include "MockPlayer.h"
#include "utils\StringUtils.h"
#include <map>


using namespace std;

class MultiplayerManager
{
public:
	MultiplayerManager(MockPlayer * currentPlayer);
	~MultiplayerManager();
	vector<MockPlayer*> getRivals();
	bool online();
	bool connectionTerminated();
private:
	SocketClient* socketClient;
	MockPlayer * currentPlayer;
	map<int, MockPlayer*> * rivals;

	/*HANDLERS*/
	void startConnectionHandlers();
	//receive handler
	DWORD recvThreadId;
	static DWORD WINAPI runRecvSocketHandler(void* args);
	DWORD recvSocketHandler();
	void handleMessage(char*);
	void playerAssignment(Message * msg);
	void updateRival(Message * msg);
	//send handler
	DWORD sendThreadId;
	static DWORD WINAPI runSendSocketHandler(void* args);
	DWORD sendSocketHandler();
};

