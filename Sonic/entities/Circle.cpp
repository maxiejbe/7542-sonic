#include "Circle.h"

Circle::Circle(Entity* entity): Entity(entity) {
		cropperInitialized = false;
}

void Circle::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {

		if (imagePath != "") {
			drawWithImage(camera);
		}
		else {
			int positionX = (coordinate.getX() + dimensions.getRadio()) - camera.x;
			int positionY = (coordinate.getY() + dimensions.getRadio()) - camera.y;
			filledCircleRGBA(gRenderer, positionX, positionY, dimensions.getRadio(), 0, 0, 0, 255);
		}
	}else {
		//TODO: log errors
	}
}


void Circle::initializeCropper() {
	if (!cropperInitialized) {
		bool cropperInitialization = imgCropper.crop(dimensions.getRadio(), imagePath);
		if (!cropperInitialization) {
			throw std::exception();
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
		LOG(logERROR) << "No se pudo cropear la imagen dentro del circulo'";
	}
	
}

