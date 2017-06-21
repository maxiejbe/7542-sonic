#include "ServerMessage.h"
#include "ServerMessage.h"
#include "ServerMessage.h"

const char* SERVER_MESSAGE_TYPE_NODE = "t";
const char* SERVER_MESSAGE_TIME_NODE = "ti";
const char* SERVER_MESSAGE_GAME_MODE_NODE = "gm";
const char* SERVER_MESSAGE_PLAYER_NUMBER_NODE = "pn";
const char* SERVER_MESSAGE_PLAYERS_STATUS_NODE = "ps";
const char* SERVER_MESSAGE_LEVELS_STATUS_NODE = "lvs";
const char* SERVER_MESSAGE_LEVEL_START_NODE = "l2s";
const char* SERVER_MESSAGE_CAMERA_NODE = "ca";
const char* SERVER_MESSAGE_FILE_CONTENT_NODE = "fc";
const char* SERVER_MESSAGE_ENTITIES_STATUS_NODE = "ets";

ServerMessage::ServerMessage()
{
	this->playerNumber = -1;
	this->type = typeless;
	this->players = vector<Player*>();
	this->entities = vector<Entity*>();
	this->levels = nullptr;
	this->camera = nullptr;
	this->levelToStart = 0;
}

ServerMessage::~ServerMessage()
{
	if (this->camera) delete this->camera;
}

void ServerMessage::setType(ServerMessageType type)
{
	this->type = type;
}

ServerMessageType ServerMessage::getType()
{
	return this->type;
}

void ServerMessage::setPlayerNumber(int playerNumber)
{
	this->playerNumber = playerNumber;
}

void ServerMessage::setGameMode(GameMode gameMode)
{
	this->gameMode = gameMode;
}

GameMode ServerMessage::getGameMode()
{
	return this->gameMode;
}


int ServerMessage::getPlayerNumber()
{
	return this->playerNumber;
}


vector<Player*> ServerMessage::getPlayers()
{
	return this->players;
}

vector<Entity*> ServerMessage::getEntities()
{
	return this->entities;
}

vector<Level>* ServerMessage::getLevels()
{
	return this->levels;
}

int ServerMessage::getLevelToStart()
{
	return this->levelToStart;
}

Camera * ServerMessage::getCamera()
{
	return this->camera;
}

int ServerMessage::getTime()
{
	return this->time;
}

void ServerMessage::setTime(int ms)
{
	this->time = ms;
}

void ServerMessage::setCamera(Camera * camera)
{
	this->camera = camera;
}

void ServerMessage::setPlayers(vector<Player*> players)
{
	this->players = players;
}

void ServerMessage::setEntities(vector<Entity*> entities)
{
	this->entities = entities;
}

void ServerMessage::setLevels(vector<Level>* levels)
{
	this->levels = levels;
}

void ServerMessage::setLevelToStart(int levelToStart)
{
	this->levelToStart = levelToStart;
}


void ServerMessage::unserialize(Value* nodeRef)
{
	//type
	parseInt((int*)&type, typeless, nodeRef, SERVER_MESSAGE_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);
	switch (this->type)
	{
	case player_assign:
		//player number
		parseInt((int*)&gameMode, individual, nodeRef, SERVER_MESSAGE_GAME_MODE_NODE);
		parseInt(&playerNumber, -1, nodeRef, SERVER_MESSAGE_PLAYER_NUMBER_NODE);
		break;
	case level_start:
		parseInt(&levelToStart, 0, nodeRef, SERVER_MESSAGE_LEVEL_START_NODE);
		break;
	case levels_content:
		parseLevels(nodeRef);
		break;
	case player_status:
		//time
		parseInt((int*)&time, 0, nodeRef, SERVER_MESSAGE_TIME_NODE);
		parsePlayersStatus(nodeRef);
		parseCameraStatus(nodeRef);
		break;
	case entities_status:
		//time
		parseInt((int*)&time, 0, nodeRef, SERVER_MESSAGE_TIME_NODE);
		parseEntitiesStatus(nodeRef);
		break;
	case level_finish:
	case game_finish:
		parsePlayersStatus(nodeRef);
		break;
	default:
		break;
	}
}

