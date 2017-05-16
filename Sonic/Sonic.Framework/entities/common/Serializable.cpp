#include "Serializable.h"	

const char* MESSAGE_PARSING_NODE_FIELD = "Buscando campo: ";
const char* MESSAGE_OK_PARSING_NODE_FIELD = "Valor procesado correctamente: ";

const char* MESSAGE_ERROR_PARSING_NODE_FIELD_EMPTY = "No se encontró el campo ";
const char* MESSAGE_ERROR_PARSING_NODE_FIELD_INCORRECT = "Es incorrecto el valor del campo ";
const char* MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT = ". Tomando por default el valor: ";

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
	Value* node = nullptr;

	if (parentNodeRef == nullptr || !parentNode.HasMember(nodeName)) {
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_INNER_NODE << nodeName << ".";
		//return;
	}
	else {
		node = &parentNode[nodeName];
		if (!node->IsObject()) {
			LOG(logWARNING) << MESSAGE_ERROR_NOT_AN_OBJECT_INNER_NODE << ": " << nodeName;
			//return;
		}
	}

	unserialize(node);
}

void Serializable::parseCurrentObject(Value* nodeRef)
{
	Value& node = *nodeRef;
	if (!node.IsObject()) {
		LOG(logWARNING) << MESSAGE_ERROR_NOT_AN_OBJECT_INNER_NODE;
		//return;
	}

	unserialize(&node);
}

void Serializable::parseInt(int * value, int defaultValue, Value * nodeRef, const char* fieldName, function<bool(int)> condition)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(fieldName)) {
		*value = defaultValue;
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_EMPTY << fieldName << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		return;
	}

	string childNodeValue = getNodeContent(&node[fieldName]);
	if (!node[fieldName].IsInt() || !(condition != NULL && condition(node[fieldName].GetInt()) || condition == NULL)) {
		*value = defaultValue;
		LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_INCORRECT << fieldName << "=" << childNodeValue << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		return;
	}

	*value = node[fieldName].GetInt();
	LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD << to_string(*value);
}

void Serializable::parseString(string * value, string defaultValue, Value * nodeRef, const char* fieldName)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(fieldName)) {
		if (*value != defaultValue) {
			*value = defaultValue;
			LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_EMPTY << fieldName << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		}
		return;
	}

	string childNodeValue = getNodeContent(&node[fieldName]);
	if (!node[fieldName].IsString()) {
		if (*value != defaultValue) {
			*value = defaultValue;
			LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_INCORRECT << fieldName << "=" << childNodeValue << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		}
		return;
	}

	*value = node[fieldName].GetString();
	LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD << *value;
}

void Serializable::parseDouble(double * value, double defaultValue, Value * nodeRef, const char * fieldName)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(fieldName)) {
		if (*value != defaultValue) {
			*value = defaultValue;
			LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_EMPTY << fieldName << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		}
		return;
	}

	string childNodeValue = getNodeContent(&node[fieldName]);
	if (!node[fieldName].IsDouble()) {
		if (*value != defaultValue) {
			*value = defaultValue;
			LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_INCORRECT << fieldName << "=" << childNodeValue << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		}
		return;
	}

	*value = node[fieldName].GetDouble();
	LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD << *value;
}

void Serializable::parseBool(bool * value, bool defaultValue, Value * nodeRef, const char * fieldName)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(fieldName)) {
		if (*value != defaultValue) {
			*value = defaultValue;
			LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_EMPTY << fieldName << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		}
		return;
	}

	string childNodeValue = getNodeContent(&node[fieldName]);
	if (!node[fieldName].IsBool()) {
		if (*value != defaultValue) {
			*value = defaultValue;
			LOG(logWARNING) << MESSAGE_ERROR_PARSING_NODE_FIELD_INCORRECT << fieldName << "=" << childNodeValue << MESSAGE_ERROR_PARSING_NODE_FIELD_DEFAULT << defaultValue;
		}
		return;
	}

	*value = node[fieldName].GetBool();
	LOG(logINFO) << MESSAGE_OK_PARSING_NODE_FIELD << *value;
}


string Serializable::getNodeContent(Value * nodeRef)
{
	Value& node = *nodeRef;
	StringBuffer sb;
	Writer<StringBuffer> writer(sb);
	node.Accept(writer);
	return sb.GetString();
}

string Serializable::serialize()
{
	return string();
}

