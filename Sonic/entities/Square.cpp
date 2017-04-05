#include "Square.h"

const int SQUARE_DEFAULT_WIDTH = 100;
const int SQUARE_DEFAULT_HEIGHT = 100;
const int SQUARE_DEFAULT_RADIO = 0;

Square::Square()
{
}

void Square::draw(SDL_Rect camera) {
	rectangle.draw(camera);
}

Dimensions Square::GetDefaultDimensions()
{
	return Dimensions(SQUARE_DEFAULT_WIDTH, SQUARE_DEFAULT_HEIGHT, SQUARE_DEFAULT_RADIO);
}
