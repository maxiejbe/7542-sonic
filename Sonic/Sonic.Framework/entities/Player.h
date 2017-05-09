#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Logger.h"
#include "../Vector2.h"
#include "../protocol/Message.h"

using namespace std;

enum FacingDirection { FACING_LEFT, FACING_RIGHT };

class Player : public Serializable
{
public:
	Player();
	Player(int windowHeight, int scenarioWidth, int scenarioHeight, int scrollSpeed) : Player() {
		this->groundPos = windowHeight / 1.35;
		this->position = Vector2(0, this->groundPos);

		this->scenarioWidth = scenarioWidth;
		this->scenarioHeight = scenarioHeight;
		this->scrollSpeed = scrollSpeed;
	}
	Player(Player&);

	void copyFrom(Player&);

	Vector2 getPosition();
	void setXPosition(double x);
	void setYPosition(double y);
	Vector2 getVelocity();
	void setXVelocity(double x);
	void setYVelocity(double y);
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
	void setFilePath(string filePath);
	string getFilePath();
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

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	int playerNumber;

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
	string filePath;
	PlayerType playerType;
};

#endif // !PLAYER_H