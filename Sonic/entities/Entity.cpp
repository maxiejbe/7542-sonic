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
	this->imageCrop = true;
	if (this->imagePath == ENTITY_DEFAULT_IMAGE_PATH) {
		this->imageCrop = false;
	}
	this->zIndex = entity->zIndex;
}

void Entity::draw(SDL_Rect camera)
{
}

bool Entity::validate()
{
	if (type.empty()) return false;
	if (coordinate.getX() < 0) return false;
	if (coordinate.getY() < 0) return false;
	return true;
}

Dimensions Entity::getDefaultDimensions()
{
	return Dimensions();
}

Uint32 Entity::getColorRgba()
{
	int full = 255; //Full of one color
	int r = 0;
	int g = 0;
	int b = 0;

	switch (EntityResolver::fromColorString(color))
	{
		case EntityColor::red:
			r = full;
			break;
		case EntityColor::yellow:
			r = full;
			g = full;
			break;
		case EntityColor::green:
			g = full;
			break;
		case EntityColor::blue:
			b = full;
			break;
		default:
			return Uint32();
			break;
	}

	Uint32 colorCode = 0;
	if (SDLWindow::getInstance().gWindow != NULL) {
		colorCode = SDL_MapRGBA(SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, r, g, b, 255);
	}
	else {
		LOG(logERROR) << "No se puede recuperar el color en formato Uint32 - Error: La ventana es nula";
	}

	return colorCode;
}

string Entity::getType()
{
	return type;
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
