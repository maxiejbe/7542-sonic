#include "Enemy.h"

const char* ENEMY_FACING_DIRECTION_NODE = "fd";

const double ENEMY_DEFAULT_POSX = 0;
const double ENEMY_DEFAULT_POSY = 0;
const double ENEMY_DEFAULT_VELX = 0;
const double ENEMY_DEFAULT_VELY = 0;
const int ENEMY_CRAB_WIDTH = 88;
const int ENEMY_CRAB_HEIGHT = 70;
const int ENEMY_FISH_WIDTH = 60;
const int ENEMY_FISH_HEIGHT = 64;
const int ENEMY_FLY_WIDTH = 90;
const int ENEMY_FLY_HEIGHT = 38;
const int ENEMY_DEFAULT_POINTS = 10;
const int ENEMY_DEFAULT_MAX_DISTANCE = 10;

const int CRAB_GIVEN_POINTS = 100;
const int FLY_GIVEN_POINTS = 500;
const int FISH_GIVEN_POINTS = 200;


Enemy::Enemy(string type)
{
	this->coordinate = Coordinate(ENEMY_DEFAULT_POSX, ENEMY_DEFAULT_POSY);
	this->velocity = Vector2(ENEMY_DEFAULT_VELX, ENEMY_DEFAULT_VELY);
	this->type = type;
	InitializeProperties();
}

void Enemy::InitializeProperties()
{
	EntityType eType = EntityResolver::fromTypeString(type);
	switch (eType) {
	case EntityType::enemigo_cangrejo:
		this->dimensions = Dimensions(ENEMY_CRAB_WIDTH, ENEMY_CRAB_HEIGHT, 0); //TODO
		break;
	case EntityType::enemigo_pez:
		this->dimensions = Dimensions(ENEMY_FISH_WIDTH, ENEMY_FISH_HEIGHT, 0); //TODO
		break;
	case EntityType::enemigo_mosca:
		this->dimensions = Dimensions(ENEMY_FLY_WIDTH, ENEMY_FLY_HEIGHT, 0); //TODO
		break;
	default:
		this->dimensions = Dimensions(0, 0, 0);
		break;
	}

	this->points = ENEMY_DEFAULT_POINTS;
	this->maxDistance = ENEMY_DEFAULT_MAX_DISTANCE;
	this->facingDirection = FACING_LEFT;
	this->distanceTravelled = 0;
	this->serializedEnemy = string();
}


Enemy::~Enemy()
{
}

void Enemy::copyFrom(Enemy& anotherEnemy)
{
	Entity::copyFrom(anotherEnemy);

	this->points = anotherEnemy.getPoints();
	this->facingDirection = anotherEnemy.getFacingDirection();
}


Vector2 Enemy::getVelocity()
{
	return this->velocity;
}


FacingDirection Enemy::getFacingDirection()
{
	return this->facingDirection;
}

void Enemy::setFacingDirection(FacingDirection facingDirection)
{
	this->facingDirection = facingDirection;
}

int Enemy::getMaxDistance()
{
	return this->maxDistance;
}

int Enemy::getDistanceTravelled()
{
	return this->distanceTravelled;
}


void Enemy::incrementDistanceTravelled(int distance) {
	this->distanceTravelled += distance;
}

void Enemy::resetDistanceTravelled()
{
	this->distanceTravelled = 0;
}

void Enemy::kill()
{
	this->isActive = false;
}

int Enemy::getPoints()
{
	return this->points;
}

int Enemy::getGivenPoints()
{
	switch (EntityResolver::fromTypeString(type))
	{
		//Sorry, this should be implemented in player with polimorfic methods
	case enemigo_cangrejo:
		return CRAB_GIVEN_POINTS;
	case enemigo_mosca:
		return FLY_GIVEN_POINTS;
		break;
	case enemigo_pez:
		return FISH_GIVEN_POINTS;
		break;
	default:
		return 0;
	}
}


void Enemy::serializeEnemy()
{
	this->serializedEnemy = this->serialize();
}

string Enemy::getSerializedEnemy()
{
	return this->serializedEnemy;
}

void Enemy::unserialize(Value * nodeRef)
{
	Entity::unserialize(nodeRef);
	parseInt((int*)&facingDirection, 0, nodeRef, ENEMY_FACING_DIRECTION_NODE, Validator::intGreaterThanOrEqualToZero);
}

char * Enemy::getNodeName()
{
	return nullptr;
}

string Enemy::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();
	basePropertiesSerialization(writer);
	writer.String(ENEMY_FACING_DIRECTION_NODE);
	writer.Int(facingDirection);
	writer.EndObject();

	return s.GetString();
}

void Enemy::onCollision(Player * player, Camera* camera)
{
	if (!getIsActive()) return;

	if (player->isDamaging()) {
		player->sumPoints(getGivenPoints());
		this->kill();
		if (player->getIsJumping()) {
			// If is falling, bounce
			if (player->getVelocity().y > 0) {
				player->setYVelocity(-8);
			}
			else {
				player->setYVelocity(0);
			}
		}
	}
	else {
		player->damage();

		if (player->getVelocity().x > 0)
			player->setXVelocity(-5);
		else
			player->setXVelocity(5);
	}


}

