#include "EntityResolver.h"
#include "EntityResolver.h"	

const char* ENTITYRESOLVER_ENTITY_TYPE_NODE = "tipo";

Entity * EntityResolver::resolve(string entityType)
{
	Entity* destination = nullptr;

	if ((entityType == toTypeString(EntityType::enemigo_cangrejo)) ||
		(entityType == toTypeString(EntityType::enemigo_mosca)) ||
		(entityType == toTypeString(EntityType::enemigo_pez))) {
		destination = new Enemy(entityType);
	}
	return destination;
}

Entity * EntityResolver::parse(Value* nodeRef)
{
	Value& node = *nodeRef;
	if (nodeRef == nullptr || !node.HasMember(ENTITYRESOLVER_ENTITY_TYPE_NODE)) return nullptr;

	const Value& entityType = node[ENTITYRESOLVER_ENTITY_TYPE_NODE];

	if (!entityType.IsString()) return nullptr;

	Entity* entity = resolve(string(entityType.GetString()));
	entity->unserialize(nodeRef);
	return entity;
}

Dimensions EntityResolver::getDefaultDimensions(Entity * entity)
{
	Dimensions dimensions;
	/*if (entity->getType() == toTypeString(EntityType::rectangle)) {
		dimensions = Rectangle().getDefaultDimensions();
	}
	else if (entity->getType() == toTypeString(EntityType::circle)) {
		dimensions = Circle().getDefaultDimensions();
	}
	else if (entity->getType() == toTypeString(EntityType::square)) {
		dimensions = Square().getDefaultDimensions();
	}*/
	return dimensions;
}

EntityType EntityResolver::fromTypeString(string entityType)
{
	if (entityType == "enemigo_cangrejo")
		return EntityType::enemigo_cangrejo;
	else if (entityType == "enemigo_pez")
		return EntityType::enemigo_pez;
	else if (entityType == "enemigo_mosca")
		return EntityType::enemigo_mosca;
	else
		return EntityType::null;
}

string EntityResolver::toTypeString(EntityType entityType)
{
	switch (entityType) {
		case EntityType::enemigo_cangrejo:
			return "enemigo_cangrejo";
		case EntityType::enemigo_pez:
			return "enemigo_pez";
		case EntityType::enemigo_mosca:
			return "enemigo_mosca";
		default:
			return "";
	}
}

EntityColor EntityResolver::fromColorString(string entityColor)
{
	if (entityColor == "rojo")
		return EntityColor::red;
	else if (entityColor == "amarillo")
		return EntityColor::yellow;
	else if (entityColor == "verde")
		return EntityColor::green;
	else if (entityColor == "azul")
		return EntityColor::blue;
	else
		return EntityColor::red;
}

string EntityResolver::toColorString(EntityColor entityColor)
{
	switch (entityColor) {
	case EntityColor::red:
		return "rojo";
	case EntityColor::yellow:
		return "amarillo";
	case EntityColor::green:
		return "verde";
	case EntityColor::blue:
		return "azul";
	default:
		return "";
	}
}
