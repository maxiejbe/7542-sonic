#include "Square.h"

Square::Square() {
	//TODO
}

Square::Square(int x, int y, int w, LTexture texture) {
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	coordinate = Coordinate(x, y);
	dimensions = Dimensions(w, w, 0);
	gTexture = texture;
}

void Square::draw(SDL_Rect camera) {
	Rectangle rectangle = Rectangle(coordinate, dimensions, gTexture);
	rectangle.draw(camera);
}