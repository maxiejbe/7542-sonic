#include "Square.h"

const int SQUARE_DEFAULT_WIDTH = 100;
const int SQUARE_DEFAULT_HEIGHT = 100;
const int SQUARE_DEFAULT_RADIO = 0;

Square::Square()
{
}

void Square::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {
		rectangle.draw(camera);
	}
	else {
		LOG(logERROR) << "No se pudo dibujar el cuadrado. El renderer es nulo.";
	}
}

Dimensions Square::getDefaultDimensions()
{
	return Dimensions(SQUARE_DEFAULT_WIDTH, SQUARE_DEFAULT_HEIGHT, SQUARE_DEFAULT_RADIO);
}
