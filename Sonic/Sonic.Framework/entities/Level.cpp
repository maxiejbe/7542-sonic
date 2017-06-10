#include "Level.h"

char* LEVEL_SCENARIO_NODE = "escenario";
char* LEVEL_LIMITS_NODE = "limites";

const char* MESSAGE_PARSING_LEVEL_NODE = "Inicio de parseo de nodo escenario.";
const char* MESSAGE_END_PARSING_LEVEL_NODE = "Fin de parseo de nodo escenario.";

Level::Level()
{
}

Level::~Level()
{
}

vector<EntityLimit> Level::getLimits()
{
	return this->limits;
}

Scenario Level::getScenario()
{
	return this->scenario;
}

void Level::setEntities(vector<Entity*> entities)
{
	this->scenario.setEntities(entities);
}

void Level::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	LOG(logINFO) << MESSAGE_PARSING_LEVEL_NODE;

	scenario.parseObject(nodeRef);

	parseCollection<EntityLimit>(&limits, nodeRef, LEVEL_LIMITS_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_LEVEL_NODE;
}

char * Level::getNodeName()
{
	return nullptr;
}
