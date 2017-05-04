#include "Circle.h"

const int CIRCLE_DEFAULT_WIDTH = 0;
const int CIRCLE_DEFAULT_HEIGHT = 0;
const int CIRCLE_DEFAULT_RADIO = 50;

Dimensions Circle::getDefaultDimensions()
{
	return Dimensions(CIRCLE_DEFAULT_WIDTH, CIRCLE_DEFAULT_HEIGHT, CIRCLE_DEFAULT_RADIO);
}
