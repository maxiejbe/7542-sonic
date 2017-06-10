#include "Enemy.h"

const char* ENEMY_TYPE_NODE = "t";
const char* ENEMY_FACING_DIRECTION_NODE = "fd";
const char* EMEMY_ALIVE_NODE = "a";

const double ENEMY_DEFAULT_POSX = 0;
const double ENEMY_DEFAULT_POSY = 0;
const double ENEMY_DEFAULT_VELX = 0;
const double ENEMY_DEFAULT_VELY = 0;
const int ENEMY_DEFAULT_WIDTH = 20;
const int ENEMY_DEFAULT_HEIGHT = 20;
const int ENEMY_DEFAULT_POINTS = 10;
const int ENEMY_DEFAULT_MAX_DISTANCE = 10;

Enemy::Enemy(string type)
{
	this->coordinate = Coordinate(ENEMY_DEFAULT_POSX, ENEMY_DEFAULT_POSY);
	this->velocity = Vector2(ENEMY_DEFAULT_VELX, ENEMY_DEFAULT_VELY);
	this->type= type;
	InitializeProperties();
}

void Enemy::InitializeProperties() 
{
	this->dimensions = Dimensions(ENEMY_DEFAULT_WIDTH, ENEMY_DEFAULT_HEIGHT, 0);
	this->points = ENEMY_DEFAULT_POINTS;
	this->maxDistance = ENEMY_DEFAULT_MAX_DISTANCE;
	this->facingDirection = FACING_LEFT;
	this->distanceTravelled = 0;
	this->alive = true;
	this->serializedEnemy = string();
}


Enemy::~Enemy()
{
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

bool Enemy::isAlive()
{
	return this->alive;
}

void Enemy::kill()
{
	this->alive = false;
}

int Enemy::getPoints()
{
	return this->points;
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
	/*coordinate.parseObject(nodeRef);
	parseInt(&width, 0, nodeRef, ENEMY_WIDTH_NODE, Validator::intGreaterThanZero);
	parseInt(&height, 0, nodeRef, ENEMY_HEIGHT_NODE, Validator::intGreaterThanZero);
	parseInt((int*)&type, 0, nodeRef, ENEMY_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);
	parseInt((int*)&facingDirection, 0, nodeRef, ENEMY_FACING_DIRECTION_NODE, Validator::intGreaterThanOrEqualToZero);
	parseBool(&alive, true, nodeRef, EMEMY_ALIVE_NODE);*/
	
}

char * Enemy::getNodeName()
{
	return nullptr;
}

string Enemy::serialize()
{
	/*StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.SetMaxDecimalPlaces(4);
	writer.StartObject();

	writer.String(ENEMY_X_POSITION_NODE);
	writer.Double(this->position.x);
	writer.String(ENEMY_Y_POSITION_NODE);
	writer.Double(this->position.y);
	writer.String(ENEMY_WIDTH_NODE);
	writer.Int(this->width);
	writer.String(ENEMY_HEIGHT_NODE);
	writer.Int(this->height);
	writer.String(ENEMY_TYPE_NODE);
	writer.Int(this->type);
	writer.String(ENEMY_FACING_DIRECTION_NODE);
	writer.Int(this->facingDirection);
	writer.String(EMEMY_ALIVE_NODE);
	writer.Bool(this->alive);

	writer.EndObject();
	return s.GetString();*/

	return string();
}

