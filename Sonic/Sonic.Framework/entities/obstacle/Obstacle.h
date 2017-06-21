#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Entity.h"
#include "../common/EntityResolver.h"

class Obstacle : public Entity
{
public:
	Obstacle(string);
	~Obstacle();

	void serialize(Writer<StringBuffer>& writer) override;
	virtual void onCollision(Player* player, Camera* camera) override;

private:

};

#endif