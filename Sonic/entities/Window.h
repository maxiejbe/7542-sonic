#ifndef WINDOW_H
#define WINDOW_H

#include "Dimensions.h"
#include "common/Serializable.h"

class Window: public Serializable {
public:
	Window();
	Window(Dimensions dimensions);

	int getWidth();
	int getHeight();
private:
	Dimensions dimensions;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif
