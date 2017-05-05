#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include "../Vector2.h"
#include "common/BoostSerializable.h"
#include <typeinfo>

enum ConnectionStatus { assign, connected, disconnected };
enum PlayerStatus { idle, walking, running, jumping };

struct Message {
public:

	template <class ArchiveT>
	void serialize(ArchiveT& ar, const unsigned int)
	{
		ar & boost::serialization::make_nvp("playerNumber", playerNumber);
		ar & boost::serialization::make_nvp("dt", dt);
		ar & boost::serialization::make_nvp("isKPLeft", isKPLeft);
		ar & boost::serialization::make_nvp("isKPRight", isKPRight);
		ar & boost::serialization::make_nvp("isKPUp", isKPUp);
		ar & boost::serialization::make_nvp("isKPSpace", isKPSpace);
		ar & boost::serialization::make_nvp("isKULeft", isKULeft);
		ar & boost::serialization::make_nvp("isKURight", isKURight);
		ar & boost::serialization::make_nvp("isKUSpace", isKUSpace);
	}

	Message();
	Message(string);
	Message(int);
	Message::Message(float dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace);

	void setPosition(Vector2 position);
	Vector2 getPosition();

	void setConnectionStatus(ConnectionStatus);
	ConnectionStatus getConnectionStatus();

	void setPlayerNumber(int);
	int getNumber();

	void fromString(string);
	void toString(string*);

	bool validate();

	void initializeProperties();

	string getBinaryData();

private:
	const string DELIMITER = "|";
	vector<void*> properties;
	int playerNumber;
	Vector2 position;
	ConnectionStatus connectionStatus;
	PlayerStatus playerStatus;

	float dt;
	bool isKPLeft, isKPRight, isKPUp, isKPSpace, isKULeft, isKURight, isKUSpace;

	string binaryMsg;
};

#endif
