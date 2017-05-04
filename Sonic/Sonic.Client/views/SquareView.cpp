#include "SquareView.h"

void SquareView::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {
		rectangleView.draw(camera);
	}
	else {
		LOG(logERROR) << "No se pudo dibujar el cuadrado. El renderer es nulo.";
	}
}