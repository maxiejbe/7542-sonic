#include "EntityResolver.h"	

const string ENTITY_TYPE_RECTANGLE = "rectangulo";
const string ENTITY_TYPE_CIRCLE = "circulo";
const string ENTITY_TYPE_SQUARE = "cuadrado";

Entity* EntityResolver::Resolve(Entity* origin)
{
	Entity* destination = 0;
	if (origin->GetType() == ENTITY_TYPE_RECTANGLE) {
		destination = new Rectangle(origin);
	}
	else if (origin->GetType() == ENTITY_TYPE_CIRCLE) {
		destination = new Circle(origin);
	}
	else if (origin->GetType() == ENTITY_TYPE_SQUARE) {
		destination = new Square(origin);
	}
	return destination;
}

Dimensions EntityResolver::GetDefaultDimensions(Entity * entity)
{
	Dimensions dimensions;
	if (entity->GetType() == ENTITY_TYPE_RECTANGLE) {
		dimensions = Rectangle().GetDefaultDimensions();
	}
	else if (entity->GetType() == ENTITY_TYPE_CIRCLE) {
		dimensions = Circle().GetDefaultDimensions();
	}
	else if (entity->GetType() == ENTITY_TYPE_SQUARE) {
		dimensions = Square().GetDefaultDimensions();
	}
	return dimensions;
}

