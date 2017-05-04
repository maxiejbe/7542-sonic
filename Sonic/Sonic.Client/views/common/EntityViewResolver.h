#ifndef I_ENTITY_VIEW_RESOLVER_H
#define I_ENTITY_VIEW_RESOLVER_H

#include "../RectangleView.h"
#include "../CircleView.h"
#include "../SquareView.h"
#include "entities/Entity.h"
#include <string>

class EntityViewResolver {
public:
	static EntityView* resolve(Entity* origin);
};
#endif