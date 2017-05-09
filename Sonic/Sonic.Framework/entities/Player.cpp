#include "Player.h"

const char* PLAYER_NUMBER_NODE = "id";
const char* PLAYER_X_POSITION_NODE = "x";
const char* PLAYER_Y_POSITION_NODE = "y";
const char* PLAYER_X_VELOCITY_NODE = "vx";
const char* PLAYER_Y_VELOCITY_NODE = "vy";
const char* PLAYER_WIDTH_NODE = "w";
const char* PLAYER_HEIGHT_NODE = "h";
const char* PLAYER_FACING_DIRECTION_NODE = "fd";
const char* PLAYER_SPRITE_STATE_NODE = "st";
const char* PLAYER_TARGET_VEL_X_NODE = "tvx";
const char* PLAYER_SCENARIO_WIDTH_NODE = "scw";
const char* PLAYER_SCENARIO_HEIGHT_NODE = "sch";
const char* PLAYER_JUMPING_NODE = "jmp";
const char* PLAYER_GROUND_POS_NODE = "gp";
const char* PLAYER_SCROLL_SPEED_NODE = "scs";
const char* PLAYER_FILE_PATH_NODE = "fp";
const char* PLAYER_TYPE_NODE = "pt";
const char* PLAYER_IS_CONNECTED_NODE = "ic";


Player::Player()
{
	this->groundPos = 0.0;

	this->position = Vector2(0, 0);
	this->velocity = Vector2(0, 0);

	this->scenarioWidth = 0;
	this->scenarioHeight = 0;

	this->scrollSpeed = 0;

	this->isJumping = false;
	this->facingDirection = FACING_RIGHT;
	this->spriteState = PlayerStatus::idle;
	this->isConnected = true;
}

Player::Player(Player & anotherPlayer) {
	this->copyFrom(anotherPlayer);
}

void Player::copyFrom(Player & anotherPlayer)
{
	this->setFilePath(anotherPlayer.getFilePath());
	this->setGroundPos(anotherPlayer.getGroundPos());
	this->setXPosition(anotherPlayer.getPosition().x);
	this->setYPosition(anotherPlayer.getPosition().y);
	this->setXVelocity(anotherPlayer.getVelocity().x);
	this->setYVelocity(anotherPlayer.getVelocity().y);
	this->setWidth(anotherPlayer.getWidth());
	this->setHeight(anotherPlayer.getHeight());
	this->setScenarioWidth(anotherPlayer.getScenarioWidth());
	this->setScenarioHeight(anotherPlayer.getScenarioHeight());
	this->setScrollSpeed(anotherPlayer.getScrollSpeed());
	this->setTargetVelX(anotherPlayer.getTargetVelX());
	this->setIsJumping(anotherPlayer.getIsJumping());
	this->setFacingDirection(anotherPlayer.getFacingDirection());
	this->setNumber(anotherPlayer.getNumber());
	this->setSpriteState(anotherPlayer.getSpriteState());
	this->setPlayerType(anotherPlayer.getPlayerType());
	this->setIsConnected(anotherPlayer.getIsConnected());
}

Vector2 Player::getPosition()
{
	return this->position;
}

void Player::setXPosition(double x)
{
	this->position.x = x;
}

void Player::setYPosition(double y)
{
	this->position.y = y;
}

Vector2 Player::getVelocity()
{
	return this->velocity;
}

void Player::setXVelocity(double x)
{
	this->velocity.x = x;
}

void Player::setYVelocity(double y)
{
	this->velocity.y = y;
}

void Player::setWidth(int w)
{
	this->width = w;
}

int Player::getWidth()
{
	return this->width;
}

void Player::setHeight(int h)
{
	this->height = h;
}

int Player::getHeight()
{
	return this->height;
}

FacingDirection Player::getFacingDirection()
{
	return facingDirection;
}

void Player::setFacingDirection(FacingDirection facingDirection)
{
	this->facingDirection = facingDirection;
}

PlayerStatus Player::getSpriteState()
{
	return spriteState;
}

void Player::setSpriteState(PlayerStatus spriteState)
{
	this->spriteState = spriteState;
}

void Player::setFilePath(string filePath)
{
	this->filePath = filePath;
}

string Player::getFilePath()
{
	return filePath;
}

double Player::getTargetVelX()
{
	return this->targetVelX;
}

void Player::setTargetVelX(double targetVelX)
{
	this->targetVelX = targetVelX;
}

int Player::getScenarioWidth()
{
	return this->scenarioWidth;
}

void Player::setScenarioWidth(int sw)
{
	this->scenarioWidth = sw;
}

int Player::getScenarioHeight()
{
	return this->scenarioHeight;
}

void Player::setScenarioHeight(int sh)
{
	this->scenarioHeight = sh;
}

void Player::setIsJumping(bool isJumping)
{
	this->isJumping = isJumping;
}

bool Player::getIsJumping()
{
	return this->isJumping;
}

double Player::getGroundPos()
{
	return this->groundPos;
}

void Player::setGroundPos(double gPos)
{
	this->groundPos = gPos;
}

int Player::getScrollSpeed()
{
	return this->scrollSpeed;
}

void Player::setScrollSpeed(int scSpeed)
{
	this->scrollSpeed = scSpeed;
}

