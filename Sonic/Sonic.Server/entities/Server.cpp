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

const int CLIENT_NUMBER_MAX_CONNECTED_PLAYERS = -99;
const int CLIENT_NUMBER_NOT_ACTIVE_PLAYERS = -100;

const int DEFAULT_COLLABORATIVE_TEAM_ID = 1;
const int PLAYER_TEAM_ID_NOT_SET = 0;
const int TEAMS_COUNT = 2;

Server::~Server()
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		closesocket((it->second)->getSocket());
		delete it->second;
		clients.erase(it);
	}

	for (vector<Client*>::iterator it = disconnectedClients.begin(); it != disconnectedClients.end(); ++it) {
		delete *it;
	}

	if (camera != nullptr) {
		delete camera;
	}

	LOG(logINFO) << MESSAGE_SERVER_EXECUTION_END;
}

void Server::terminateThreads()
{
	if (this->updateEnemiesThreadHandle != NULL)
	{
		this->continueUpdatingEnemies = false;
		CloseHandle(this->updateEnemiesThreadHandle);
		this->updateEnemiesThreadHandle = NULL;
	}
}

Server::Server(ServerConfiguration* serverConfig, string fileContent, Window* window, Configuration* config, GameConfig* gameConfig)
{
	this->portNumber = serverConfig->getPortNumber();

	this->serverConfig = serverConfig;
	this->fileContent = fileContent;
	this->window = window;
	this->config = config;
	this->gameConfig = gameConfig;

	this->currentLevel = 1; // First level
	this->lastLevel = gameConfig->getLevels()->size();
	this->resetLevel();

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

	for (size_t i = 0; i < TEAMS_COUNT; i++)
	{
		teamPoints[i] = 0;
	}
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

	char i;
	setsockopt(this->_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&i, sizeof(i));

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
	return CLIENT_NUMBER_MAX_CONNECTED_PLAYERS;
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
	return CLIENT_NUMBER_MAX_CONNECTED_PLAYERS;
}

void Server::acceptClientConnection()
{
	Client* client = new Client(this);
	if (!client->acceptSocket()) {
		delete client;
		return;
	}

	//Get either available or disconnected index
	int index = getAvailableIndex();
	if (index < 0) index = getDisconnectedIndex();
	if (index < 0) {
		//max users reached
		client->setClientNumber(index);
		client->sendClientNumber();
		delete client;
		return;
	}

	int clientNumber = index + 1;
	Player* player = clients.count(index) && clients[index] != NULL ? clients[index]->getPlayer() : nullptr;

	Client * previousClient = nullptr;
	if (player != nullptr) {
		//if player is not active inform client that all lives were lost^M
		if (!player->getIsActive()) {
			client->setClientNumber(CLIENT_NUMBER_NOT_ACTIVE_PLAYERS);
			client->sendClientNumber();
			delete client;
			return;
		}

		previousClient = clients[index];
	}

	if (!client->welcome(clientNumber, player)) {
		delete client;
		return;
	}

	clients[index] = client;
}

void Server::removeClientConnection(int clientNumber)
{
	int index = clientNumber - 1;
	Client* client = clients[index];

	client->getPlayer()->setIsConnected(false);
	this->connectedClients--;
	this->disconnectedClients.push_back(client);

	client->closeSocket();
	client->terminateThreads();
}

void Server::addConnectedClients()
{
	this->connectedClients++;

	//Max connections reached!
	if (this->gameStarted || this->connectedClients == this->serverConfig->getMaxAllowedClients())
	{
		if (!this->gameStarted) { this->gameStarted = true; }

		this->sendBroadcast();

		//start enemies update thread
		this->continueUpdatingEnemies = true;
		this->updateEnemiesThreadHandle = CreateThread(0, 0, runUpdateEnemiesHandler, (void*)this, 0, &this->updateEnemiesThreadId);
	}
}

int Server::getCurrentLevel()
{
	return this->currentLevel;
}

bool Server::lastLevelReached()
{
	return this->currentLevel == this->lastLevel;
}

void Server::resetLevel()
{
	Level* level = &this->gameConfig->getLevels()->at(this->currentLevel - 1);
	this->scenario = level->getScenario();

	//initialize camera
	this->camera = new Camera(0, 0, window->getWidth(), window->getHeight(), window->getWidth(), window->getHeight(), scenario->getWidth(), scenario->getHeight());
	this->levelFinishedNotified = false;
	//reset team rings
	for (size_t i = 0; i < TEAMS_COUNT; i++)
	{
		teamRings[i] = 0;
	}
}

