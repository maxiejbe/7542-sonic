#include "Dimensions.h"

class Window {
public:
	void SetDimensions(Dimensions dimensionsParam);
	Dimensions GetDimensions();
private:
	Dimensions dimensions;
};
