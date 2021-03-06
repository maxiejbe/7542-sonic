#include "Ring.h"

const int RING_GIVEN_POINTS = 1;
const int RING_DEFAULT_WIDTH = 32;
const int RING_DEFAULT_HEIGHT = 32;

Ring::Ring(string type)
{
	this->type = type;
	this->dimensions = Dimensions(RING_DEFAULT_WIDTH, RING_DEFAULT_HEIGHT, 0);
}

void Ring::serialize(Writer<StringBuffer> &writer)
{
	writer.StartObject();
	Entity::serialize(writer);
	writer.EndObject();
}

void Ring::onCollision(Player * player, Camera* camera)
{
	if (!isActive) return;
	player->sumRings(RING_GIVEN_POINTS);
	this->isActive = false;
}
