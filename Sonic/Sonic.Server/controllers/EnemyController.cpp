#include "EnemyController.h"

EnemyController::EnemyController()
{
}

void EnemyController::update(Enemy * enemy, Camera * camera)
{
	//if enemy is out of screen don't update
	if (!isEnemyVisible(enemy, camera)) return;

	switch (enemy->getType()) {
	case crab:
		moveCrab(enemy);
		break;
	}
}

bool EnemyController::isEnemyVisible(Enemy * enemy, Camera * camera)
{
	return (enemy->getPosition().x >= camera->getPosition().x && enemy->getPosition().x <= (camera->getPosition().x + camera->getScreenWidth() - enemy->getWidth()));
}

void EnemyController::moveCrab(Enemy * enemy)
{
	horizontalMovement(enemy);
	//if reached max distance change direction
	if (enemy->getDistanceTravelled() >= enemy->getMaxDistance()) {
		FacingDirection newDirection = (enemy->getFacingDirection() == FACING_LEFT) ? FACING_RIGHT : FACING_LEFT;
		enemy->setFacingDirection(newDirection);
	}
}

void EnemyController::horizontalMovement(Enemy * enemy)
{
	if (enemy->getFacingDirection() == FACING_LEFT) {
		enemy->setPositionX(enemy->getPosition().x - enemy->getVelocity().x);
	}else if (enemy->getFacingDirection() == FACING_RIGHT) {
		enemy->setPositionX(enemy->getPosition().x + enemy->getVelocity().x);
	}

	enemy->incrementDistanceTravelled(enemy->getVelocity().x);
}



