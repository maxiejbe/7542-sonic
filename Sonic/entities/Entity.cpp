#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(int idParam, string typeParam, string colorParam, Dimensions dimensionsParam, Coordinate coordinateParam, string imagePathParam, int zIndexParam)
{
	id = idParam;
	type = typeParam;
	color = colorParam;
	dimensions = dimensionsParam;
	coordinate = coordinateParam;
	imagePath = imagePathParam;
	zIndex = zIndexParam;
}

void Entity::draw() {
}