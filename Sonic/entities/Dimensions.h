#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "common/Serializable.h"
#include "common/Validator.h"
#include <Logger.h>

class Dimensions : public Serializable {
public:
	Dimensions();
	Dimensions(int width, int height, int radio);

	void SetDefaults(int width, int height, int radio);
	
	int getWidth();
	int getHeight();
	int getRadio();
private:
	int width;
	int height;
	int radio;

	int defaultWidth;
	int defaultHeight;
	int defaultRadio;

	// Inherited via Serializable
	virtual void Unserialize(Value * parentNode) override;
	virtual char* GetNodeName() override;
};

#endif