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
	if (player->isDamaging()) {
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
		if (player->getIsJumping()) {
			player->setYVelocity(-8);
		}
	}
	else {
		int borderLeft = player->getXPosition();
		int borderRight = player->getXPosition() + 72;
		int otherBorderLeft = this->getXPosition();
		int otherBorderRight = this->getXPosition() + this->getWidth();

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