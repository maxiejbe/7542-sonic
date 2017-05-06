#ifndef SERIALIZABLE_MESSAGE_H
#define SERIALIZABLE_MESSAGE_H

#include "../entities/common/Serializable.h"
#include "../utils/StringUtils.h"

class SerializableMessage : public Serializable {
public:
	SerializableMessage();

	bool fromJson(string json);

	// Inherited via Serializable
	virtual void unserialize(Value* nodeRef) = 0;
	virtual char* getNodeName() = 0;
	virtual string serialize() = 0;
};

#endif