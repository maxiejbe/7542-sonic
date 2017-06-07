#include "EntityLimit.h"

const char* ENTITY_LIMIT_MIN_COUNT_NODE = "id";
const char* ENTITY_LIMIT_MAX_COUNT_NODE = "index_z";

const char* MESSAGE_PARSING_ENTITY_LIMIT_NODE = "Inicio de parseo de nodo limites de entidades.";
const char* MESSAGE_END_PARSING_ENTITY_LIMIT_NODE = "Fin de parseo de nodo limites de entidades.";

const int ENTITY_LIMIT_DEFAULT_MIN_COUNT = 0;
const int ENTITY_LIMIT_DEFAULT_MAX_COUNT = 0;

EntityLimit::EntityLimit()
{
}

void EntityLimit::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_ENTITY_LIMIT_NODE;

	parseInt(&minCount, ENTITY_LIMIT_DEFAULT_MIN_COUNT, nodeRef, ENTITY_LIMIT_DEFAULT_MIN_COUNT);

	parseInt(&maxCount, ENTITY_LIMIT_DEFAULT_MAX_COUNT, nodeRef, ENTITY_LIMIT_DEFAULT_MIN_COUNT, Validator::intGreaterThanZero);

	LOG(logINFO) << MESSAGE_END_PARSING_ENTITY_LIMIT_NODE;
}

char* EntityLimit::getNodeName()
{
	return nullptr;
}