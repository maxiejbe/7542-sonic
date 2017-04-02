#include "Square.h"

Square::Square() {
	//TODO
}

Square::Square(int x, int y, int w) {
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	coordinate = Coordinate(x, y);
	dimensions = Dimensions(w, w, 0);
}

void Square::draw(SDL_Rect camera) {
	Rectangle rectangle = Rectangle(coordinate, dimensions);
	rectangle.draw(camera);
}