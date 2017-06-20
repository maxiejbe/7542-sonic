#ifndef ENEMY_H
#define ENEMY_H

#include "../Player.h"
#include "../Entity.h"
#include "../common/EntityResolver.h"

//TODO: Enemy and player should hava a common parent class
//enum EnemyType {crab, bee, fish};

class Enemy : public Entity
{
public:
	Enemy(string);
	~Enemy();

	void copyFrom(Enemy&);

	Vector2 getVelocity();
	void setVelocity(Vector2 velocity);
	void incrementDistanceTravelled(double);
	double getDistanceTravelled();
	void resetDistanceTravelled();
	void handleKill(Player* player);

	double getMaxDistance();

	int getPoints();
	int getGivenPoints();
	int getLives();

	int getRecoveringTime();
	void setRecoveringTime(int ms);

	// Inherited via Serializable
	virtual void unserialize(Value* nodeRef);
	virtual char* getNodeName() override;

	void serialize(Writer<StringBuffer>& writer) override;
	// Inherited via Entity
	virtual void onCollision(Player* player, Camera* camera) override;
private:
	Vector2 velocity;
	int points;
	int lives;
	double distanceTravelled;
	int recoveringTime;

	void InitializeProperties();
	void bounce(Player * player);
	void bounceVertical(Player * player);
};

#endif

