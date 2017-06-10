#ifndef BONUS_H
#define BONUS_H

#include "../Entity.h"

class Bonus : public Entity
{
public:
	Bonus();
	~Bonus();

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	
};

#endif