char* ServerMessage::getNodeName()
{
	return nullptr;
}

string ServerMessage::serialize()
{
	if (this->type == typeless) {
		return "";
	}

	StringBuffer s;
	Writer<StringBuffer> writer(s);
	//serialize
	writer.StartObject();
	//type
	writer.String(SERVER_MESSAGE_TYPE_NODE);
	writer.Int(this->type);

	//player number
	switch (this->type)
	{
	case player_assign:
		writer.String(SERVER_MESSAGE_GAME_MODE_NODE);
		writer.Int(this->gameMode);
		writer.String(SERVER_MESSAGE_PLAYER_NUMBER_NODE);
		writer.Int(this->playerNumber);
		break;
	case player_status:
		//time
		writer.String(SERVER_MESSAGE_TIME_NODE);
		if (players.size() > 0)
			writer.Int(players.at(0)->getTime());
		else
			writer.Int(0);

		this->serializePlayers(writer);
		this->serializeCamera(writer);
		break;
	case entities_status:
		//time
		writer.String(SERVER_MESSAGE_TIME_NODE);
		if (entities.size() > 0)
			writer.Int(entities.at(0)->getTime());
		else
			writer.Int(0);

		this->serializeEntities(writer);
		break;
	case levels_content:
		this->serializeLevels(writer);
		break;
	case level_start:
		writer.String(SERVER_MESSAGE_LEVEL_START_NODE);
		writer.Int(levelToStart);
		break;
	case level_finish:
	case game_finish:
		this->serializePlayers(writer);
		break;
	default:
		break;
	}

	writer.EndObject();

	return s.GetString();
}

void ServerMessage::serializeCamera(Writer<StringBuffer>& writer)
{
	if (!this->camera) return;
	writer.String(SERVER_MESSAGE_CAMERA_NODE);
	string serializedcamera = this->camera->getSerializedCamera();
	writer.String(serializedcamera.c_str());
}

void ServerMessage::serializePlayers(Writer<StringBuffer>& writer)
{
	writer.String(SERVER_MESSAGE_PLAYERS_STATUS_NODE);
	writer.StartArray();

	vector<Player*>::iterator it = this->players.begin();
	while (it != this->players.end()) {
		if (*it == NULL) continue;
		string serializedplayer = (*it)->getSerializedPlayer();
		writer.String(serializedplayer.c_str());
		it++;
	}
	writer.EndArray();
}

void ServerMessage::serializeLevels(Writer<StringBuffer>& writer)
{
	writer.String(SERVER_MESSAGE_LEVELS_STATUS_NODE);
	writer.StartArray();

	vector<Level>::iterator it = this->levels->begin();
	while (it != this->levels->end()) {
		string serializedLevel = (*it).serialize();
		writer.String(serializedLevel.c_str());
		it++;
	}
	writer.EndArray();
}

void ServerMessage::serializeEntities(Writer<StringBuffer>& writer)
{
	writer.String(SERVER_MESSAGE_ENTITIES_STATUS_NODE);
	writer.StartArray();

	vector<Entity*>::iterator it = this->entities.begin();
	while (it != this->entities.end()) {
		if (*it == NULL) continue;
		string serializedEntity = (*it)->getSerializedEntity();
		writer.String(serializedEntity.c_str());
		it++;
	}
	writer.EndArray();

	while (it != this->entities.end()) {
		delete *it;
	}
	entities.clear();
}


void ServerMessage::parseCameraStatus(Value * nodeRef)
{
	Value& node = *nodeRef;

	if (nodeRef == nullptr || !node.HasMember(SERVER_MESSAGE_CAMERA_NODE)) {
		LOG(logWARNING) << "Server Message: Fallo parseo de camara";
		return;
	}

	const Value& cameraStatus = node[SERVER_MESSAGE_CAMERA_NODE];
	//Check cameraStatus
	if (!cameraStatus.IsString()) {
		LOG(logWARNING) << "Server Message: Campo incorrecto de camera" << SERVER_MESSAGE_PLAYERS_STATUS_NODE;
		return;
	}

	Document jsonCamera;
	if (jsonCamera.Parse(cameraStatus.GetString()).HasParseError()) {
		LOG(logERROR) << "Server Message: Error al parsear camera";
		return;
	}

	if (this->camera) delete this->camera;
	this->camera = new Camera();
	this->camera->unserialize(&jsonCamera);
}

