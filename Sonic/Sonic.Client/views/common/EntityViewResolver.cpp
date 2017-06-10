#include "EntityViewResolver.h"

EntityView * EntityViewResolver::resolve(Entity * origin)
{
	EntityView* destination = nullptr;
	/*if (origin->getType() == EntityResolver::toTypeString(EntityType::rectangle)) {
		destination = new RectangleView(origin);
	}
	else if (origin->getType() == EntityResolver::toTypeString(EntityType::circle)) {
		destination = new CircleView(origin);
	}
	else if (origin->getType() == EntityResolver::toTypeString(EntityType::square)) {
		destination = new SquareView(origin);
	}*/
	return destination;
}
