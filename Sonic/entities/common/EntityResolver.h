#ifndef I_ENTITY_RESOLVER_H
#define I_ENTITY_RESOLVER_H

#include "../Rectangle.h"
#include "../Circle.h"
#include "../Square.h"
#include "../Dimensions.h"
#include <string>

enum EntityType { rectangle, circle, square, null };

enum EntityColor {  red, yellow, green };

class EntityResolver {
public: 
	static Entity* Resolve(Entity* origin);
	static Dimensions GetDefaultDimensions(Entity* entity);

	static EntityType FromTypeString(string entityType);
	static string ToTypeString(EntityType entityType);

	static EntityColor FromColorString(string entityColor);
	static string ToColorString(EntityColor entityColor);
};
#endif
