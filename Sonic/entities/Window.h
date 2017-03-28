#ifndef WINDOW_H
#define WINDOW_H

#include "Dimensions.h"

class Window {
public:
	Window();
	Window(Dimensions dimensions);

	Dimensions GetDimensions();
private:
	Dimensions* dimensions;
};

#endif