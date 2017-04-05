#include "Entity.h"
#include "common/EntityResolver.h"

#include <iostream>

const char* ENTITY_NODE = "entidades";
const char* ENTITY_ID_NODE = "id";
const char* ENTITY_TYPE_NODE = "tipo";
const char* ENTITY_COLOR_NODE = "color";
const char* ENTITY_IMAGE_PATH_NODE = "ruta_imagen";
const char* ENTITY_ZINDEX_NODE = "index_z";

const char* MESSAGE_PARSING_ENTITY_NODE = "Inicio de parseo de nodo entidad.";
const char* MESSAGE_END_PARSING_ENTITY_NODE = "Fin de parseo de nodo entidad.";

const int ENTITY_DEFAULT_ID = 0;
const string ENTITY_DEFAULT_TYPE = "";
const string ENTITY_DEFAULT_COLOR = "";
const int ENTITY_DEFAULT_WIDTH = 0;
const int ENTITY_DEFAULT_HEIGHT = 0;
const int ENTITY_DEFAULT_RADIO = 0;
const string ENTITY_DEFAULT_IMAGE_PATH = "";
const int ENTITY_DEFAULT_ZINDEX = 0;

Entity::Entity()
{
}

Entity::Entity(Entity* entity)
{
	this->id = entity->id;
	this->type = entity->type;
	this->color = entity->color;
	this->dimensions = entity->dimensions;
	this->coordinate = entity->coordinate;
	this->imagePath = entity->imagePath;
	this->zIndex = entity->zIndex;
}

void Entity::draw(SDL_Rect camera)
{
}

string Entity::GetType()
{
	return type;
}

void Entity::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = GetNodeName();

	LOG(logINFO) << MESSAGE_PARSING_ENTITY_NODE;

	ParseInt(&id, ENTITY_DEFAULT_ID, nodeRef, ENTITY_ID_NODE);

	ParseString(&type, ENTITY_DEFAULT_TYPE, nodeRef, ENTITY_TYPE_NODE);

	dimensions.SetDefaults(ENTITY_DEFAULT_WIDTH, ENTITY_DEFAULT_HEIGHT, ENTITY_DEFAULT_RADIO);
	dimensions.ParseObject(nodeRef);

	string colorJson;
	ParseString(&colorJson, ENTITY_DEFAULT_COLOR, nodeRef, ENTITY_COLOR_NODE);
	SetColor(colorJson);

	coordinate.ParseObject(nodeRef);

	ParseString(&imagePath, ENTITY_DEFAULT_IMAGE_PATH, nodeRef, ENTITY_IMAGE_PATH_NODE);

	ParseInt(&zIndex, ENTITY_DEFAULT_ZINDEX, nodeRef, ENTITY_ZINDEX_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_ENTITY_NODE;
}

char* Entity::GetNodeName()
{
	return nullptr;
}

void Entity::SetColor(string color)
{
	Color colorObj = Color(color);
	this->color = colorObj;
}