PlayerType Player::getPlayerType()
{
	return this->playerType;
}

void Player::setPlayerType(PlayerType playerType)
{
	this->playerType = playerType;
}

bool Player::getIsConnected()
{
	return this->isConnected;
}

void Player::setIsConnected(bool isConnected)
{
	this->isConnected = isConnected;
}

void Player::unserialize(Value * nodeRef)
{
	double x, y, vx, vy, gp, tvx = 0;
	//position x
	parseDouble(&x, 0, nodeRef, PLAYER_X_POSITION_NODE);
	this->setXPosition(x);
	//position y
	parseDouble(&y, 0, nodeRef, PLAYER_Y_POSITION_NODE);
	this->setYPosition(y);
	//velocity x
	parseDouble(&vx, 0, nodeRef, PLAYER_X_VELOCITY_NODE);
	this->setXVelocity(vx);
	//velocity y
	parseDouble(&vy, 0, nodeRef, PLAYER_Y_VELOCITY_NODE);
	this->setYVelocity(vy);
	//width
	parseInt(&this->width, 0, nodeRef, PLAYER_WIDTH_NODE, Validator::intGreaterThanZero);
	//height
	parseInt(&this->height, 0, nodeRef, PLAYER_HEIGHT_NODE, Validator::intGreaterThanZero);
	//scenario width
	parseInt(&this->scenarioWidth, 0, nodeRef, PLAYER_SCENARIO_WIDTH_NODE, Validator::intGreaterThanZero);
	//scenario height
	parseInt(&this->scenarioHeight, 0, nodeRef, PLAYER_SCENARIO_HEIGHT_NODE, Validator::intGreaterThanZero);
	//scroll speed
	parseInt(&this->scrollSpeed, 0, nodeRef, PLAYER_SCROLL_SPEED_NODE, Validator::intGreaterThanZero);
	//ground pos
	parseDouble(&gp, 0, nodeRef, PLAYER_GROUND_POS_NODE);
	this->setGroundPos(gp);
	//jumping
	parseBool(&isJumping, false, nodeRef, PLAYER_JUMPING_NODE);
	//target vel x
	parseDouble(&tvx, 0, nodeRef, PLAYER_TARGET_VEL_X_NODE);
	this->setTargetVelX(tvx);
	//facing direction
	parseInt((int*)&facingDirection, 0, nodeRef, PLAYER_FACING_DIRECTION_NODE, Validator::intGreaterThanOrEqualToZero);
	//number
	parseInt(&number, -1, nodeRef, PLAYER_NUMBER_NODE, Validator::intGreaterThanOrEqualToZero);
	//sprite state
	parseInt((int*)&spriteState, 0, nodeRef, PLAYER_SPRITE_STATE_NODE, Validator::intGreaterThanOrEqualToZero);
	//file path
	parseString(&filePath, "img/sonic-spritesheet.png", nodeRef, PLAYER_FILE_PATH_NODE);
	//player type
	parseInt((int*)&playerType, 0, nodeRef, PLAYER_TYPE_NODE);
	//is connected
	parseBool(&isConnected, false, nodeRef, PLAYER_IS_CONNECTED_NODE);
}

string Player::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();

	writer.String(PLAYER_X_POSITION_NODE);
	writer.Double(this->position.x);
	writer.String(PLAYER_Y_POSITION_NODE);
	writer.Double(this->position.y);
	writer.String(PLAYER_X_VELOCITY_NODE);
	writer.Double(this->velocity.x);
	writer.String(PLAYER_Y_VELOCITY_NODE);
	writer.Double(this->velocity.y);
	writer.String(PLAYER_WIDTH_NODE);
	writer.Int(this->width);
	writer.String(PLAYER_HEIGHT_NODE);
	writer.Int(this->height);
	writer.String(PLAYER_SCENARIO_WIDTH_NODE);
	writer.Int(this->scenarioWidth);
	writer.String(PLAYER_SCENARIO_HEIGHT_NODE);
	writer.Int(this->scenarioHeight);
	writer.String(PLAYER_SCROLL_SPEED_NODE);
	writer.Int(this->scrollSpeed);
	writer.String(PLAYER_GROUND_POS_NODE);
	writer.Double(this->groundPos);
	writer.String(PLAYER_JUMPING_NODE);
	writer.Bool(this->isJumping);
	writer.String(PLAYER_TARGET_VEL_X_NODE);
	writer.Double(this->targetVelX);
	writer.String(PLAYER_FACING_DIRECTION_NODE);
	writer.Int(this->facingDirection);
	writer.String(PLAYER_NUMBER_NODE);
	writer.Int(this->number);
	writer.String(PLAYER_SPRITE_STATE_NODE);
	writer.Int(this->spriteState);
	writer.String(PLAYER_FILE_PATH_NODE);
	const char* fp = this->filePath.c_str();
	writer.String(fp);
	writer.String(PLAYER_TYPE_NODE);
	writer.Int(this->playerType);
	writer.String(PLAYER_IS_CONNECTED_NODE);
	writer.Bool(this->isConnected);

	writer.EndObject();
	return s.GetString();
}

char * Player::getNodeName()
{
	return nullptr;
}

int Player::getNumber()
{
	return this->number;
}

void Player::setNumber(int number)
{
	this->number = number;
}
