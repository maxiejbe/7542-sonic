#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include "../entities/Camera.h"
#include "../entities/enemies/Enemy.h"
#include "../entities/Level.h"

enum ServerMessageType {player_assign, levels_content, level_start, players_status, enemies_status, typeless, heart_beat_server };

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
	vector<Enemy*> getEnemies();
	vector<Level>* getLevels();
	Camera * getCamera();
	void setCamera(Camera * camera);
	void setPlayers(vector<Player*> players);
	void setEnemies(vector<Enemy*> enemies);
	void setLevels(vector<Level>* levels);
	
	void serializePlayers(Writer<StringBuffer>& writer);
	void serializeLevels(Writer<StringBuffer>& writer);
	//void serializeEnemies(Writer<StringBuffer>& writer);
	void serializeCamera(Writer<StringBuffer>& writer);
	void parsePlayersStatus(Value *);
	void parseLevels(Value * nodeRef);
	//void parseEnemiesStatus(Value *);
	void parseCameraStatus(Value *);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	vector<Player*> players;
	vector<Enemy*> enemies;
	vector<Level>* levels;
	Camera * camera;
	int playerNumber;
};

#endif