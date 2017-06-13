#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "common/Serializable.h"
#include "common/Validator.h"
#include "../Logger.h"

class Dimensions : public Serializable {
public:
	Dimensions();
	Dimensions(int width, int height, int radio);

	void setDefaults(int width, int height, int radio);
	
	int getWidth();
	int getHeight();
	int getRadio();

	void serialize(Writer<StringBuffer>&writer);
	// Inherited via Serializable
	virtual string serialize() override;
	virtual void unserialize(Value * parentNode) override;
	virtual char* getNodeName() override;
private:
	int width;
	int height;
	int radio;

	int defaultWidth;
	int defaultHeight;
	int defaultRadio;
};

#endif