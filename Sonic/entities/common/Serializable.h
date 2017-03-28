#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include "rapidjson/document.h"
#include <vector>

using namespace rapidjson;
using namespace std;

class Serializable {
public:
	//TODO: Change name to parse inner object
	void ParseObject(Value* parentNodeRef);

	void ParseCurrentObject(Value* nodeRef);

	virtual void Unserialize(Value* nodeRef) = 0;
	virtual char* GetNodeName() = 0;
};

#endif