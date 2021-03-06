#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Logger.h"
#include "../Vector2.h"
#include "../protocol/Message.h"
#include <chrono>
#include "common/Collisionable.h"
#include <unordered_map>

#include <mutex>
#include <iostream>

using namespace std;

enum FacingDirection { FACING_LEFT, FACING_RIGHT, FACING_UP, FACING_DOWN };

class Player : public Serializable, public Collisionable
{
public:
	Player();
	Player(int number, int windowHeight, int scenarioWidth, int scenarioHeight, int scrollSpeed, unordered_map<int, int>* teamPoints, unordered_map<int, int>* teamRings, int gameMode) : Player() {
		this->number = number;
		this->scenarioWidth = scenarioWidth;
		this->scenarioHeight = scenarioHeight;
		this->scrollSpeed = scrollSpeed;
		this->playerType = calculatePlayerType();
		this->groundPos = calculateGroundPos(windowHeight);
		this->position = Vector2(0, this->groundPos);
		this->isConnected = true;
		this->time = 0;
		this->testMode = false;
		this->generalTeamPoints = teamPoints;
		this->generalTeamRings = teamRings;
		this->gameMode = gameMode;
	}
	Player(Player&);

	void copyFrom(Player&);

	void lock();
	void unlock();

	//Collisionable
	int getXPosition() override;
	int getYPosition() override;
	int getRadio() override;
	int getWidth() override;
	int getHeight() override;
	CollisionableType getCollisionableType() override;

	bool isDamaging();
	void damage();

	Vector2 getPosition();
	void setXPosition(double x);
	void setYPosition(double y);
	void reset();
	Vector2 getVelocity();
	void setXVelocity(double x);
	void setYVelocity(double y);
	void setNumber(int number);

	void sumPoints(int points);
	void sumRings(int points);
	void setHasShield(bool hasShield);
	int getTeamId();
	void setTeamId(int teamId);

	string getSerializedPlayer();

	int getNumber();
	void setWidth(int w);
	void setHeight(int h);
	FacingDirection getFacingDirection();
	void setFacingDirection(FacingDirection facingDirection);
	PlayerStatus getSpriteState();
	void setSpriteState(PlayerStatus spriteState);
	double getTargetVelX();
	void setTargetVelX(double targetVelX);
	int getScenarioWidth();
	void setScenarioWidth(int sw);
	int getScenarioHeight();
	void setScenarioHeight(int sh);
	void setIsJumping(bool isJumping);
	bool getIsJumping();
	double getGroundPos();
	void setGroundPos(double gPos);
	int getScrollSpeed();
	void setScrollSpeed(int scSpeed);
	PlayerType getPlayerType();
	void setPlayerType(PlayerType playerType);
	bool getIsConnected();
	void setIsConnected(bool isConnected);
	int getTime();
	void setTime(int time);
	void setTestMode(bool testMode);
	bool getTestMode();
	int getRings();
	void setRings(int rings);
	int getLives();
	void setLives(int lives);
	int getPoints();
	void setPoints(int points);
	bool getIsActive();
	void setIsActive(bool isActive);
	bool getHasShield();

	int getTeamPoints();
	void setTeamPoints(int teamPoints);
	int getTeamRings();
	void setTeamRings(int teamRings);
	bool getIsInvincible();
	void setIsInvincible(bool isInvincible);
	int getInvincibleTime();
	void setInvincibleTime(int ms);
	bool getIsRecovering();
	void setIsRecovering(bool isRecovering);
	int getRecoveringTime();
	void setRecoveringTime(int ms);

	string serializedPlayer;

	PlayerType calculatePlayerType();
	double calculateGroundPos(int windowHeight);

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	void serializePlayer();
	string serialize() override;
private:
	Vector2 position;
	Vector2 velocity;
	int width, height;
	int scenarioWidth, scenarioHeight;
	int scrollSpeed;
	double groundPos;
	bool isJumping;
	double targetVelX;
	FacingDirection facingDirection;
	int number;
	PlayerStatus spriteState;
	PlayerType playerType;
	bool isConnected;
	int time;
	bool testMode;

	int teamId;
	int teamPoints;
	int teamRings;

	int gameMode;
	unordered_map<int, int>* generalTeamPoints;
	unordered_map <int, int>* generalTeamRings;

	int rings;
	int lives;
	int points;
	bool isActive;
	bool hasShield;
	bool isInvincible;
	int invincibleTime;
	bool isRecovering;
	int recoveringTime;

	mutex playerMutex;
};

#endif // !PLAYER_H