#include "Square.h"

Square::Square(int id, string type, string color, Dimensions dimensions, Coordinate coordinate, string imagePath, int zIndex)
{
	this->id = id;
	this->type = type;
	this->color = color;
	this->dimensions = dimensions;
	this->coordinate = coordinate;
	this->imagePath = imagePath;
	this->zIndex = zIndex;
}

void Square::draw(SDL_Rect camera) {
	Rectangle rectangle = Rectangle(id, type, color, dimensions, coordinate, imagePath, zIndex);
	rectangle.draw(camera);
}