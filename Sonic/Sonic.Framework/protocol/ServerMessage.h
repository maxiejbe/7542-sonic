#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include "../entities/Camera.h"
#include "../entities/Level.h"

enum ServerMessageType {player_assign, levels_content, level_start, level_finish, player_entities_status, typeless, heart_beat_server };

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
	vector<Entity*> getEntities();
	vector<Level>* getLevels();
	int getLevelToStart();
	Camera * getCamera();
	void setCamera(Camera * camera);
	void setPlayers(vector<Player*> players);
	void setEntities(vector<Entity*> enemies);
	void setLevels(vector<Level>* levels);
	void setLevelToStart(int);
	
	void serializePlayers(Writer<StringBuffer>& writer);
	void serializeLevels(Writer<StringBuffer>& writer);
	void serializeEntities(Writer<StringBuffer>& writer);

	void serializeCamera(Writer<StringBuffer>& writer);
	void parsePlayersStatus(Value *);
	void parseLevels(Value * nodeRef);
	void parseEntitiesStatus(Value *);
	void parseCameraStatus(Value *);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	vector<Player*> players;
	vector<Entity*> entities;
	vector<Level>* levels;
	int levelToStart;
	Camera * camera;
	int playerNumber;
};

#endif