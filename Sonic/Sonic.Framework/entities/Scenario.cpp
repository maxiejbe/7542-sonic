#include "Scenario.h"

char* SCENARIO_NODE = "escenario";
char* SCENARIO_LAYERS_NODE = "capas";
char* SCENARIO_ENTITIES_NODE = "entidades";

const char* MESSAGE_PARSING_SCENARIO_NODE = "Inicio de parseo de nodo escenario.";
const char* MESSAGE_END_PARSING_SCENARIO_NODE = "Fin de parseo de nodo escenario.";

const int SCENARIO_DEFAULT_WIDTH = 1920;
const int SCENARIO_DEFAULT_HEIGHT = 600;
const int SCENARIO_DEFAULT_RADIO = 0;

Scenario::Scenario()
{
}

Scenario::~Scenario() {
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		delete *it;
	}
}

void Scenario::setDimensions(Dimensions dimensions)
{
	this->dimensions = dimensions;
}

void Scenario::setLayers(vector<Layer> layers)
{
	this->layers = layers;
}

void Scenario::setEntities(vector<Entity*> entities)
{
	this->entities = entities;
}

vector<Entity*> Scenario::getEntities()
{
	return entities;
}

int Scenario::getWidth()
{
	return dimensions.getWidth();
}

int Scenario::getHeight()
{
	return dimensions.getHeight();
}

void Scenario::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_SCENARIO_NODE;

	dimensions.setDefaults(SCENARIO_DEFAULT_WIDTH, SCENARIO_DEFAULT_HEIGHT, SCENARIO_DEFAULT_RADIO);
	dimensions.parseObject(nodeRef);

	parseCollection<Layer>(&layers, nodeRef, SCENARIO_LAYERS_NODE);

	// Order layers by z-index
	sort(layers.begin(), layers.end());

	vector<Entity> entities;
	parseCollection<Entity>(&entities, nodeRef, SCENARIO_ENTITIES_NODE);

	// Order entities by z-index
	sort(entities.begin(), entities.end());
	
	this->entities.clear();
	for (vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		Entity entity = &(*it);
		Entity* toAdd = EntityResolver::resolve(&entity);
		if (entity.validate()) {
			this->entities.push_back(toAdd);
		}
	}
	
	LOG(logINFO) << MESSAGE_END_PARSING_SCENARIO_NODE;
}

char * Scenario::getNodeName()
{
	return SCENARIO_NODE;
}

vector<Layer> Scenario::getLayers()
{
	return this->layers;
}