#include "EntityLimit.h"

const char* ENTITY_LIMIT_TYPE_NODE = "tipo";
const char* ENTITY_LIMIT_MIN_COUNT_NODE = "cantidad_minima";
const char* ENTITY_LIMIT_MAX_COUNT_NODE = "cantidad_maxima";

const char* ENTITY_LIMIT_MIN_X_NODE = "min_x";
const char* ENTITY_LIMIT_MAX_X_NODE = "max_x";
const char* ENTITY_LIMIT_MIN_Y_NODE = "min_y";
const char* ENTITY_LIMIT_MAX_Y_NODE = "max_y";

const char* MESSAGE_PARSING_ENTITY_LIMIT_NODE = "Inicio de parseo de nodo limites de entidades.";
const char* MESSAGE_END_PARSING_ENTITY_LIMIT_NODE = "Fin de parseo de nodo limites de entidades.";

const int ENTITY_LIMIT_DEFAULT_MIN_COUNT = 0;
const string ENTITY_LIMIT_DEFAULT_TYPE = "anillo";
const int ENTITY_LIMIT_DEFAULT_MAX_COUNT = 0;

const int ENTITY_LIMIT_DEFAULT_MIN_X = 0;
const int ENTITY_LIMIT_DEFAULT_MAX_X = 0;
const int ENTITY_LIMIT_DEFAULT_MIN_Y = 0;
const int ENTITY_LIMIT_DEFAULT_MAX_Y = 0;

EntityLimit::EntityLimit()
{
}

string EntityLimit::getType()
{
	return this->type;
}

int EntityLimit::getMinCount()
{
	return this->minCount;
}

int EntityLimit::getMaxCount()
{
	return this->maxCount;
}

int EntityLimit::getMinX()
{
	return this->minX;
}

int EntityLimit::getMaxX()
{
	return this->maxX;
}

int EntityLimit::getMinY()
{
	return this->minY;
}

int EntityLimit::getMaxY()
{
	return this->maxY;
}

void EntityLimit::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_ENTITY_LIMIT_NODE;

	parseString(&type, ENTITY_LIMIT_DEFAULT_TYPE, nodeRef, ENTITY_LIMIT_TYPE_NODE);

	parseInt(&minCount, ENTITY_LIMIT_DEFAULT_MIN_COUNT, nodeRef, ENTITY_LIMIT_MIN_COUNT_NODE);

	parseInt(&maxCount, ENTITY_LIMIT_DEFAULT_MAX_COUNT, nodeRef, ENTITY_LIMIT_MAX_COUNT_NODE, Validator::intGreaterThanZero);


	parseInt(&minX, ENTITY_LIMIT_DEFAULT_MIN_X, nodeRef, ENTITY_LIMIT_MIN_X_NODE, Validator::intGreaterThanZero);
	
	parseInt(&maxX, ENTITY_LIMIT_DEFAULT_MAX_X, nodeRef, ENTITY_LIMIT_MAX_X_NODE, Validator::intGreaterThanZero);
	
	parseInt(&minY, ENTITY_LIMIT_DEFAULT_MIN_Y, nodeRef, ENTITY_LIMIT_MIN_Y_NODE, Validator::intGreaterThanZero);

	parseInt(&maxY, ENTITY_LIMIT_DEFAULT_MAX_Y, nodeRef, ENTITY_LIMIT_MAX_Y_NODE, Validator::intGreaterThanZero);


	LOG(logINFO) << MESSAGE_END_PARSING_ENTITY_LIMIT_NODE;
}

char* EntityLimit::getNodeName()
{
	return nullptr;
}