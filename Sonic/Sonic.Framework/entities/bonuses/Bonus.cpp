#include "Bonus.h"

void Bonus::onCollision(Player * player)
{
	switch (EntityResolver::fromTypeString(type))
	{
		case bonus_super_ring:
			player->sumPoints(SUPER_RING_GIVEN_POINTS);
			break;
		case bonus_escudo:
			player->setHasShield(true);
			break;
		default:
			break;
	}
	this->isActive = false;
}
