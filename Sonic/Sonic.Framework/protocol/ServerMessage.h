#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include "../entities/Player.h"
#include "../entities/Camera.h"
#include "../entities/Team.h"

enum ServerMessageType {player_assign, content, start_game, players_status, typeless, heart_beat_server,  team_options};

//TODO: Apply polimorphism with server message type 
class ServerMessage : public SerializableMessage {
public:
	ServerMessage();
	~ServerMessage();
	void setType(ServerMessageType);
	ServerMessageType getType();
	void setPlayerNumber(int);
	int getPlayerNumber();
	vector<Player*> getPlayers();
	Camera * getCamera();
	vector<Team*> getTeams();
	void setCamera(Camera * camera);
	void setPlayers(vector<Player*> players);
	void setFileContent(string content);
	void setTeams(vector<Team*> teams);
	string getFileContent();

	void serializePlayers(Writer<StringBuffer>& writer);
	void serializeCamera(Writer<StringBuffer>& writer);
	void serializeTeams(Writer<StringBuffer>& writer);
	void parsePlayersStatus(Value *);
	void parseCameraStatus(Value *);
	void parseTeams(Value *);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	vector<Player*> players;
	vector<Team*> teams;
	Camera * camera;
	string fileContent;
	int playerNumber;
};

#endif