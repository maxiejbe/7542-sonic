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
