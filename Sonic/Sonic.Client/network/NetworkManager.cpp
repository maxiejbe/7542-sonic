#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	this->client = NULL;
}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::close()
{
	if (this->client) { delete client; }
}

bool NetworkManager::startClient(char * host, int port)
{
	if (this->client) {
		//delete previous client
		delete this->client;
	}

	this->client = new SocketClient(host, port);

	if (!this->client->isConnected()) {
		LOG(logERROR) << "Network Manager: Error al inicializar el cliente";
		delete this->client;
		return false;
	}

	//TODO: inicializar receiver
	LOG(logINFO) << "Network Manager: Se inicializo el cliente correctamente - host: " << host << " puerto: " << port;
	
	//start handlers
	this->startConnectionHandlers();
	return true;
}

bool NetworkManager::online()
{
	return (this->client && this->client->isConnected());
}

void NetworkManager::startConnectionHandlers()
{
	//Receive Handler
	//TODO: kill theads
	CreateThread(0, 0, runRecvSocketHandler, (void*)this, 0, &this->recvThreadId);
	//CreateThread(0, 0, runSendSocketHandler, (void*)this, 0, &this->sendThreadId);
}

DWORD WINAPI NetworkManager::runRecvSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->recvSocketHandler();
}

DWORD NetworkManager::recvSocketHandler()
{
	char receivedMsg[1024];
	int receivedMsgLen = 1024;
	while (this->online()) 
	{
		if (!this->client->receiveMessage(receivedMsg, receivedMsgLen))
		{
			LOG(logERROR) << "Network Manager: Fallo la recepción de mensajes";
		}
		this->handleMessage(receivedMsg);
	}
	return 0;
}

void NetworkManager::handleMessage(char * receivedMessage)
{
	string strMessage(receivedMessage);
	cout << strMessage << endl;

	//Message* message = new Message(/*strMessage*/);
	//if (message->getConnectionStatus() == assign)
	//{
	//	playerAssignment(message);
	//}
	//else {
	//	updateRival(message);
	//}
	//delete message;
}

void NetworkManager::playerAssignment(Message * message)
{
	//if (this->playerNumber < 0) {
	//	LOG(logERROR) << "Network Manager: El jugador fue borrado no se puede asignar un id";
	//	return;
	//}
	
	//Assign number to player
	//this->playerNumber = message->getPlayerNumber();
	//LOG(logINFO) << "Network Manager: Se asigno id #" << msg->getPlayerNumber() << " a jugador";
}

void NetworkManager::updateRival(Message * message)
{
	//muestro mensaje
	if (message->getPlayerNumber() == this->playerNumber) return;
	LOG(logINFO) << "Network Manager: Recibida data de rival #" << message->getPlayerNumber();
}

DWORD WINAPI NetworkManager::runSendSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->sendSocketHandler();
}

DWORD NetworkManager::sendSocketHandler()
{
	//send new message
	while (this->online() && this->playerNumber < 0) {
		//wait till user gets number
		if (this->playerNumber > 0) {
			Message * msg = new Message(/*this->player->getNumber()*/);
			this->sendMessage(msg);
			delete msg;
		}
		//wait 3 seconds;
		Sleep(3000);
	}

	return 0;
}

void NetworkManager::sendMessage(Message* message)
{
	if (!this->online()) {
		return;
	}

	//Serialize message before sending to server
	vector<Message*> messages;
	messages.push_back(message);

	/*string stringMessage;
	BoostSerializable::serialize_save(messages, stringMessage);
	
	vector<Message*> messages2;
	BoostSerializable::serialize_load(messages2, stringMessage.c_str(), stringMessage.size());

	if (this->client->sendMessage(stringMessage)) {
		LOG(logINFO) << "Network Manager: Se envio mensaje -> " << stringMessage;
	}
	else {
		LOG(logERROR) << "Network Manager: Falló envio de mensaje -> " << stringMessage;
	}*/
}

int NetworkManager::getPlayerNumber()
{
	return this->playerNumber;
}

string NetworkManager::getFileContent()
{
	return this->fileContent;
}
