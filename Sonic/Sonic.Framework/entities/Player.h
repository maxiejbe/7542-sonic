#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Logger.h"
#include "../Vector2.h"
#include "Message.h"

using namespace std;

enum FacingDirection { FACING_LEFT, FACING_RIGHT };

class Player
{
public:
	Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed);

	Vector2 getPosition();
	Vector2 getVelocity();
	void setNumber(int number);
	int getNumber();
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);
	FacingDirection getFacingDirection();
	PlayerStatus getSpriteState();
	string getFilePath();
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