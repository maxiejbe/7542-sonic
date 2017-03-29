#include "Rectangle.h"

SDL_Rect Rectangle::getRenderRectangle(SDL_Rect camera)
{
	SDL_Rect rect;
	
	rect.x = coordinate.getX() - camera.x;
	rect.y = coordinate.getY() - camera.y;
	rect.w = dimensions.getWidth();
	rect.h = dimensions.getHeight();

	return rect;
}

Rectangle::Rectangle(int x, int y, int w, int h) {
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	coordinate = Coordinate(x, y);
	dimensions = Dimensions(w, h,0);
}

void Rectangle::draw(SDL_Rect camera) {
	//Show the tile
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if ( gRenderer != NULL) {
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_Rect rect = getRenderRectangle(camera);
		SDL_RenderFillRect(gRenderer, &rect);
	}else {
		//TODO: log errors
	}
}

