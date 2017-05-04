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
		//printf("ERROR: no se pudo inicializar el cliente");
		LOG(logERROR) << "Error al inicializar el cliente";
		delete this->client;
		return false;
	}

	//TODO: inicializar receiver
	//printf("Se inicializo el client en host: %s, puerto: %d", host, port);
	LOG(logINFO) << "Se inicializo el cliente correctamente";
	return true;
}

bool NetworkManager::online()
{
	return (this->client && this->client->isConnected());
}

bool NetworkManager::sendMessage(Message * message)
{
	if (!this->online()) {
		return false;
	}

	string strMsg = "";
	message->toString(&strMsg);
	char* msgToSend = StringUtils::convert(strMsg);
	delete message;
	if (!this->client->sendMessage(msgToSend)) {
		//LOG: Failed send
		return false;
	}

	return true;
}

