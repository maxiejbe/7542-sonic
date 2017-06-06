#include "ServerMessage.h"

const char* SERVER_MESSAGE_TYPE_NODE = "t";
const char* SERVER_MESSAGE_PLAYER_NUMBER_NODE = "pn";
const char* SERVER_MESSAGE_PLAYERS_STATUS_NODE = "ps";
const char* SERVER_MESSAGE_CAMERA_NODE = "ca";
const char* SERVER_MESSAGE_FILE_CONTENT_NODE = "fc";
const char* SERVER_MESSAGE_TEAMS_NODE = "tm";

ServerMessage::ServerMessage()
{
	this->playerNumber = -1;
	this->type = typeless;
	this->players = vector<Player*>();
	this->teams = vector<Team*>();
	this->camera = nullptr;
	this->fileContent = "";
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

int ServerMessage::getPlayerNumber()
{
	return this->playerNumber;
}


vector<Player*> ServerMessage::getPlayers()
{
	return this->players;
}

Camera * ServerMessage::getCamera()
{
	return this->camera;
}

vector<Team*> ServerMessage::getTeams()
{
	return this->teams;
}

void ServerMessage::setCamera(Camera * camera)
{
	this->camera = camera;
}

void ServerMessage::setPlayers(vector<Player*> players)
{
	this->players = players;
}

void ServerMessage::setFileContent(string content)
{
	this->fileContent = content;
}

void ServerMessage::setTeams(vector<Team*> teams)
{
	this->teams = teams;
}

string ServerMessage::getFileContent()
{
	return this->fileContent;
}


void ServerMessage::unserialize(Value* nodeRef)
{
	//type
	parseInt((int*)&type, typeless, nodeRef, SERVER_MESSAGE_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);
	switch (this->type)
	{
		case player_assign:
			//player number
			parseInt(&playerNumber, -1, nodeRef, SERVER_MESSAGE_PLAYER_NUMBER_NODE);
			break;
		case players_status:
			parsePlayersStatus(nodeRef);
			parseCameraStatus(nodeRef);
			break;
		case content:
			parseString(&this->fileContent, "", nodeRef, SERVER_MESSAGE_FILE_CONTENT_NODE);
			break;
		case team_options:
			parseTeams(nodeRef);
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
			writer.String(SERVER_MESSAGE_PLAYER_NUMBER_NODE);
			writer.Int(this->playerNumber);
			break;
		case players_status:
			this->serializePlayers(writer);
			this->serializeCamera(writer);
		case content:
			writer.String(SERVER_MESSAGE_FILE_CONTENT_NODE);
			writer.String(this->fileContent.c_str());
		case team_options:
			this->serializeTeams(writer);
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
	string serializedcamera = this->camera->serialize();
	writer.String(serializedcamera.c_str());
}

void ServerMessage::serializeTeams(Writer<StringBuffer>& writer)
{
	writer.String(SERVER_MESSAGE_TEAMS_NODE);
	writer.StartArray();

	vector<Team*>::iterator it = this->teams.begin();
	while (it != this->teams.end()) {
		if (*it == NULL) continue;
		string serializedTeam = (*it)->serialize();
		writer.String(serializedTeam.c_str());
		it++;
	}

	writer.EndArray();
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

void ServerMessage::parseTeams(Value * nodeRef)
{
	//free players and clear vector
	Value& node = *nodeRef;

	//LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(SERVER_MESSAGE_TEAMS_NODE)) {
		LOG(logWARNING) << "Server Message: Fallo parseo de equipos";
		return;
	}

	//string childNodeValue = getNodeContent(&node[SERVER_MESSAGE_PLAYERS_STATUS_NODE]);
	const Value& teamOptions = node[SERVER_MESSAGE_TEAMS_NODE];
	if (!teamOptions.IsArray()) {
		LOG(logWARNING) << "Server Message: Campo incorrecto de equipos " << SERVER_MESSAGE_TEAMS_NODE;
		return;
	}

	//unserialize teams
	Document jsonPlayer;
	for (Value::ConstValueIterator itr = teamOptions.Begin(); itr != teamOptions.End(); ++itr) {
		if (jsonPlayer.Parse((*itr).GetString()).HasParseError()) {
			//LOG
			continue;
		}

		//unsearialize player and add to vector
		Team* newTeam = new Team();
		newTeam->unserialize(&jsonPlayer);
		this->teams.push_back(newTeam);
	}
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

