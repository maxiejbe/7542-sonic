#include "EnemyController.h"

EnemyController::EnemyController()
{
}

void EnemyController::update(Enemy * enemy, int milliseconds)
{
	enemy->lock();

	enemy->setTime(milliseconds);

	move(enemy);

	enemy->unlock();
}

void EnemyController::move(Enemy * enemy)
{
	switch (EntityResolver::fromTypeString(enemy->getType())) {
	case enemigo_cangrejo:
		horizontalMovement(enemy, 0.01);
		break;
	case enemigo_pez:
		verticalMovement(enemy, 0.1);
		break;
	case enemigo_mosca:
		horizontalMovement(enemy, 0.03);
		break;
	}

	// If reached max distance change direction
	if (enemy->getDistanceTravelled() >= enemy->getMaxDistance()) {
		FacingDirection newDirection = (enemy->getFacingDirection() == FACING_LEFT) ? FACING_RIGHT : FACING_LEFT;
		enemy->setFacingDirection(newDirection);
		enemy->resetDistanceTravelled();
	}
}

void EnemyController::horizontalMovement(Enemy * enemy, double velocityX)
{
	if (abs(enemy->getVelocity().x) > 100) {
		enemy->setVelocity(Vector2(0, 0));
	}

	enemy->setVelocity(Vector2(velocityX, 0));

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

void EnemyController::verticalMovement(Enemy * enemy, double velocityY)
{
	if (abs(enemy->getVelocity().y) > 100) {
		enemy->setVelocity(Vector2(0, 0));
	}

	enemy->setVelocity(Vector2(0, velocityY));

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



