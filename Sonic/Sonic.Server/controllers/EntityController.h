#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include "entities/Entity.h"
#include "entities/Camera.h"

class EntityController
{
public:
	//check if enemy is seen in the scenario
	static bool isEntityVisible(Entity*, Camera*);
};
#endif // !ENTITYCONTROLLER_H


