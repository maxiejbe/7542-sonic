#include "Server.h"

const char* MESSAGE_STARTING_SERVER = "Intentando arrancar servidor: ";
const char* MESSAGE_STARTING_SERVER_FAIL = "No se pudo arrancar el servidor.";
const char* MESSAGE_STARTING_SERVER_OK = "Servidor corriendo correctamente en: ";
const char* MESSAGE_SERVER_EXECUTION_END = "Se finalizó la ejecución del servidor. No se recibirán nuevos clientes.";
const char* MESSAGE_SERVER_CANNOT_FIND_DLL = "No se encontró una dll para sockets utilizable. ";
const char* MESSAGE_SERVER_CANNOT_OPEN_SOCKET = "No se pudo abrir el socket. ";
const char* MESSAGE_SERVER_CANNOT_BIND_SOCKET = "No se pudo bindear el socket a la dirección.";
const char* MESSAGE_SERVER_CANNOT_LISTEN = "No se pudo arrancar a escuchar conexiones en puerto.";
const char* MESSAGE_SERVER_WAITING_CONNECTIONS = "Esperando nuevas conexiones...";
const char* MESSAGE_SERVER_ERROR_CODE = "Código de error: ";

const char* MESSAGE_SERVER_SEND_MESSAGE_ERROR = "No se pudo enviar el mensaje ";
const char* MESSAGE_SERVER_SEND_MESSAGE_SUCCESS = "Se envió correctamente el mensaje ";

Server::~Server()
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		closesocket((it->second)->getSocket());
		delete it->second;
	}

	LOG(logINFO) << MESSAGE_SERVER_EXECUTION_END;
}

Server::Server(ServerConfiguration* serverConfig, string fileContent, Window* window, Configuration* config, Scenario* scenario, Camera * camera)
{
	this->portNumber = serverConfig->getPortNumber();

	this->serverConfig = serverConfig;
	this->fileContent = fileContent;
	this->window = window;
	this->config = config;
	this->scenario = scenario;
	//initialize camera
	this->camera = camera;

	this->isValid = false;

	LOG(logINFO) << MESSAGE_STARTING_SERVER << "El Puerto es " << this->portNumber << ". La máxima cantidad de clientes es " << this->serverConfig->getMaxAllowedClients();

	this->connectedClients = 0;
	clients.clear();

	if (!initializeWindowsSupport()) {
		return;
	}
	if (!initSocket()) {
		return;
	}
	if (!configureAddress()) {
		return;
	}
	if (!bindSocket()) {
		return;
	}
	if (!startListening()) {
		return;
	}

	LOG(logINFO) << MESSAGE_STARTING_SERVER_OK << SocketUtils::getIpFromAddress(this->address) << ":" << this->portNumber;

	this->isValid = true;
}

bool Server::initializeWindowsSupport()
{
	WSADATA wsaData;
	unsigned short wVersionRequested = MAKEWORD(2, 2);
	int initResult = WSAStartup(wVersionRequested, &wsaData);
	if (initResult != 0 || (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)) {
		LOG(logERROR) << MESSAGE_SERVER_CANNOT_FIND_DLL << MESSAGE_SERVER_ERROR_CODE << WSAGetLastError();
		return false;
	}
	return true;
}

bool Server::initSocket()
{
	//create socket
	this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->_socket == INVALID_SOCKET)
	{
		LOG(logERROR) << MESSAGE_SERVER_CANNOT_OPEN_SOCKET << MESSAGE_SERVER_ERROR_CODE << WSAGetLastError();
		return false;
	}
	return true;
}

bool Server::configureAddress()
{
	//Take a look at: http://stackoverflow.com/questions/3492647/what-are-the-alternative-for-win32-to-alarm-bzero-bcopy-when-porting-c-code
	bzero((char*)&this->address, sizeof(this->address));

	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(this->portNumber);

	return true;
}

bool Server::bindSocket()
{
	if (::bind(_socket, (struct sockaddr *)&this->address, sizeof(this->address)) < 0)
	{
		LOG(logERROR) << MESSAGE_SERVER_CANNOT_BIND_SOCKET;
		return false;
	}
	return true;
}

bool Server::startListening()
{
	if (listen(_socket, 5) < 0) {
		LOG(logERROR) << MESSAGE_SERVER_CANNOT_LISTEN << MESSAGE_SERVER_ERROR_CODE << WSAGetLastError();
		return false;
	}
	return true;
}

