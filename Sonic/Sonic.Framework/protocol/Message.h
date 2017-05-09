#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include "../Vector2.h"
//#include "common/BoostSerializable.h"
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include <typeinfo>

enum ConnectionStatus { assign, connected, disconnected };
enum PlayerStatus { idle, walking, running, jumping };
enum PlayerType { SONIC, TAILS };

struct Message : public SerializableMessage {
public:

	/*template <class ArchiveT>
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
	}*/

	Message::Message();
	Message::Message(double dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace);

	void setConnectionStatus(ConnectionStatus);
	ConnectionStatus getConnectionStatus();

	void setPlayerNumber(int);
	int getPlayerNumber();

	bool validate();

	string getBinaryData();

	double getTimeStep();
	
	bool getIsKPLeft();
	bool getIsKPSpace();
	bool getIsKPRight();
	bool getIsKPUp();
	
	bool getIsKULeft();
	bool getIsKURight();
	bool getIsKUSpace();

	bool unserialize(string json);

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	const string DELIMITER = "|";
	vector<void*> properties;
	int playerNumber;
	
	ConnectionStatus connectionStatus;
	PlayerStatus playerStatus;

	double dt;
	bool isKPLeft, isKPRight, isKPUp, isKPSpace, isKULeft, isKURight, isKUSpace;

	string binaryMsg;

	void performSerialization(Writer<StringBuffer>& writer);
};

#endif