void ServerMessage::parsePlayersStatus(Value * nodeRef)
{
	//free players and clear vector
	Value& node = *nodeRef;

	//LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(SERVER_MESSAGE_PLAYERS_STATUS_NODE)) {
		LOG(logWARNING) << "Server Message: Fallo parseo de jugadores";
		return;
	}

	//string childNodeValue = getNodeContent(&node[SERVER_MESSAGE_PLAYERS_STATUS_NODE]);
	const Value& playersStatus = node[SERVER_MESSAGE_PLAYERS_STATUS_NODE];
	if (!playersStatus.IsArray()) {
		LOG(logWARNING) << "Server Message: Campo incorrecto de jugadores " << SERVER_MESSAGE_PLAYERS_STATUS_NODE;
		return;
	}

	//unserialize players
	Document jsonPlayer;
	for (Value::ConstValueIterator itr = playersStatus.Begin(); itr != playersStatus.End(); ++itr) {
		if (jsonPlayer.Parse((*itr).GetString()).HasParseError()) {
			//LOG
			continue;
		}

		//unsearialize player and add to vector
		Player* newPlayer = new Player();
		newPlayer->unserialize(&jsonPlayer);
		this->players.push_back(newPlayer);
	}
}

void ServerMessage::parseLevels(Value * nodeRef)
{
	//free enemies and clear vector
	Value& node = *nodeRef;

	if (nodeRef == nullptr || !node.HasMember(SERVER_MESSAGE_LEVELS_STATUS_NODE)) {
		LOG(logWARNING) << "Server Message: Fallo parseo de niveles";
		return;
	}

	//string childNodeValue = getNodeContent(&node[SERVER_MESSAGE_PLAYERS_STATUS_NODE]);
	const Value& levels = node[SERVER_MESSAGE_LEVELS_STATUS_NODE];
	if (!levels.IsArray()) {
		LOG(logWARNING) << "Server Message: Campo incorrecto de enemigos " << SERVER_MESSAGE_LEVELS_STATUS_NODE;
		return;
	}

	//unserialize enemies
	Document jsonEnemy;
	this->levels = new vector<Level>();
	for (Value::ConstValueIterator itr = levels.Begin(); itr != levels.End(); ++itr) {
		if (jsonEnemy.Parse((*itr).GetString()).HasParseError()) {
			//LOG
			continue;
		}

		//unsearialize player and add to vector
		Level newLevel = Level();
		newLevel.unserialize(&jsonEnemy);
		this->levels->push_back(newLevel);
	}
}

void ServerMessage::parseEntitiesStatus(Value * nodeRef)
{
	//free players and clear vector
	Value& node = *nodeRef;

	//LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(SERVER_MESSAGE_ENTITIES_STATUS_NODE)) {
		LOG(logWARNING) << "Server Message: Fallo parseo de entidades";
		return;
	}

	//string childNodeValue = getNodeContent(&node[SERVER_MESSAGE_PLAYERS_STATUS_NODE]);
	const Value& entitiesStatus = node[SERVER_MESSAGE_ENTITIES_STATUS_NODE];
	if (!entitiesStatus.IsArray()) {
		LOG(logWARNING) << "Server Message: Campo incorrecto de entidades " << SERVER_MESSAGE_ENTITIES_STATUS_NODE;
		return;
	}

	//unserialize players
	Document jsonEntity;
	for (Value::ConstValueIterator itr = entitiesStatus.Begin(); itr != entitiesStatus.End(); ++itr) {
		if (jsonEntity.Parse((*itr).GetString()).HasParseError()) {
			//LOG
			continue;
		}

		//unsearialize player and add to vector
		this->entities.push_back(EntityResolver::parse(&jsonEntity));
	}
}

