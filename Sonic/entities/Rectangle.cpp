#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h, LTexture texture) {
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	coordinate = Coordinate(x, y);
	dimensions = Dimensions(w, h, 0);
	gTexture = texture;
}

Rectangle::Rectangle(Coordinate coordinate, Dimensions dimensions, LTexture texture) {
	this->coordinate = coordinate;
	this->dimensions = dimensions;
	this->gTexture = texture;
}

void Rectangle::draw(SDL_Rect camera) {
	//Show the tile
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	
	if ( gRenderer != NULL) {
		int x1 = coordinate.getX() - camera.x;
		int x2 = x1 + dimensions.getWidth();
		int y1 = coordinate.getY() - camera.y;
		int y2 = y1 + dimensions.getHeight();
		boxRGBA(gRenderer,x1,y1,x2,y2, 0x00, 0xFF, 0x00, 0xFF);

		//Crop texture (mostrar imagen con las mismas dimensiones que la entidad). Falta hacer si la entidad no trae imagen, chequeo de textura null
		int textureW = gTexture.getWidth();
		int textureH = gTexture.getHeight();
		int widthR = dimensions.getWidth();
		int heightR = dimensions.getHeight();

		if (textureW > widthR) { textureW = widthR; }
		if (textureH > heightR) { textureH = heightR; }

		SDL_Rect cropTexture = { x1, y1, x1 + textureW, y1 + textureH };
		gTexture.render(x1, y1, &cropTexture);
	}else {
		//TODO: log errors
	}
}

