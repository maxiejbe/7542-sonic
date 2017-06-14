#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include "../Vector2.h"
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include <typeinfo>

enum ConnectionStatus { assign, connected, disconnected };
enum PlayerStatus { idle, walking, running, jumping, spinning };
enum PlayerType { SONIC, TAILS, KNUCKLES, SHADOW };
enum BonusType { RING, INVINCIBILITY, SHIELD };
enum ObstacleType { BLOCK, SPYKES };
enum EnemyType { FISH, FLY, CRAB };

enum MessageType { player_assign_ok, levels_content_ok, level_start_ok, status, heart_beat, no_type, team_assign };

struct Message : public SerializableMessage {
public:

	Message::Message();
	Message::Message(double dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKPShift, bool isKULeft, bool isKURight, bool isKUSpace, bool isKUShift, bool isKUTest);

	void setType(MessageType);
	MessageType getType();

	double getTimeStep();

	bool getIsKPLeft();
	bool getIsKPSpace();
	bool getIsKPRight();
	bool getIsKPUp();
	bool getIsKPShift();

	bool getIsKULeft();
	bool getIsKURight();
	bool getIsKUSpace();
	bool getIsKUShift();
	bool getIsKUTest();

	void setTeamId(int team);

	//bool unserialize(string json);

	bool equals(Message& message);

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	const string DELIMITER = "|";
	vector<void*> properties;

	MessageType type;
	double dt;
	int teamId;
	bool isKPLeft, isKPRight, isKPUp, isKPSpace, isKPShift, isKULeft, isKURight, isKUSpace, isKUShift, isKUTest;

	void performSerialization(Writer<StringBuffer>& writer);
};

#endif
