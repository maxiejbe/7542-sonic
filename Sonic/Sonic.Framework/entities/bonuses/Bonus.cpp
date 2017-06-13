#include "Bonus.h"

const int BONUS_DEFAULT_WIDTH = 56;
const int BONUS_DEFAULT_HEIGHT = 64;

Bonus::Bonus(string type)
{
	this->type = type;
	this->dimensions = Dimensions(BONUS_DEFAULT_WIDTH, BONUS_DEFAULT_HEIGHT, 0);
}


void Bonus::onCollision(Player * player, Camera* camera)
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