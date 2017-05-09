#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include "../Vector2.h"
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include <typeinfo>

enum ConnectionStatus { assign, connected, disconnected };
enum PlayerStatus { idle, walking, running, jumping };
enum PlayerType { SONIC, TAILS };

struct Message : public SerializableMessage {
public:

	Message::Message();
	Message::Message(double dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace);

	string getBinaryData();

	double getTimeStep();
	
	bool getIsKPLeft();
	bool getIsKPSpace();
	bool getIsKPRight();
	bool getIsKPUp();
	
	bool getIsKULeft();
	bool getIsKURight();
	bool getIsKUSpace();

	//bool unserialize(string json);

	bool equals(Message& message);

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	const string DELIMITER = "|";
	vector<void*> properties;
	
	double dt;
	bool isKPLeft, isKPRight, isKPUp, isKPSpace, isKULeft, isKURight, isKUSpace;

	void performSerialization(Writer<StringBuffer>& writer);
};

#endif
