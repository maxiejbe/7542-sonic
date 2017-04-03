#include "Rectangle.h"

void Rectangle::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;	
	if ( gRenderer != NULL) {
		int x1 = coordinate.getX() - camera.x;
		int x2 = x1 + dimensions.getWidth();
		int y1 = coordinate.getY() - camera.y;
		int y2 = y1 + dimensions.getHeight();
		boxRGBA(gRenderer, x1, y1, x2, y2, 0x00, 0xFF, 0x00, 0xFF);

		if (!texture.loadFromFile(imagePath)) {
			LOG(logWARNING) << "No se pudo cargar la imagen '" << imagePath << "'. Se tomará una por defecto.";
			//TODO: tomar por defecto
		}
		else {
			x1 = coordinate.getX() - camera.x;
			y1 = coordinate.getY() - camera.y;
			SDL_Rect dstrect = { x1, y1, min(texture.getWidth(), dimensions.getWidth()) , min(texture.getHeight(), dimensions.getHeight()) };
			SDL_Rect croprect = { 0, 0, min(texture.getWidth(), dimensions.getWidth()), min(texture.getHeight(), dimensions.getHeight()) };
			SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), &croprect, &dstrect);
		}
	}
	else {
		//TODO: log errors
	}
}

