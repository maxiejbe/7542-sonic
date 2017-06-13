#include "Ring.h"

const int RING_GIVEN_POINTS = 1;
const int RING_DEFAULT_WIDTH = 20;
const int RING_DEFAULT_HEIGHT = 20;

Ring::Ring(string type)
{
	this->type = type;
	this->dimensions = Dimensions(RING_DEFAULT_WIDTH, RING_DEFAULT_HEIGHT, 0); //TODO
}

void Ring::onCollision(Player * player)
{
	if (!isActive) return;
	player->sumRings(RING_GIVEN_POINTS);
	this->isActive = false;
}
