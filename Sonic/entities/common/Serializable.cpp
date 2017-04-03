#include "Serializable.h"	

const char* MESSAGE_PARSING_NODE_FIELD = "Buscando campo: ";
const char* MESSAGE_OK_PARSING_NODE_FIELD = "Valor procesado correctamente: ";
const char* MESSAGE_ERROR_PARSING_NODE_FIELD = "No se encontr� el campo o su valor es incorrecto. Tomando por default en valor: ";

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

void Serializable::ParseInt(int * value, int defaultValue, Value * nodeRef, const char* fieldName)
{
	Value& node = *nodeRef;

	//Check width field
	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);
	if (node.HasMember(fieldName) && node[fieldName].IsInt()) {
		*value = node[fieldName].GetInt();
		LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD + to_string(*value);
	}
	else {
		*value = defaultValue;
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD + to_string(defaultValue);
	}
}

void Serializable::ParseString(string * value, string defaultValue, Value * nodeRef, const char* fieldName)
{
	Value& node = *nodeRef;

	//Check width field
	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);
	if (node.HasMember(fieldName) && node[fieldName].IsString()) {
		*value = node[fieldName].GetString();
		LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD + *value;
	}
	else {
		*value = defaultValue;
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD + defaultValue;
	}
}

