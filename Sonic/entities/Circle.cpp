#include "Circle.h"

const int CIRCLE_DEFAULT_WIDTH = 0;
const int CIRCLE_DEFAULT_HEIGHT = 0;
const int CIRCLE_DEFAULT_RADIO = 50;

Circle::Circle()
{
}

Circle::Circle(Entity* entity) : Entity(entity) {
	cropperInitialized = false;
}

void Circle::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {

		// Check if there is an image
		if (imagePath.empty()) {
			// Draw color
			int positionX = (coordinate.getX() + dimensions.getRadio()) - camera.x;
			int positionY = (coordinate.getY() + dimensions.getRadio()) - camera.y;
			Uint8 r, g, b, a;
			SDL_GetRGBA(getColorRgba(), SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, &r, &g, &b, &a);
			filledCircleRGBA(gRenderer, positionX, positionY, dimensions.getRadio(), r, g, b, a); // TODO color
			return;
		}

		// Try to load the image
		if (texture.getTexture() == nullptr && !texture.loadFromFile(imagePath)) {
			this->imagePath = "img/image-not-found.png";
		}

		// Draw image
		drawWithImage(camera);
	}
	else {
		//TODO: log errors
	}
}

void Circle::initializeCropper() {
	if (!cropperInitialized) {
		bool cropperInitialization = imgCropper.crop(dimensions.getRadio(), imagePath, getColorRgba());
		if (!cropperInitialization) {
			throw std::exception();
			// TODO log
		}
		cropperInitialized = true;
	}
}

void Circle::drawWithImage(SDL_Rect camera) {
	//crop image and render
	try {
		if (!cropperInitialized) {
			initializeCropper();
		}

		imgCropper.render(coordinate.getX() - camera.x, coordinate.getY() - camera.y);
	}
	catch (std::exception e) {
		LOG(logERROR) << "No se pudo cropear la imagen dentro del circulo";
	}

}

Dimensions Circle::getDefaultDimensions()
{
	return Dimensions(CIRCLE_DEFAULT_WIDTH, CIRCLE_DEFAULT_HEIGHT, CIRCLE_DEFAULT_RADIO);
}
