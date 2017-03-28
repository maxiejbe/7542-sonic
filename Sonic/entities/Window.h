#include "Dimensions.h"

class Window {
public:
	Window();
	Window(Dimensions dimensions);

	Dimensions GetDimensions();
private:
	Dimensions* dimensions;
};
