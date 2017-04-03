#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h) {
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	coordinate = Coordinate(x, y);
	dimensions = Dimensions(w, h, 0);
}

Rectangle::Rectangle(Coordinate coordinate, Dimensions dimensions) {
	this->coordinate = coordinate;
	this->dimensions = dimensions;
}

void Rectangle::draw(SDL_Rect camera) {
	//Show the tile
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;	
	if ( gRenderer != NULL) {
		int x1 = coordinate.getX() - camera.x;
		int x2 = x1 + dimensions.getWidth();
		int y1 = coordinate.getY() - camera.y;
		int y2 = y1 + dimensions.getHeight();
		// Fixme
		//boxRGBA(gRenderer,x1,y1,x2,y2, 0x00, 0xFF, 0x00, 0xFF);
	}else {
		//TODO: log errors
	}
}

