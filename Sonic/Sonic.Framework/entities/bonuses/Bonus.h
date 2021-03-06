#ifndef BONUS_H
#define BONUS_H

#include "../Entity.h"
#include "../common/EntityResolver.h"

const int SUPER_RING_GIVEN_POINTS = 10;

class Bonus : public Entity
{
public:
	Bonus(string);
	~Bonus();

	void serialize(Writer<StringBuffer>& writer) override;

	virtual void onCollision(Player* player, Camera* camera) override;
private:
	
};

#endif


