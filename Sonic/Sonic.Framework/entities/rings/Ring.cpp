#include "Ring.h"

const int RING_GIVEN_POINTS = 1;

void Ring::onCollision(Player * player)
{
	if (!isActive) return;
	player->sumRings(RING_GIVEN_POINTS);
	this->isActive = false;
}
