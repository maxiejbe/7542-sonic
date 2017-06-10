#ifndef RING_H
#define RING_H

#include "../Entity.h"

class Ring : public Entity
{
public:
	Ring();
	~Ring();

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:

};

#endif
