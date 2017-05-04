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

const char* ERROR_ENTITY_NO_TYPE = "No puede dibujarse la entidad ya que no tiene un tipo válido.";
const char* ERROR_ENTITY_NO_COORDINATE_X = "No puede dibujarse la entidad ya que no tiene coordenada X válida.";
const char* ERROR_ENTITY_NO_COORDINATE_Y = "No puede dibujarse la entidad ya que no tiene coordenada Y válida.";

const int ENTITY_DEFAULT_ID = 1;
const string ENTITY_DEFAULT_TYPE = "";
const string ENTITY_DEFAULT_COLOR = "";
const string ENTITY_DEFAULT_IMAGE_PATH = ""; // Vacio = no hay imagen (solo color)
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

bool Entity::validate()
{
	if (type.empty()) 
	{
		LOG(logERROR) << ERROR_ENTITY_NO_TYPE;
		return false;
	}

	if (coordinate.getX() < 0) {
		LOG(logERROR) << ERROR_ENTITY_NO_COORDINATE_X;
		return false;
	}
	if (coordinate.getY() < 0)
	{
		LOG(logERROR) << ERROR_ENTITY_NO_COORDINATE_Y;
		return false;
	}
	return true;
}

Dimensions Entity::getDefaultDimensions()
{
	return Dimensions();
}

string Entity::getType()
{
	return type;
}

string Entity::getColor()
{
	return color;
}

void Entity::setImagePath(string imagePath)
{
	this->imagePath = imagePath;
}

string Entity::getImagePath()
{
	return color;
}

Coordinate Entity::getCoordinate()
{
	return coordinate;
}

Dimensions Entity::getDimensions()
{
	return dimensions;
}

void Entity::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = getNodeName();

	LOG(logINFO) << MESSAGE_PARSING_ENTITY_NODE;

	parseInt(&id, ENTITY_DEFAULT_ID, nodeRef, ENTITY_ID_NODE, Validator::intGreaterThanZero);
	
	parseString(&type, ENTITY_DEFAULT_TYPE, nodeRef, ENTITY_TYPE_NODE);
	type = EntityResolver::toTypeString(EntityResolver::fromTypeString(type));

	Dimensions defaultDimensions = EntityResolver::getDefaultDimensions(this);
	dimensions.setDefaults(defaultDimensions.getWidth(), defaultDimensions.getHeight(), defaultDimensions.getRadio());
	dimensions.parseObject(nodeRef);

	parseString(&color, ENTITY_DEFAULT_COLOR, nodeRef, ENTITY_COLOR_NODE);
	color = EntityResolver::toColorString(EntityResolver::fromColorString(color));

	coordinate.parseObject(nodeRef);

	parseString(&imagePath, ENTITY_DEFAULT_IMAGE_PATH, nodeRef, ENTITY_IMAGE_PATH_NODE);

	parseInt(&zIndex, ENTITY_DEFAULT_ZINDEX, nodeRef, ENTITY_ZINDEX_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_ENTITY_NODE;
}

char* Entity::getNodeName()
{
	return nullptr;
}
