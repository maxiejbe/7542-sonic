#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "common/Serializable.h"

class Dimensions : public Serializable {
public:
	Dimensions();
	Dimensions(int width, int height, int radio);
	int getWidth();
	int getHeight();
	int getRadio();
private:
	int width;
	int height;
	int radio;

	// Inherited via Serializable
	virtual void Unserialize(Value * parentNode) override;
	virtual char* GetNodeName() override;
};

#endif