int Server::getAvailableIndex()
{
	for (int i = 0; i < this->serverConfig->getMaxAllowedClients(); i++)
	{
		if (!clients.count(i)) return i;
	}
	return -1;
}

int Server::getDisconnectedIndex()
{
	for (int i = 0; i < this->serverConfig->getMaxAllowedClients(); i++)
	{
		if (clients.count(i)) 
		{
			if (!clients[i]->getPlayer()->getIsConnected()) {
				return i;
			}
		}
	}
	return -1;
}

void Server::acceptClientConnection()
{
	Client* client = new Client(this, nullptr);
	if (!client->acceptSocket()) {
		delete client;
		return;
	}

	//Get either available or disconnected index
	int index = getAvailableIndex();
	if (index < 0) index = getDisconnectedIndex();
	if (index < 0) {
		delete client;
		return;
	}

	int clientNumber = index + 1;
	Player* player = clients.count(index) && clients[index] != NULL ? clients[index]->getPlayer() : nullptr;
	
	if (!client->welcome(clientNumber, player)) {
		delete client;
		return;
	}

	if (player != nullptr) {
		delete clients[index];
	}

	clients[index] = client;
	/*this->connectedClients++;*/
}

void Server::removeClientConnection(int clientNumber)
{
	int index = clientNumber - 1;
	Client* client = clients[index];
	client->closeSocket();
	
	//delete client;
	//clients.erase(index);
	client->getPlayer()->setIsConnected(false);
	
	this->connectedClients--;
}

void Server::addConnectedClients()
{
	this->connectedClients++;
}

SOCKET Server::getSocket()
{
	return this->_socket;
}

string Server::getFileContent()
{
	return this->fileContent;
}

Window * Server::getWindow()
{
	return this->window;
}

Configuration * Server::getConfiguration()
{
	return this->config;
}

Scenario * Server::getScenario()
{
	return this->scenario;
}

Camera * Server::getCamera()
{
	return this->camera;
}

void Server::waitForClientConnections()
{
	bool keepWaiting = true;
	bool startNotificationSent = false;

	LOG(logINFO) << MESSAGE_SERVER_WAITING_CONNECTIONS;

	while (keepWaiting) {
		//Still accepting new connections
		if (this->connectedClients <= this->serverConfig->getMaxAllowedClients()) 
		{
			this->acceptClientConnection();
		}

		//Max connections reached!
		if (!startNotificationSent && this->connectedClients == this->serverConfig->getMaxAllowedClients())
		{
			ServerMessage* message = new ServerMessage();
			message->setType(ServerMessageType::start_game);
			char* serializedMessage = StringUtils::convert(message->serialize());
			delete message;

			this->sendBroadcast(serializedMessage);
			Sleep(1000);
			startNotificationSent = true;
		}
	}
}

void Server::sendBroadcast(char* serializedMessage)
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		int bytecount;
		//If client is not connected, just set to false
		if (!it->second->getPlayer()->getIsConnected()) continue;

		if ((bytecount = send(it->second->getSocket(), serializedMessage, strlen(serializedMessage), 0)) == SOCKET_ERROR) {
			LOG(logERROR) << MESSAGE_SERVER_SEND_MESSAGE_ERROR << serializedMessage << ". " << MESSAGE_SERVER_SEND_MESSAGE_ERROR << WSAGetLastError()
				<< " (Cliente " << it->second->getClientNumber() << ")";
			continue;
		}
		//LOG(logINFO) << MESSAGE_SERVER_SEND_MESSAGE_SUCCESS << message << " (Cliente " << it->second->getClientNumber() << ")";
	}
}

bool Server::validate()
{
	return this->isValid;
}

ServerMessage* Server::getPlayersStatusMessage()
{
	vector<Player*> clientsPlayers = this->clientsPlayers();

	//update camera
	CameraController::updateCamera(this->camera, clientsPlayers);	

	ServerMessage * message = new ServerMessage();
	message->setType(players_status);
	message->setPlayers(clientsPlayers);
	message->setCamera(new Camera(*this->camera));

	return message;
}

vector<Player*> Server::clientsPlayers()
{
	//TODO: ADD MUTEX
	vector<Player*> clientPlayers = vector<Player*>();
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		//copy player to avoid problems (will be deleted in ServerMessage destructor)
		Player * clientPlayer = new Player(*it->second->getPlayer());
		clientPlayers.push_back(clientPlayer);
	}

	return clientPlayers;
}