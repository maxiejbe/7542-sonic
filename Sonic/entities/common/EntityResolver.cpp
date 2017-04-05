#include "EntityResolver.h"	

Entity* EntityResolver::resolve(Entity* origin)
{
	Entity* destination = nullptr;
	if (origin->getType() == toTypeString(EntityType::rectangle)) {
		destination = new Rectangle(origin);
	}
	else if (origin->getType() == toTypeString(EntityType::circle)) {
		destination = new Circle(origin);
	}
	else if (origin->getType() == toTypeString(EntityType::square)) {
		destination = new Square(origin);
	}
	return destination;
}

Dimensions EntityResolver::getDefaultDimensions(Entity * entity)
{
	Dimensions dimensions;
	if (entity->getType() == toTypeString(EntityType::rectangle)) {
		dimensions = Rectangle().getDefaultDimensions();
	}
	else if (entity->getType() == toTypeString(EntityType::circle)) {
		dimensions = Circle().getDefaultDimensions();
	}
	else if (entity->getType() == toTypeString(EntityType::square)) {
		dimensions = Square().getDefaultDimensions();
	}
	return dimensions;
}

EntityType EntityResolver::fromTypeString(string entityType)
{
	if (entityType == "rectangulo")
		return EntityType::rectangle;
	else if (entityType == "cuadrado")
		return EntityType::square;
	else if (entityType == "circulo")
		return EntityType::circle;
	else
		return EntityType::null;
}

string EntityResolver::toTypeString(EntityType entityType)
{
	switch (entityType) {
		case EntityType::rectangle:
			return "rectangulo";
		case EntityType::square:
			return "cuadrado";
		case EntityType::circle:
			return "circulo";
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
