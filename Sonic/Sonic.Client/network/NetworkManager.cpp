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

bool NetworkManager::startClient(char * host, int port, Player * player)
{
	if (this->client) {
		//delete previous client
		delete this->client;
	}

	this->client = new SocketClient(host, port);

	if (!this->client->isConnected()) {
		//printf("ERROR: no se pudo inicializar el cliente");
		LOG(logERROR) << "Network Manager: Error al inicializar el cliente";
		delete this->client;
		return false;
	}

	//TODO: inicializar receiver
	//printf("Se inicializo el client en host: %s, puerto: %d", host, port);
	LOG(logINFO) << "Network Manager: Se inicializo el cliente correctamente - host: " << host << " puerto: " << port;
	this->player = player;
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
	CreateThread(0, 0, runSendSocketHandler, (void*)this, 0, &this->sendThreadId);
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
	while (this->online()) {
		if (this->client->receiveMessage(receivedMsg, receivedMsgLen))
		{
			this->handleMessage(receivedMsg);
		}
		else {
			//TODO: LOG FAILED RECEIVED MESSAGE
			LOG(logERROR) << "Network Manager: Fallo la recepción de mensajes";
		}
	}

	return 0;
}

void NetworkManager::handleMessage(char * receivedMessage)
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

	delete message;
}

void NetworkManager::playerAssignment(Message * msg)
{
	if (!this->player) {
		LOG(logERROR) << "Network Manager: El jugador fue borrado no se puede asignar un id";
		return;
	}
	//asign number to player
	//TODO: usar mutex
	this->player->setNumber(msg->getNumber());
	LOG(logINFO) << "Network Manager: Se asigno id #" << msg->getNumber() << " a jugador";
}

void NetworkManager::updateRival(Message * msg)
{
	//muestro mensaje
	if (msg->getNumber() == this->player->getNumber()) return;
	LOG(logINFO) << "Network Manager: Recibida data de rival #" << msg->getNumber() << ": x->" << msg->getPosition().x << " y->" << msg->getPosition().y;
}

DWORD WINAPI NetworkManager::runSendSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->sendSocketHandler();
}

DWORD NetworkManager::sendSocketHandler()
{
	//send new message
	while (this->online() && this->player != NULL) {
		//wait till user gets number
		if (this->player->getNumber() > 0) {
			Message * msg = new Message(this->player->getNumber());
			msg->setPosition(this->player->getPosition());
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

	string strMsg = "";
	message->toString(&strMsg);
	char* msgToSend = StringUtils::convert(strMsg);

	if (this->client->sendMessage(msgToSend)) {
		LOG(logINFO) << "Network Manager: Se envio mensaje -> " << strMsg;
	}
	else {
		LOG(logERROR) << "Network Manager: Falló envio de mensaje -> " << strMsg;
	}
}