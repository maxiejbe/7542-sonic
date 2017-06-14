#include "EnemyController.h"

EnemyController::EnemyController()
{
}

void EnemyController::update(Enemy * enemy, Camera * camera, int milliseconds)
{
	//if enemy is out of screen don't update
	if (!isEnemyVisible(enemy, camera)) return;

	enemy->lock();

	enemy->setTime(milliseconds);

	switch (EntityResolver::fromTypeString(enemy->getType())) {
	case enemigo_cangrejo:
		moveCrab(enemy);
		break;
	case enemigo_pez:
		moveFish(enemy);
		break;
	case enemigo_mosca:
		break;
	}

	enemy->unlock();
}

bool EnemyController::isEnemyVisible(Enemy * enemy, Camera * camera)
{
	return (enemy->getCoordinate().getX() >= camera->getPosition().x && enemy->getCoordinate().getX() <= (camera->getPosition().x + camera->getScreenWidth() - enemy->getDimensions().getWidth()));
}

void EnemyController::moveCrab(Enemy * enemy)
{
	if (abs(enemy->getVelocity().x) > 100) {
		enemy->setVelocity(Vector2(0, 0));
	}

	horizontalMovement(enemy);

	//if reached max distance change direction
	if (enemy->getDistanceTravelled() >= enemy->getMaxDistance()) {
		FacingDirection newDirection = (enemy->getFacingDirection() == FACING_LEFT) ? FACING_RIGHT : FACING_LEFT;
		enemy->setFacingDirection(newDirection);
		enemy->resetDistanceTravelled();
	}
}

void EnemyController::moveFish(Enemy * enemy)
{
	if (abs(enemy->getVelocity().y) > 100) {
		enemy->setVelocity(Vector2(0, 0));
	}

	verticalMovement(enemy);

	//if reached max distance change direction
	if (enemy->getDistanceTravelled() >= enemy->getMaxDistance()) {
		FacingDirection newDirection = (enemy->getFacingDirection() == FACING_LEFT) ? FACING_RIGHT : FACING_LEFT;
		enemy->setFacingDirection(newDirection);
		enemy->resetDistanceTravelled();
	}
}

void EnemyController::horizontalMovement(Enemy * enemy)
{
	enemy->setVelocity(Vector2(0.01, 0));
	Coordinate newEnemyCoordinate;
	Coordinate enemyCoordinate = enemy->getCoordinate();
	if (enemy->getFacingDirection() == FACING_LEFT) {
		newEnemyCoordinate = Coordinate(enemyCoordinate.getX() - enemy->getVelocity().x, enemyCoordinate.getY());
	}
	else if (enemy->getFacingDirection() == FACING_RIGHT) {
		newEnemyCoordinate = Coordinate(enemyCoordinate.getX() + enemy->getVelocity().x, enemyCoordinate.getY());
	}

	enemy->setCoordinate(newEnemyCoordinate);
	enemy->incrementDistanceTravelled(enemy->getVelocity().x);
}

void EnemyController::verticalMovement(Enemy * enemy)
{
	enemy->setVelocity(Vector2(0, 0.08));
	Coordinate newEnemyCoordinate;
	Coordinate enemyCoordinate = enemy->getCoordinate();
	if (enemy->getFacingDirection() == FACING_LEFT) {
		newEnemyCoordinate = Coordinate(enemyCoordinate.getX(), enemyCoordinate.getY() - enemy->getVelocity().y);
	}
	else if (enemy->getFacingDirection() == FACING_RIGHT) {
		newEnemyCoordinate = Coordinate(enemyCoordinate.getX(), enemyCoordinate.getY() + enemy->getVelocity().y);
	}

	enemy->setCoordinate(newEnemyCoordinate);
	enemy->incrementDistanceTravelled(enemy->getVelocity().y);
}



