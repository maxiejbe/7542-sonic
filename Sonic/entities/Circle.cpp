#include "Circle.h"

Circle::Circle(int id, string type, string color, Dimensions dimensions, Coordinate coordinate, string imagePath, int zIndex)
{
	this->id = id;
	this->type = type;
	this->color = color;
	this->dimensions = dimensions;
	this->coordinate = coordinate;
	this->imagePath = imagePath;
	this->zIndex = zIndex;
}

void Circle::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {
		filledCircleRGBA(gRenderer, coordinate.getX() - camera.x, coordinate.getY() - camera.y, dimensions.getRadio(), 0x00, 0xFF, 0x00, 0xFF);
	}
	else {
		//TODO: log errors
	}
}