vector<Level>* Server::getLevels()
{
	return this->gameConfig->getLevels();
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

GameConfig * Server::getGameConfig()
{
	return this->gameConfig;
}

Camera * Server::getCamera()
{
	return this->camera;
}

unordered_map<int, int>* Server::getTeamPoints()
{
	return &(this->teamPoints);
}

unordered_map<int, int>* Server::getTeamRings()
{
	return &(this->teamRings);
}

void Server::waitForClientConnections()
{
	bool keepWaiting = true;

	LOG(logINFO) << MESSAGE_SERVER_WAITING_CONNECTIONS;

	while (keepWaiting) {
		//Still accepting new connections
		if (this->connectedClients <= this->serverConfig->getMaxAllowedClients())
		{
			this->acceptClientConnection();
		}
	}
}

void Server::sendBroadcast()
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		int bytecount;
		//If client is not connected, just set to false
		if (!it->second->getPlayer()->getIsConnected()) continue;
		it->second->sendLevelStart();
	}
}

bool Server::validate()
{
	return this->isValid;
}

ServerMessage* Server::getStatusMessage()
{
	vector<Player*> clientsPlayers = this->clientsPlayers();

	//update camera
	CameraController::updateCamera(this->camera, clientsPlayers);
	this->camera->serializeCamera();

	ServerMessage * message = new ServerMessage();
	message->setType(player_entities_status);
	message->setPlayers(clientsPlayers);
	message->setEntities(this->getVisibleEntities());
	message->setCamera(new Camera(*this->camera));

	return message;
}

vector<Entity*> Server::getVisibleEntities()
{
	vector<Entity*> entities = this->scenario->getEntities();
	vector<Entity*> visibleEntities;
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++) {

		if ((*it)->getIsActive() && EntityController::isEntityVisible((*it), this->camera)) {
			visibleEntities.push_back((*it));
		}
	}

	return visibleEntities;
}

void Server::levelFinished()
{
	//mutex in order to avoid multiple level finished notifications
	bool notifyLevelFinish = false;
	bool lastLevelReached = false;
	this->levelFinishedMutex.lock();
	if (!this->levelFinishedNotified) {
		this->levelFinishedNotified = true;
		notifyLevelFinish = true;
	}
	lastLevelReached = this->lastLevelReached();
	this->levelFinishedMutex.unlock();

	//last level should't be notified, boss dead ends game
	if (lastLevelReached) {
		return;
	}

	if (notifyLevelFinish)
	{
		this->updateScoresLevelFinished();
		this->notifyClientsLevelFinished();
		//wait 5 seconds for client to display statistics
		Sleep(6000);
		this->currentLevel++;
		this->notifyClientsStartNewLevel();
		this->resetLevel();
	}
}

void Server::updateScoresLevelFinished() 
{
	int currentPlayerTeamId;
	int ringPoints;
	Player* player;
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		//If client is not connected, just set to false
		if (!it->second->getPlayer()->getIsConnected()) continue;
		player = it->second->getPlayer();
		currentPlayerTeamId = player->getTeamId();
		//calculate points obtained from rings
		ringPoints = player->getRings() * this->gameConfig->getRingPointsMultiplier();
		if (player->getRings() >= this->gameConfig->getRingsForBonus()) {
			ringPoints *= this->gameConfig->getBonusRingPointsMultiplier();
		}

		//update points
		player->sumPoints(ringPoints);
	}
}

void Server::notifyClientsLevelFinished()
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		//If client is not connected, just set to false
		if (!it->second->getPlayer()->getIsConnected()) continue;
		it->second->notifyLevelFinished();
	}
}

void Server::notifyClientsStartNewLevel()
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		//If client is not connected, just set to false
		if (!it->second->getPlayer()->getIsConnected()) continue;
		it->second->notifyStartNewLevel();
	}
}

void Server::notifyClientsGameFinished()
{
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		int bytecount;
		//If client is not connected, just set to false
		if (!it->second->getPlayer()->getIsConnected()) continue;
		it->second->notifyGameFinished();
	}
}

vector<Player*> Server::clientsPlayers()
{
	//TODO: ADD MUTEX
	int currentPlayerTeamId;
	vector<Player*> clientPlayers = vector<Player*>();
	for (unordered_map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		Player* player = (*it).second->getPlayer();
		//set team rings and points
		currentPlayerTeamId = player->getTeamId();
		if (currentPlayerTeamId > PLAYER_TEAM_ID_NOT_SET) {
			player->setTeamPoints(this->teamPoints[currentPlayerTeamId - 1]);
			player->setTeamRings(this->teamRings[currentPlayerTeamId - 1]);
		}

		if (player->getIsActive()) clientPlayers.push_back(player);
	}
	return clientPlayers;
}

DWORD Server::runUpdateEnemiesHandler(void * args)
{
	Server * serverInstance = (Server *)args;
	serverInstance->updateEnemiesHandler();
	return 0;
}

DWORD Server::updateEnemiesHandler()
{
	while (this->continueUpdatingEnemies) {
		vector<Entity*> entities = scenario->getEntities();
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++) {
			if ((*it)->getIsMoving()) {
				//We should find a more elegant solution. JA!
				Enemy* enemy = (Enemy*)*it;
				if (enemy->getIsActive() && EntityController::isEntityVisible(enemy, this->camera)) {
					EnemyController::update(enemy, timer.elapsed());
				}
			}

			(*it)->serializeEntity();
			//Sleep(10);
		}
	}

	return 0;
}

