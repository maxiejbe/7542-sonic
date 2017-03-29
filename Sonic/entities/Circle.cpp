#include "Circle.h"

Circle::Circle(int x, int y, int radio) {
	coordinate = Coordinate(x, y);
	dimensions = Dimensions(0, 0, radio);
}

Circle::Circle() {

}

void Circle::draw(SDL_Rect camera){
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {
		filledCircleRGBA(gRenderer, coordinate.getX() - camera.x, coordinate.getY() - camera.y, dimensions.getRadio(), 0x00, 0xFF, 0x00, 0xFF);
	}
	else {
		//TODO: log errors
	}
}

