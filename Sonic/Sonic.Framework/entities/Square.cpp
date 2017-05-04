#include "Square.h"

const int SQUARE_DEFAULT_WIDTH = 100;
const int SQUARE_DEFAULT_HEIGHT = 100;
const int SQUARE_DEFAULT_RADIO = 0;

Square::Square()
{
}

Dimensions Square::getDefaultDimensions()
{
	return Dimensions(SQUARE_DEFAULT_WIDTH, SQUARE_DEFAULT_HEIGHT, SQUARE_DEFAULT_RADIO);
}
