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

Dimensions Entity::GetDefaultDimensions()
{
	return Dimensions();
}

Uint32 Entity::GetColorRgba()
{
	int full = 255; //Full of one color
	int r = 0;
	int g = 0;
	int b = 0;

	switch (EntityResolver::FromColorString(color))
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

string Entity::GetType()
{
	return type;
}

void Entity::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = GetNodeName();

	LOG(logINFO) << MESSAGE_PARSING_ENTITY_NODE;

	ParseInt(&id, ENTITY_DEFAULT_ID, nodeRef, ENTITY_ID_NODE, Validator::IntGreaterThanZero);
	
	ParseString(&type, ENTITY_DEFAULT_TYPE, nodeRef, ENTITY_TYPE_NODE);
	type = EntityResolver::ToTypeString(EntityResolver::FromTypeString(type));

	Dimensions defaultDimensions = EntityResolver::GetDefaultDimensions(this);
	dimensions.SetDefaults(defaultDimensions.getWidth(), defaultDimensions.getHeight(), defaultDimensions.getRadio());
	dimensions.ParseObject(nodeRef);

	ParseString(&color, ENTITY_DEFAULT_COLOR, nodeRef, ENTITY_COLOR_NODE);
	color = EntityResolver::ToColorString(EntityResolver::FromColorString(color));

	coordinate.ParseObject(nodeRef);

	ParseString(&imagePath, ENTITY_DEFAULT_IMAGE_PATH, nodeRef, ENTITY_IMAGE_PATH_NODE);

	ParseInt(&zIndex, ENTITY_DEFAULT_ZINDEX, nodeRef, ENTITY_ZINDEX_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_ENTITY_NODE;
}

char* Entity::GetNodeName()
{
	return nullptr;
}
