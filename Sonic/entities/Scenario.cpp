#include "Scenario.h"

char* SCENARIO_NODE = "escenario";
char* SCENARIO_LAYERS_NODE = "capas";
char* SCENARIO_ENTITIES_NODE = "entidades";

Scenario::Scenario()
{
}

void Scenario::SetDimensions(Dimensions dimensions)
{
	this->dimensions = dimensions;
}

void Scenario::SetLayers(vector<Layer> layers)
{
	this->layers = layers;
}

void Scenario::SetEntities(vector<Entity> entities)
{
	this->entities = entities;
}

int Scenario::GetWidth()
{
	return dimensions.GetWidth();
}

int Scenario::GetHeight()
{
	return dimensions.GetHeight();
}

void Scenario::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	dimensions.ParseObject(nodeRef);

	ParseCollection<Layer>(&layers, nodeRef, SCENARIO_LAYERS_NODE);

	ParseCollection<Entity>(&entities, nodeRef, SCENARIO_ENTITIES_NODE);
}

char * Scenario::GetNodeName()
{
	return SCENARIO_NODE;
}
