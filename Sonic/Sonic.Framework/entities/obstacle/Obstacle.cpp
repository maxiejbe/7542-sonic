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
	int borderLeft = player->getXPosition();
	int borderRight = player->getXPosition() + 72;
	int borderBotton = player->getYPosition() + 54;

	int otherBorderLeft = this->getXPosition();
	int otherBorderRight = this->getXPosition() + this->getWidth();
	int otherBorderTop = this->getYPosition();

	if (borderBotton <= otherBorderTop) {
		if (this->getType() == EntityResolver::toTypeString(EntityType::obstaculo_pinche)) {
			player->damage();
		}
		if (player->getFacingDirection() == FACING_RIGHT)
			player->setXVelocity(-10);
		else
			player->setXVelocity(10);
	}
	else {
		if (borderRight >= otherBorderLeft && borderLeft < otherBorderLeft) {
			if (player->getVelocity().x < 0) return;
			player->setXPosition(this->getCoordinate().getX() - 72);
		}
		else if (borderLeft <= otherBorderRight && borderRight > otherBorderRight) {
			if (player->getVelocity().x > 0) return;
			player->setXPosition(this->getCoordinate().getX() + this->getDimensions().getWidth());
		}
	}
}