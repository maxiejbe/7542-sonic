#include "Serializable.h"

/*
Parses serializable object from rapidjson node.
Calls unserialize of Parent node ["node Name"]
*/
void Serializable::ParseObject(Value* parentNodeRef)
{
	Value& parentNode = *parentNodeRef;
	const char* nodeName = GetNodeName();

	if (!parentNode.HasMember(nodeName)) {
		//TODO: Log warning
		return;
	}

	Value& node = parentNode[nodeName];
	if (!node.IsObject()) {
		//TODO: Log warning
		return;
	}

	Unserialize(&node);
}

void Serializable::ParseCurrentObject(Value* nodeRef)
{
	Value& node = *nodeRef;
	if (!node.IsObject()) {
		//TODO: Log warning
		return;
	}

	Unserialize(&node);
}

