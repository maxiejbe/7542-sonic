#include "Rectangle.h"

const int RECTANGLE_DEFAULT_WIDTH = 200;
const int RECTANGLE_DEFAULT_HEIGHT = 250;
const int RECTANGLE_DEFAULT_RADIO = 0;

Dimensions Rectangle::getDefaultDimensions()
{
	return Dimensions(RECTANGLE_DEFAULT_WIDTH, RECTANGLE_DEFAULT_HEIGHT, RECTANGLE_DEFAULT_RADIO);
}

