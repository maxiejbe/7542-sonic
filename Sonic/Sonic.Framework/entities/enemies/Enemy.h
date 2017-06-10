#ifndef ENEMY_H
#define ENEMY_H

#include "../Player.h"
#include "../Entity.h"
#include <mutex>

//TODO: Enemy and player should hava a common parent class
//enum EnemyType {crab, bee, fish};

class Enemy : public Entity
{
public:
	Enemy(string);
	~Enemy();
	
	Vector2 getVelocity();
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
	virtual void unserialize(Value* nodeRef);
	virtual char* getNodeName() override;
	virtual string serialize() override;
	// Inherited via Entity
	virtual void onCollision(Player* player) override;
private:
	Vector2 velocity;
	bool alive;
	int points;
	FacingDirection facingDirection;
	int maxDistance;
	int distanceTravelled;
	string serializedEnemy;

	void InitializeProperties();
};

#endif

