#include "EntityResolver.h"	

Entity* EntityResolver::Resolve(Entity* origin)
{
	Entity* destination = nullptr;
	if (origin->GetType() == ToTypeString(EntityType::rectangle)) {
		destination = new Rectangle(origin);
	}
	else if (origin->GetType() == ToTypeString(EntityType::circle)) {
		destination = new Circle(origin);
	}
	else if (origin->GetType() == ToTypeString(EntityType::square)) {
		destination = new Square(origin);
	}
	return destination;
}

Dimensions EntityResolver::GetDefaultDimensions(Entity * entity)
{
	Dimensions dimensions;
	if (entity->GetType() == ToTypeString(EntityType::rectangle)) {
		dimensions = Rectangle().GetDefaultDimensions();
	}
	else if (entity->GetType() == ToTypeString(EntityType::circle)) {
		dimensions = Circle().GetDefaultDimensions();
	}
	else if (entity->GetType() == ToTypeString(EntityType::square)) {
		dimensions = Square().GetDefaultDimensions();
	}
	return dimensions;
}

EntityType EntityResolver::FromTypeString(string entityType)
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

string EntityResolver::ToTypeString(EntityType entityType)
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

EntityColor EntityResolver::FromColorString(string entityColor)
{
	if (entityColor == "rojo")
		return EntityColor::red;
	else if (entityColor == "amarillo")
		return EntityColor::yellow;
	else if (entityColor == "verde")
		return EntityColor::green;
	else
		return EntityColor::red;
}

string EntityResolver::ToColorString(EntityColor entityColor)
{
	switch (entityColor) {
	case EntityColor::red:
		return "rojo";
	case EntityColor::yellow:
		return "amarillo";
	case EntityColor::green:
		return "verde";
	default:
		return "";
	}
}
