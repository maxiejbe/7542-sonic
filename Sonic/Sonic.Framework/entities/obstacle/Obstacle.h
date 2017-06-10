#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../Entity.h"

class Obstacle : public Entity
{
public:
	Obstacle();
	~Obstacle();

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:

};

#endif