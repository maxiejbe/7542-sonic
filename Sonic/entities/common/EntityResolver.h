#ifndef I_ENTITY_RESOLVER_H
#define I_ENTITY_RESOLVER_H

#include "../Rectangle.h"
#include "../Circle.h"
#include "../Square.h"
#include "../Dimensions.h"

class EntityResolver {
public: 
	static Entity* Resolve(Entity* origin);
	static Dimensions GetDefaultDimensions(Entity* entity);
};
#endif
