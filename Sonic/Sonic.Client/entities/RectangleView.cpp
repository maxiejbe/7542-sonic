#include "Rectangle.h"

const int RECTANGLE_DEFAULT_WIDTH = 200;
const int RECTANGLE_DEFAULT_HEIGHT = 250;
const int RECTANGLE_DEFAULT_RADIO = 0;

void Rectangle::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {
		// Draw color
		int x1 = coordinate.getX() - camera.x;
		int x2 = x1 + dimensions.getWidth();
		int y1 = coordinate.getY() - camera.y;
		int y2 = y1 + dimensions.getHeight();

		Uint8 r, g, b, a;
		SDL_GetRGBA(getColorRgba(), SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, &r, &g, &b, &a);
		boxRGBA(gRenderer, x1, y1, x2, y2, r, g, b, a);

		// Check if there is an image
		if (imagePath.empty()) return;

		// Try to load image
		if (texture.getTexture() == nullptr && !texture.loadFromFile(imagePath)) {
			this->imagePath = "img/image-not-found.png";
			this->imageCrop = true;
			return;
		}

		// Draw image
		x1 = coordinate.getX() - camera.x;
		y1 = coordinate.getY() - camera.y;

		SDL_Rect dstrect;
		SDL_Rect croprect;
		if (this->imageCrop) {
			dstrect = { x1, y1, min(texture.getWidth(), dimensions.getWidth()) , min(texture.getHeight(), dimensions.getHeight()) };
			croprect = { 0, 0, min(texture.getWidth(), dimensions.getWidth()), min(texture.getHeight(), dimensions.getHeight()) };
		}
		else {
			dstrect = { x1, y1, dimensions.getWidth() , dimensions.getHeight() };
			croprect = { 0, 0, dimensions.getWidth(), dimensions.getHeight() };
		}

		SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), &croprect, &dstrect);
	}
	else {
		LOG(logERROR) << "No se pudo dibujar el rectangulo. El renderer es nulo.";
	}
}

Dimensions Rectangle::getDefaultDimensions()
{
	return Dimensions(RECTANGLE_DEFAULT_WIDTH, RECTANGLE_DEFAULT_HEIGHT, RECTANGLE_DEFAULT_RADIO);
}

