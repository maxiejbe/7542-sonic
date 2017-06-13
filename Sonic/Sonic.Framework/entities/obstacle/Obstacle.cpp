#include "Obstacle.h"

const int OBSTACLE_BLOCK_DEFAULT_WIDTH = 79;
const int OBSTACLE_BLOCK_DEFAULT_HEIGHT = 80;
const int OBSTACLE_SPIKES_DEFAULT_WIDTH = 59;
const int OBSTACLE_SPIKES_DEFAULT_HEIGHT = 60;

Obstacle::Obstacle(string type)
{
	this->type = type;
	if (type == EntityResolver::toTypeString(EntityType::obstaculo_piedra)) {
		this->dimensions = Dimensions(OBSTACLE_BLOCK_DEFAULT_WIDTH, OBSTACLE_BLOCK_DEFAULT_HEIGHT, 0);
	}
	else {
		this->dimensions = Dimensions(OBSTACLE_SPIKES_DEFAULT_WIDTH, OBSTACLE_SPIKES_DEFAULT_HEIGHT, 0);
	}
}

void Obstacle::onCollision(Player * player, Camera* camera)
{
	int borderBotton = player->getYPosition() + 50;
	int otherBorderTop = this->getYPosition();

	if (borderBotton <= otherBorderTop) {
		if (player->getFacingDirection() == FACING_RIGHT)
			player->setXVelocity(-5);
		else
			player->setXVelocity(5);
	}
	else {
		if (player->getFacingDirection() == FACING_RIGHT)
			player->setXPosition(this->getCoordinate().getX() - 72);
		else
			player->setXPosition(this->getCoordinate().getX() + this->getDimensions().getWidth());
	}
}