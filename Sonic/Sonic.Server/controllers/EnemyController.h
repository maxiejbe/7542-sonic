#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "entities/enemies/Enemy.h"
#include "entities/Camera.h"

class EnemyController
{
public:
	EnemyController();
	static void update(Enemy*, Camera *);
	//check if enemy is seen in the scenario
	static bool isEnemyVisible(Enemy*, Camera*);
private:
	static void moveCrab(Enemy*);
	static void horizontalMovement(Enemy*);
};
#endif // !ENEMYCONTROLLER_H
