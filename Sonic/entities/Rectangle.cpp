#include "Rectangle.h"

void Rectangle::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {
		int x1 = coordinate.getX() - camera.x;
		int x2 = x1 + dimensions.getWidth();
		int y1 = coordinate.getY() - camera.y;
		int y2 = y1 + dimensions.getHeight();
		boxRGBA(gRenderer, x1, y1, x2, y2, 0x00, 0xFF, 0x00, 0xFF);

		if (!texture.loadFromFile(imagePath)) {
			this->imagePath = "img/image-not-found.png";
			this->imageCrop = false;
		}
		else {
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
	}
	else {
		//TODO: log errors
	}
}

