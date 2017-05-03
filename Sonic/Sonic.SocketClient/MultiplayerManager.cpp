#include "MultiplayerManager.h"



MultiplayerManager::MultiplayerManager(MockPlayer * currentPlayer)
{
	if (!currentPlayer) {
		//LOG: no player 
		return;
	}
	
	this->currentPlayer = currentPlayer;
	//initialize rivals
	this->rivals = new map<int, MockPlayer*>();
	this->socketClient = new SocketClient("127.0.0.1", 5000);
	if (!this->socketClient->isInitialized()) {
		//TODO: Loguear que no se pudo inicializar el socket
		return;
	}

	if (this->socketClient->isConnected()) {
		//TODO: reintentar conexion
		startConnectionHandlers();
	}
	
}

void MultiplayerManager::startConnectionHandlers()
{
	//Receive Handler
	CreateThread(0, 0, runRecvSocketHandler, (void*)this, 0, &this->recvThreadId);
	CreateThread(0, 0, runSendSocketHandler, (void*)this, 0, &this->sendThreadId);
}

DWORD WINAPI MultiplayerManager::runRecvSocketHandler(void * args)
{
	MultiplayerManager * mManager = (MultiplayerManager*)args;
	return mManager->recvSocketHandler();
}

DWORD MultiplayerManager::recvSocketHandler()
{
	char receivedMsg[1024];
	int receivedMsgLen = 1024;
	while (this->online() && !this->connectionTerminated()) {
		if (this->socketClient->receiveMessage(receivedMsg, receivedMsgLen)) 
		{
			this->handleMessage(receivedMsg);
		}
		else {
			//TODO: LOG FAILED RECEIVED MESSAGE
		}
	}

	return 0;
}

void MultiplayerManager::handleMessage(char * receivedMessage)
{
	string strMessage(receivedMessage);
	Message* message = new Message(strMessage);
	if (message->getConnectionStatus() == assign) 
	{
		playerAssignment(message);
	}
	else {
		updateRival(message);
	}
}

void MultiplayerManager::playerAssignment(Message * msg)
{
	if (!currentPlayer) {
		//LOG: Player deleted
		return;
	}
	//asign number to player
	this->currentPlayer->setNumber(msg->getNumber());
}

void MultiplayerManager::updateRival(Message * msg)
{
	if (msg->getNumber() == this->currentPlayer->getNumber()) {
		return;
	}

	MockPlayer * rival;
	try {
		rival = this->rivals->at(msg->getNumber());
		if (rival == NULL) {
			//LOG: rival deleted
			return;
		}

		if (msg->getConnectionStatus() == disconnected) {
			delete rival;
			this->rivals->erase(msg->getNumber());
			return;
		}

		//update positions
		rival->setPosX(msg->getXPosition());
		rival->setPosY(msg->getYPosition());
	}
	catch (out_of_range e) {
		//player not exists with that id
		rival = new MockPlayer(msg->getNumber(), msg->getXPosition(), msg->getYPosition(), idle);
		this->rivals->insert(pair<int,MockPlayer*>(rival->getNumber(),rival));
	}
}

DWORD WINAPI MultiplayerManager::runSendSocketHandler(void * args)
{
	MultiplayerManager * mManager = (MultiplayerManager*)args;
	return mManager->sendSocketHandler();
}

DWORD MultiplayerManager::sendSocketHandler()
{
	//send new message
	while (this->online() && !this->connectionTerminated() && this->currentPlayer != NULL) {
		//wait till user gets number
		if (this->currentPlayer->getNumber() > 0) {
			Message msg = Message(this->currentPlayer->getNumber());
			msg.setPosition(this->currentPlayer->getPosX(), this->currentPlayer->getPosY());
			string strMsg= "";
			msg.toString(&strMsg);
			char* msgToSend = StringUtils::convert(strMsg);
			if (!this->socketClient->sendMessage(msgToSend)) {
				//LOG: Failed send
			}

			delete msgToSend;
		}
		//wait 3 seconds;
		Sleep(3000);
	}

	return 0;
}


MultiplayerManager::~MultiplayerManager()
{
	map<int, MockPlayer*>::iterator it = this->rivals->begin();
	while (it != this->rivals->end()) {
		//delete all players
		delete it->second;
	}

	this->rivals->clear();
	delete this->rivals;
	delete this->socketClient;
}

vector<MockPlayer*> MultiplayerManager::getRivals()
{
	vector<MockPlayer*> rivalsList;
	rivalsList.clear();
	map<int, MockPlayer*>::iterator it = this->rivals->begin();
	while (it != this->rivals->end()) {
		//delete all players
		rivalsList.push_back(it->second);
	}

	return rivalsList;
}

bool MultiplayerManager::online()
{
	return this->socketClient->isConnected();
}

bool MultiplayerManager::connectionTerminated()
{
	return this->socketClient->isTerminated();
}
