#include "Scenario.h"

char* SCENARIO_NODE = "escenario";
char* SCENARIO_LAYERS_NODE = "capas";
char* SCENARIO_ENTITIES_NODE = "entidades";

const char* MESSAGE_PARSING_SCENARIO_NODE = "Inicio de parseo de nodo escenario.";
const char* MESSAGE_END_PARSING_SCENARIO_NODE = "Fin de parseo de nodo escenario.";

const int SCENARIO_DEFAULT_WIDTH = 1920;
const int SCENARIO_DEFAULT_HEIGHT = 600;
const int SCENARIO_DEFAULT_RADIO = 0;

const string ENTITY_TYPE_RECTANGLE = "rectangulo";
const string ENTITY_TYPE_CIRCLE = "circulo";
const string ENTITY_TYPE_SQUARE = "cuadrado";

Scenario::Scenario()
{
}

Scenario::~Scenario() {
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		delete *it;
	}
}

void Scenario::SetDimensions(Dimensions dimensions)
{
	this->dimensions = dimensions;
}

void Scenario::SetLayers(vector<Layer> layers)
{
	this->layers = layers;
}

void Scenario::SetEntities(vector<Entity*> entities)
{
	this->entities = entities;
}

vector<Entity*> Scenario::GetEntities()
{
	return entities;
}

int Scenario::GetWidth()
{
	return dimensions.getWidth();
}

int Scenario::GetHeight()
{
	return dimensions.getHeight();
}

void Scenario::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_SCENARIO_NODE;

	dimensions.SetDefaults(SCENARIO_DEFAULT_WIDTH, SCENARIO_DEFAULT_HEIGHT, SCENARIO_DEFAULT_RADIO);
	dimensions.ParseObject(nodeRef);

	ParseCollection<Layer>(&layers, nodeRef, SCENARIO_LAYERS_NODE);

	vector<Entity> entities;
	ParseCollection<Entity>(&entities, nodeRef, SCENARIO_ENTITIES_NODE);
	
	this->entities.clear();
	for (vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		Entity entity = &(*it);
		Entity* toAdd = EntityResolver::Resolve(&entity);
		this->entities.push_back(toAdd);
	}
	
	LOG(logINFO) << MESSAGE_END_PARSING_SCENARIO_NODE;
}

char * Scenario::GetNodeName()
{
	return SCENARIO_NODE;
}

vector<Layer> Scenario::getLayers()
{
	return this->layers;
}