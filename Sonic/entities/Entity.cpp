#include "Entity.h"

const char* ENTITY_NODE = "entidades";
const char* ENTITY_ID_NODE = "id";
const char* ENTITY_TYPE_NODE = "tipo";
const char* ENTITY_COLOR_NODE = "color";
const char* ENTITY_IMAGE_PATH_NODE = "ruta_imagen";
const char* ENTITY_ZINDEX_NODE = "index_z";

Entity::Entity()
{
}

void Entity::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = GetNodeName();

	if (node.HasMember(ENTITY_ID_NODE) && node[ENTITY_ID_NODE].IsInt()) {
		id = node[ENTITY_ID_NODE].GetInt();
	}

	if (node.HasMember(ENTITY_TYPE_NODE) && node[ENTITY_TYPE_NODE].IsString()) {
		type = node[ENTITY_TYPE_NODE].GetString();
	}

	if (node.HasMember(ENTITY_COLOR_NODE) && node[ENTITY_COLOR_NODE].IsString()) {
		color = node[ENTITY_COLOR_NODE].GetString();
	}

	dimensions.ParseObject(nodeRef);
	coordinate.ParseObject(nodeRef);

	if (node.HasMember(ENTITY_IMAGE_PATH_NODE) && node[ENTITY_IMAGE_PATH_NODE].IsString()) {
		imagePath = node[ENTITY_IMAGE_PATH_NODE].GetString();
	}

	if (node.HasMember(ENTITY_ZINDEX_NODE) && node[ENTITY_ZINDEX_NODE].IsInt()) {
		zIndex = node[ENTITY_ZINDEX_NODE].GetInt();
	}
}

char * Entity::GetNodeName()
{
	return nullptr;
}

void Entity::draw(SDL_Rect camera) {
}