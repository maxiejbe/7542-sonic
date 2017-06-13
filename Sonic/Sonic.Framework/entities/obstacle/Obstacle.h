#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Entity.h"
#include "../common/EntityResolver.h"

class Obstacle : public Entity
{
public:
	Obstacle(string);
	~Obstacle();

	virtual void onCollision(Player* player) override;
private:

};

#endif