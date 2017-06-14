#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "entities/enemies/Enemy.h"
#include "entities/Camera.h"
#include "entities/common/EntityResolver.h"

class EnemyController
{
public:
	EnemyController();
	static void update(Enemy * enemy, Camera * camera, int milliseconds);
	//check if enemy is seen in the scenario
	static bool isEnemyVisible(Enemy*, Camera*);
private:
	static void EnemyController::move(Enemy * enemy);
	static void horizontalMovement(Enemy*, double velocityX);
	static void verticalMovement(Enemy*, double velocityX);
};
#endif // !ENEMYCONTROLLER_H

