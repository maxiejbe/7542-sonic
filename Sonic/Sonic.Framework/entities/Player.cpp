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
const char* PLAYER_TEST_MODE_NODE = "tm";
const char* PLAYER_RINGS_NODE = "ri";
const char* PLAYER_LIVES_NODE = "li";
const char* PLAYER_POINTS_NODE = "po";
const char* PLAYER_IS_ACTIVE_NODE = "ia";
const char* PLAYER_HAS_SHIELD_NODE = "hs";
const char* PLAYER_IS_INVINCIBLE_NODE = "ii";
const char* PLAYER_IS_RECOVERING_NODE = "ir";
const char* PLAYER_TEAM_POINTS_NODE = "tp";
const char* PLAYER_TEAM_RINGS_NODE = "tr";
const char* PLAYER_TEAM_ID_NODE = "ti";

const int COLLABORATIVE_MODE = 2;
const int COLLABORATIVE_TEAM_ID = 1;

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
	this->testMode = false;

	this->lives = 3;
	this->rings = 0;
	this->points = 0;
	this->isActive = true;

	this->time = 0;
	this->hasShield = false;
	this->isInvincible = false;
	this->isRecovering = false;

	this->teamPoints = 0;
	this->teamRings = 0;
	this->teamId = 0;
}

Player::Player(Player & anotherPlayer) {
	this->copyFrom(anotherPlayer);
}

void Player::copyFrom(Player & anotherPlayer)
{
	this->setGroundPos(anotherPlayer.getGroundPos());
	this->setXPosition(anotherPlayer.getPosition().x);
	this->setYPosition(anotherPlayer.getPosition().y);
	this->setXVelocity(anotherPlayer.getVelocity().x);
	this->setYVelocity(anotherPlayer.getVelocity().y);
	this->setScrollSpeed(anotherPlayer.getScrollSpeed());
	this->setTargetVelX(anotherPlayer.getTargetVelX());
	this->setIsJumping(anotherPlayer.getIsJumping());
	this->setFacingDirection(anotherPlayer.getFacingDirection());
	this->setNumber(anotherPlayer.getNumber());
	this->setSpriteState(anotherPlayer.getSpriteState());
	this->setPlayerType(anotherPlayer.getPlayerType());
	this->setIsConnected(anotherPlayer.getIsConnected());
	this->setTestMode(anotherPlayer.getTestMode());
	this->setRings(anotherPlayer.getRings());
	this->setLives(anotherPlayer.getLives());
	this->setPoints(anotherPlayer.getPoints());
	this->setIsActive(anotherPlayer.getIsActive());
	this->setHasShield(anotherPlayer.getHasShield());
	this->setIsInvincible(anotherPlayer.getIsInvincible());
	this->setIsRecovering(anotherPlayer.getIsRecovering());
	this->setTeamPoints(anotherPlayer.getTeamPoints());
	this->setTeamRings(anotherPlayer.getTeamRings());
	this->setTeamId(anotherPlayer.getTeamId());
}

void Player::lock()
{
	this->playerMutex.lock();
}

void Player::unlock()
{
	this->playerMutex.unlock();
}

int Player::getXPosition()
{
	return position.x;
}

int Player::getYPosition()
{
	return position.y;
}

int Player::getRadio()
{
	return 0;
}

CollisionableType Player::getCollisionableType()
{
	return CollisionableType::rectangle;
}

bool Player::isDamaging() {
	//If we have a kind of bonus, apply here
	return spriteState == PlayerStatus::jumping || spriteState == PlayerStatus::spinning;
}

void Player::damage()
{
	if (this->hasShield) {
		this->hasShield = false;
		return;
	}

	if (this->rings > 0) {
		int teamId = getTeamId();
		if (teamId > 0) {
			int teamIdIndex = teamId - 1;
			(*this->generalTeamRings)[teamIdIndex] -= this->rings;
		}
		rings = 0;
		this->isRecovering = true;
		return;
	}

	if (lives > 1) {
		this->lives--;
	}
	else {
		isActive = false;
	}

	this->isRecovering = true;
}

Vector2 Player::getPosition()
{
	return this->position;
}

