#ifndef I_ENTITY_RESOLVER_H
#define I_ENTITY_RESOLVER_H

#include "../Rectangle.h"
#include "../Circle.h"
#include "../Square.h"
#include "../Dimensions.h"
#include <string>

enum EntityType { rectangle, circle, square, null };

enum EntityColor {  red, yellow, green, blue };

class EntityResolver {
public: 
	static Entity* resolve(Entity* origin);
	static Dimensions getDefaultDimensions(Entity* entity);

	static EntityType fromTypeString(string entityType);
	static string toTypeString(EntityType entityType);

	static EntityColor fromColorString(string entityColor);
	static string toColorString(EntityColor entityColor);
};
#endif
