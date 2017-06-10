#include "EnemyController.h"

EnemyController::EnemyController()
{
}

void EnemyController::update(Enemy * enemy, Camera * camera)
{
	//if enemy is out of screen don't update
	if (!isEnemyVisible(enemy, camera)) return;

	/*switch (enemy->getType()) {
	case crab:
		moveCrab(enemy);
		break;
	}*/
}

bool EnemyController::isEnemyVisible(Enemy * enemy, Camera * camera)
{
	return (enemy->getCoordinate().getX() >= camera->getPosition().x && enemy->getCoordinate().getX() <= (camera->getPosition().x + camera->getScreenWidth() - enemy->getDimensions().getWidth()));
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
	Coordinate newEnemyCoordinate;
	Coordinate enemyCoordinate = enemy->getCoordinate();
	if (enemy->getFacingDirection() == FACING_LEFT) {
		newEnemyCoordinate = Coordinate(enemyCoordinate.getX() - enemy->getVelocity().x, enemyCoordinate.getY());
	}else if (enemy->getFacingDirection() == FACING_RIGHT) {
		newEnemyCoordinate = Coordinate(enemyCoordinate.getX() + enemy->getVelocity().x, enemyCoordinate.getY());
	}

	enemy->setCoordinate(newEnemyCoordinate);
	enemy->incrementDistanceTravelled(enemy->getVelocity().x);
}