void Player::reset()
{
	this->position = Vector2(0, getGroundPos());
	this->isJumping = false;
	this->facingDirection = FACING_RIGHT;
	this->spriteState = PlayerStatus::idle;
	this->rings = 0;
	this->time = 0;
	this->hasShield = false;
	this->isInvincible = false;
	this->isRecovering = false;
	this->teamRings = 0;
	this->velocity = Vector2(0, 0);
	this->invincibleTime = 0;
	this->recoveringTime = 0;
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

int Player::getTime()
{
	return this->time;
}

void Player::setTime(int time)
{
	this->time = time;
}

void Player::setTestMode(bool testMode)
{
	this->testMode = testMode;
}

bool Player::getTestMode()
{
	return this->testMode;
}

int Player::getRings()
{
	return this->rings;
}

void Player::setRings(int rings)
{
	this->rings = rings;
}

int Player::getLives()
{
	return this->lives;
}

void Player::setLives(int lives)
{
	this->lives = lives;
}

int Player::getPoints()
{
	return this->points;
}

void Player::setPoints(int points)
{
	this->points = points;
}

bool Player::getIsActive()
{
	return this->isActive;
}

void Player::setIsActive(bool isActive)
{
	this->isActive = isActive;
}

bool Player::getHasShield()
{
	return this->hasShield;
}

int Player::getTeamPoints()
{
	return this->teamPoints;
}

void Player::setTeamPoints(int teamPoints)
{
	this->teamPoints = teamPoints;
}

int Player::getTeamRings()
{
	return this->teamRings;
}

void Player::setTeamRings(int teamRings)
{
	this->teamRings = teamRings;
}

bool Player::getIsInvincible()
{
	return this->isInvincible;
}

void Player::setIsInvincible(bool isInvincible)
{
	this->isInvincible = isInvincible;
}

int Player::getInvincibleTime()
{
	return this->invincibleTime;
}

void Player::setInvincibleTime(int ms)
{
	this->invincibleTime = ms;
}

bool Player::getIsRecovering()
{
	return this->isRecovering;
}

void Player::setIsRecovering(bool isRecovering)
{
	this->isRecovering = isRecovering;
}

int Player::getRecoveringTime()
{
	return this->recoveringTime;;
}

void Player::setRecoveringTime(int ms)
{
	this->recoveringTime = ms;
}

PlayerType Player::calculatePlayerType()
{
	switch (this->getNumber() % 4) {
	case 1:
		return PlayerType::SONIC;
	case 2:
		return PlayerType::TAILS;
	case 3:
		return PlayerType::KNUCKLES;
	case 0:
		return PlayerType::SHADOW;
	default:
		return PlayerType::SONIC;
	}
}

double Player::calculateGroundPos(int windowHeight)
{
	switch (playerType) {
	case SONIC:
	case KNUCKLES:
	case SHADOW:
		return windowHeight / 1.40;
	case TAILS:
		return windowHeight / 1.358;
	default:
		return windowHeight / 1.35;
	}
}

void Player::unserialize(Value * nodeRef)
{
	//position x
	parseDouble(&position.x, 0, nodeRef, PLAYER_X_POSITION_NODE);
	//position y
	parseDouble(&position.y, 0, nodeRef, PLAYER_Y_POSITION_NODE);
	//velocity x
	parseDouble(&velocity.x, 0, nodeRef, PLAYER_X_VELOCITY_NODE);
	//velocity y
	parseDouble(&velocity.y, 0, nodeRef, PLAYER_Y_VELOCITY_NODE);
	//scroll speed
	parseInt(&scrollSpeed, 0, nodeRef, PLAYER_SCROLL_SPEED_NODE, Validator::intGreaterThanZero);
	//ground pos
	parseDouble(&groundPos, 0, nodeRef, PLAYER_GROUND_POS_NODE);
	//jumping
	parseBool(&isJumping, false, nodeRef, PLAYER_JUMPING_NODE);
	//target vel x
	parseDouble(&targetVelX, 0, nodeRef, PLAYER_TARGET_VEL_X_NODE);
	//facing direction
	parseInt((int*)&facingDirection, 0, nodeRef, PLAYER_FACING_DIRECTION_NODE, Validator::intGreaterThanOrEqualToZero);
	//number
	parseInt(&number, -1, nodeRef, PLAYER_NUMBER_NODE, Validator::intGreaterThanOrEqualToZero);
	//sprite state
	parseInt((int*)&spriteState, 0, nodeRef, PLAYER_SPRITE_STATE_NODE, Validator::intGreaterThanOrEqualToZero);
	//player type
	parseInt((int*)&playerType, 0, nodeRef, PLAYER_TYPE_NODE);
	//is connected
	parseBool(&isConnected, false, nodeRef, PLAYER_IS_CONNECTED_NODE);
	//time
	//parseInt(&time, 0, nodeRef, PLAYER_MILLISECONDS);
	//test mode
	parseBool(&testMode, false, nodeRef, PLAYER_TEST_MODE_NODE);
	//rings
	parseInt(&rings, 0, nodeRef, PLAYER_RINGS_NODE);
	//lives
	parseInt(&lives, 0, nodeRef, PLAYER_LIVES_NODE);
	//points
	parseInt(&points, 0, nodeRef, PLAYER_POINTS_NODE);
	//is active
	parseBool(&isActive, false, nodeRef, PLAYER_IS_ACTIVE_NODE);
	//has shield
	parseBool(&hasShield, false, nodeRef, PLAYER_HAS_SHIELD_NODE);
	//is invincible
	parseBool(&isInvincible, false, nodeRef, PLAYER_IS_INVINCIBLE_NODE);
	//is recovering
	parseBool(&isRecovering, false, nodeRef, PLAYER_IS_RECOVERING_NODE);
	//team points
	parseInt(&teamPoints, 0, nodeRef, PLAYER_TEAM_POINTS_NODE);
	//team rings
	parseInt(&teamRings, 0, nodeRef, PLAYER_TEAM_RINGS_NODE);
	//team id
	parseInt(&teamId, 0, nodeRef, PLAYER_TEAM_ID_NODE);
}

void Player::serializePlayer()
{
	this->lock();
	this->serializedPlayer = this->serialize();
	this->unlock();
}

string Player::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.SetMaxDecimalPlaces(4);
	writer.StartObject();

	writer.String(PLAYER_X_POSITION_NODE);
	writer.Double(this->position.x);
	writer.String(PLAYER_Y_POSITION_NODE);
	writer.Double(this->position.y);
	writer.String(PLAYER_X_VELOCITY_NODE);
	writer.Double(this->velocity.x);
	writer.String(PLAYER_Y_VELOCITY_NODE);
	writer.Double(this->velocity.y);
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
	writer.String(PLAYER_TYPE_NODE);
	writer.Int(this->playerType);
	writer.String(PLAYER_IS_CONNECTED_NODE);
	writer.Bool(this->isConnected);
	//writer.String(PLAYER_MILLISECONDS);
	//writer.Int(this->time);
	writer.String(PLAYER_TEST_MODE_NODE);
	writer.Bool(this->testMode);
	writer.String(PLAYER_RINGS_NODE);
	writer.Int(this->rings);
	writer.String(PLAYER_LIVES_NODE);
	writer.Int(this->lives);
	writer.String(PLAYER_POINTS_NODE);
	writer.Int(this->points);
	writer.String(PLAYER_IS_ACTIVE_NODE);
	writer.Bool(this->isActive);
	writer.String(PLAYER_HAS_SHIELD_NODE);
	writer.Bool(this->hasShield);
	writer.String(PLAYER_IS_INVINCIBLE_NODE);
	writer.Bool(this->isInvincible);
	writer.String(PLAYER_IS_RECOVERING_NODE);
	writer.Bool(this->isRecovering);
	writer.String(PLAYER_TEAM_POINTS_NODE);
	writer.Int(this->teamPoints);
	writer.String(PLAYER_TEAM_RINGS_NODE);
	writer.Int(this->teamRings);
	writer.String(PLAYER_TEAM_ID_NODE);
	writer.Int(this->teamId);

	int(time);

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

void Player::sumPoints(int points)
{
	this->points += points;
	int teamId = getTeamId();
	if (teamId <= 0) return;

	//Total team points and rings
	int teamIdIndex = teamId - 1;
	(*this->generalTeamPoints)[teamIdIndex] += points;
}

void Player::sumRings(int rings)
{
	this->rings += rings;

	int teamId = getTeamId();
	if (teamId <= 0) return;

	//Total team points and rings
	int teamIdIndex = teamId - 1;
	(*this->generalTeamRings)[teamIdIndex] += rings;
}

void Player::setHasShield(bool hasShield)
{
	this->hasShield = hasShield;
}

int Player::getTeamId()
{
	int teamId = this->teamId;
	//Please dont change collaborative mode number
	if (gameMode == COLLABORATIVE_MODE) teamId = COLLABORATIVE_TEAM_ID;
	return teamId;
}

void Player::setTeamId(int teamId)
{
	this->teamId = teamId;
}

string Player::getSerializedPlayer()
{
	this->lock();
	string serializedPlayer = this->serializedPlayer;
	this->unlock();
	return serializedPlayer;
}
