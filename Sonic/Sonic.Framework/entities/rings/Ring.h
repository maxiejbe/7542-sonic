#ifndef RING_H
#define RING_H

#include "../Entity.h"

class Ring : public Entity
{
public:
	Ring(string);
	~Ring();

	virtual void onCollision(Player* player) override;
private:

};

#endif
