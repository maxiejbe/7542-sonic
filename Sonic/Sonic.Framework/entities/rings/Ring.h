#ifndef RING_H
#define RING_H

#include "../Entity.h"

class Ring : public Entity
{
public:
	Ring(string);
	~Ring();

	void serialize(Writer<StringBuffer>& writer) override;

	virtual void onCollision(Player* player, Camera* camera) override;
private:

};

#endif
