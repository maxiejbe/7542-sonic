#include "Serializable.h"	

const char* MESSAGE_PARSING_NODE_FIELD = "Buscando campo: ";
const char* MESSAGE_OK_PARSING_NODE_FIELD = "Valor procesado correctamente: ";
const char* MESSAGE_ERROR_PARSING_NODE_FIELD = "No se encontró el campo o su valor es incorrecto. Tomando por default en valor: ";

const char* MESSAGE_ERROR_PARSING_INNER_NODE = "No se encontró el nodo ";
const char* MESSAGE_ERROR_NOT_AN_OBJECT_INNER_NODE = "El nodo encontrado no es un objeto";

/*
Parses serializable object from rapidjson node.
Calls unserialize of Parent node ["node Name"]
*/
void Serializable::parseObject(Value* parentNodeRef)
{
	Value& parentNode = *parentNodeRef;
	const char* nodeName = getNodeName();

	if (!parentNode.HasMember(nodeName)) {
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_INNER_NODE << nodeName;
		return;
	}

	Value& node = parentNode[nodeName];
	if (!node.IsObject()) {
		LOG(logWARNING) << MESSAGE_ERROR_NOT_AN_OBJECT_INNER_NODE << ": " << nodeName;
		return;
	}

	unserialize(&node);
}

void Serializable::parseCurrentObject(Value* nodeRef)
{
	Value& node = *nodeRef;
	if (!node.IsObject()) {
		LOG(logWARNING) << MESSAGE_ERROR_NOT_AN_OBJECT_INNER_NODE;
		return;
	}

	unserialize(&node);
}

void Serializable::parseInt(int * value, int defaultValue, Value * nodeRef, const char* fieldName, function<bool(int)> condition)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);
	if (node.HasMember(fieldName) && node[fieldName].IsInt() && (condition != NULL && condition(node[fieldName].GetInt()) || condition == NULL)) {
		*value = node[fieldName].GetInt();
		LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD << to_string(*value);
	}
	else {
		*value = defaultValue;
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD << fieldName << "=" << defaultValue;
	}
}

void Serializable::parseString(string * value, string defaultValue, Value * nodeRef, const char* fieldName)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);
	if (node.HasMember(fieldName) && node[fieldName].IsString()) {
		*value = node[fieldName].GetString();
		LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD << *value;
	}
	else {
		*value = defaultValue;
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD << fieldName << "=" << defaultValue;
	}
}

