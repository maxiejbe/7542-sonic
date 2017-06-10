#ifndef I_ENTITY_VIEW_RESOLVER_H
#define I_ENTITY_VIEW_RESOLVER_H

#include "../EntityView.h"
#include "../ObstacleView.h"
#include "../BonusView.h"
#include "../EnemyView.h"
#include "../RingView.h"
#include "entities/Entity.h"
#include <string>

class EntityViewResolver {
public:
	static EntityView* resolve(Entity* origin);
};
#endif