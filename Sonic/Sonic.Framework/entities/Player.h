#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Logger.h"
#include "../Vector2.h"
#include "../protocol/Message.h"

using namespace std;

enum FacingDirection { FACING_LEFT, FACING_RIGHT };

class Player
{
public:
	Player(int windowHeight, int scenarioWidth, int scenarioHeight, int scrollSpeed);

	Vector2 getPosition();
	void setXPosition(float x);
	void setYPosition(float y);
	Vector2 getVelocity();
	void setXVelocity(float x);
	void setYVelocity(float y);
	void setNumber(int number);
	int getNumber();
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);
	FacingDirection getFacingDirection();
	void setFacingDirection(FacingDirection facingDirection);
	PlayerStatus getSpriteState();
	void setSpriteState(PlayerStatus spriteState);
	string getFilePath();
	float getTargetVelX();
	void setTargetVelX(float targetVelX);
	int getScenarioWidth();
	int getScenarioHeight();
	void setIsJumping(bool isJumping);
	bool getIsJumping();
	float getGroundPos();
	int getScrollSpeed();
private:
	Vector2 position;
	Vector2 velocity;
	int width, height;
	int scenarioWidth, scenarioHeight;
	int scrollSpeed;
	float groundPos;
	bool isJumping;
	float targetVelX;
	FacingDirection facingDirection;
	int number;
	PlayerStatus spriteState;
	string filePath;
};

#endif // !PLAYER_H