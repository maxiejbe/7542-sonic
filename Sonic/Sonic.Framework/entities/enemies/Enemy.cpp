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

const int ENEMY_CRAB_MAX_DISTANCE = 180;
const int ENEMY_FISH_MAX_DISTANCE = 350;
const int ENEMY_FLY_MAX_DISTANCE = 300;

const int CRAB_GIVEN_POINTS = 100;
const int FLY_GIVEN_POINTS = 500;
const int FISH_GIVEN_POINTS = 200;

const int BOUNCE_ON_COLLISION = 10;


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
		this->dimensions = Dimensions(ENEMY_CRAB_WIDTH, ENEMY_CRAB_HEIGHT, 0);
		this->maxHorizontalDistance = ENEMY_CRAB_MAX_DISTANCE;
		break;
	case EntityType::enemigo_pez:
		this->dimensions = Dimensions(ENEMY_FISH_WIDTH, ENEMY_FISH_HEIGHT, 0);
		this->maxVerticalDistance = ENEMY_FISH_MAX_DISTANCE;
		break;
	case EntityType::enemigo_mosca:
		this->dimensions = Dimensions(ENEMY_FLY_WIDTH, ENEMY_FLY_HEIGHT, 0);
		this->maxHorizontalDistance = ENEMY_FLY_MAX_DISTANCE;
		break;
	default:
		this->dimensions = Dimensions(0, 0, 0);
		break;
	}

	this->points = ENEMY_DEFAULT_POINTS;
	this->distanceTravelled = 0;
	this->serializedEnemy = string();
	this->isMoving = true;
	this->facingDirection = FacingDirection::FACING_LEFT;
}


Enemy::~Enemy()
{
}

void Enemy::copyFrom(Enemy& anotherEnemy)
{
	Entity::copyFrom(anotherEnemy);

	this->points = anotherEnemy.getPoints();
}

Vector2 Enemy::getVelocity()
{
	return this->velocity;
}

void Enemy::setVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

double Enemy::getDistanceTravelled()
{
	return this->distanceTravelled;
}

void Enemy::incrementDistanceTravelled(double distance) {
	this->distanceTravelled += abs(distance);
}

void Enemy::resetDistanceTravelled()
{
	this->distanceTravelled = 0;
}

double Enemy::getMaxDistance()
{
	EntityType eType = EntityResolver::fromTypeString(type);
	switch (eType) {
	case EntityType::enemigo_cangrejo:
		return this->maxHorizontalDistance;
		break;
	case EntityType::enemigo_pez:
		return this->maxVerticalDistance;
		break;
	case EntityType::enemigo_mosca:
		return this->maxHorizontalDistance;
		break;
	default:
		return 0;
		break;
	}
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

void Enemy::lock()
{
	this->enemyMutex.lock();
}

void Enemy::unlock()
{
	this->enemyMutex.unlock();
}

void Enemy::serializeEnemy()
{
	this->lock();
	this->serializedEnemy = this->serialize();
	this->unlock();
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

	if (player->isDamaging() || player->getIsInvincible()) {
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
		if (!player->getIsRecovering()) {
			player->damage();
		}

		if (player->getVelocity().x > 0)
			player->setXVelocity(-BOUNCE_ON_COLLISION);
		else if (player->getVelocity().x < 0)
			player->setXVelocity(BOUNCE_ON_COLLISION);
		else {
			if (player->getFacingDirection() == FACING_RIGHT)
				player->setXVelocity(-BOUNCE_ON_COLLISION);
			else
				player->setXVelocity(BOUNCE_ON_COLLISION);
		}

	}
}

