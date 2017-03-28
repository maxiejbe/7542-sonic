#ifndef WINDOW_H
#define WINDOW_H

#include "Dimensions.h"
#include "common/Serializable.h"

class Window: public Serializable {
public:
	Window();
	Window(Dimensions dimensions);

	Dimensions GetDimensions();
private:
	Dimensions dimensions;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif
