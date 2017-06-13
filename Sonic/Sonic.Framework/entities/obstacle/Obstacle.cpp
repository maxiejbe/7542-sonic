#include "Obstacle.h"

const int OBSTACLE_DEFAULT_WIDTH = 20;
const int OBSTACLE_DEFAULT_HEIGHT = 20;

void Obstacle::onCollision(Player * player)
{

}

Obstacle::Obstacle(string type)
{
	this->type = type;
	this->dimensions = Dimensions(OBSTACLE_DEFAULT_WIDTH, OBSTACLE_DEFAULT_HEIGHT, 0); //TODO
}
