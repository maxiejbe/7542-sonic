#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "common/Serializable.h"

using namespace std;

class Layer : public Serializable {
public:
	Layer();
private:
	int id;
	int zIndex;
	string imagePath;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif