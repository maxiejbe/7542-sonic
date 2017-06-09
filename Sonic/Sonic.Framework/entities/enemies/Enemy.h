#ifndef ENEMY_H
#define ENEMY_H

#include "../../Vector2.h"
#include "../Player.h"
#include <mutex>

//TODO: Enemy and player should hava a common parent class
enum EnemyType {crab, bee, fish};

class Enemy : public Serializable
{
public:
	Enemy();
	Enemy(double, double, double, double, EnemyType);
	~Enemy();
	
	Vector2 getPosition();
	Vector2 getVelocity();
	void setPositionX(double);
	void setPositionY(double);
	int getHeight();
	int getWidth();
	EnemyType getType();
	FacingDirection getFacingDirection();
	void setFacingDirection(FacingDirection);
	int getMaxDistance();
	void incrementDistanceTravelled(int);
	int getDistanceTravelled();
	void resetDistanceTravelled();
	bool isAlive();
	void kill();
	int getPoints();

	mutex enemyMutex;

	void serializeEnemy();
	string getSerializedEnemy();

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	Vector2 position;
	Vector2 velocity;
	int width;
	int height;
	bool alive;
	int points;
	EnemyType type;
	FacingDirection facingDirection;
	int maxDistance;
	int distanceTravelled;
	string serializedEnemy;

	void InitializeProperties();
};

#endif

