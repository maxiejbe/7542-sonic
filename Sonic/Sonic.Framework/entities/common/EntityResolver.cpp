#include "EntityResolver.h"
#include "EntityResolver.h"	

Entity* EntityResolver::resolve(Entity* origin)
{
	Entity* destination = nullptr;

	/*if (origin->getType() == toTypeString(EntityType::rectangle)) {
		destination = new Rectangle(origin);
	}
	else if (origin->getType() == toTypeString(EntityType::circle)) {
		destination = new Circle(origin);
	}
	else if (origin->getType() == toTypeString(EntityType::square)) {
		destination = new Square(origin);
	}*/

	if ((origin->getType() == toTypeString(EntityType::enemigo_cangrejo)) || 
		(origin->getType() == toTypeString(EntityType::enemigo_mosca)) || 
		(origin->getType() == toTypeString(EntityType::enemigo_pez))) {
		destination = new Enemy(origin->getType());
	}

	return destination;
}

Entity * EntityResolver::resolve(string entityType)
{
	Entity entity;
	entity.setType(entityType);
	return resolve(&entity);
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
