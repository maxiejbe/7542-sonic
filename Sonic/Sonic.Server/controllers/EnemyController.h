#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "entities/enemies/Enemy.h"
#include "entities/Camera.h"
#include "entities/common/EntityResolver.h"

class EnemyController
{
public:
	EnemyController();
	static void update(Enemy * enemy, int milliseconds);
private:
	static void move(Enemy * enemy);
	static void horizontalMovement(Enemy*, double velocityX);
	static void verticalMovement(Enemy*, double velocityX);
	static void checkRecovering(Enemy* enemy, int ms);
	static int resetCounter;
	
};
#endif // !ENEMYCONTROLLER_H

