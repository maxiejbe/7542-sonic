#include "Bonus.h"

const int BONUS_DEFAULT_WIDTH = 20;
const int BONUS_DEFAULT_HEIGHT = 20;

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

Bonus::Bonus(string type)
{
	this->type = type;
	this->dimensions = Dimensions(BONUS_DEFAULT_WIDTH, BONUS_DEFAULT_HEIGHT, 0); //TODO
}
