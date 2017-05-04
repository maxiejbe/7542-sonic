#include "CircleView.h"

void CircleView::draw(SDL_Rect camera) {
	SDL_Renderer * gRenderer = Renderer::getInstance().gRenderer;
	if (gRenderer != NULL) {

		Coordinate coordinate = this->entity->getCoordinate();
		Dimensions dimensions = this->entity->getDimensions();
		string imagePath = this->entity->getImagePath();

		// Check if there is an image
		if (imagePath.empty()) {
			// Draw color
			int positionX = (coordinate.getX() + dimensions.getRadio()) - camera.x;
			int positionY = (coordinate.getY() + dimensions.getRadio()) - camera.y;
			Uint8 r, g, b, a;
			SDL_GetRGBA(getColorRgba(), SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, &r, &g, &b, &a);
			filledCircleRGBA(gRenderer, positionX, positionY, dimensions.getRadio(), r, g, b, a);
			return;
		}

		// Try to load the image
		if (texture.getTexture() == nullptr && !texture.loadFromFile(imagePath)) {
			this->entity->setImagePath("img/image-not-found.png");
		}

		// Draw image
		drawWithImage(camera);
	}
	else {
		LOG(logERROR) << "No se pudo dibujar el circulo. El renderer es nulo.";
	}
}

void CircleView::initializeCropper() {
	Dimensions dimensions = this->entity->getDimensions();
	string imagePath = this->entity->getImagePath();

	if (!cropperInitialized) {
		bool cropperInitialization = imgCropper.crop(dimensions.getRadio(), imagePath, getColorRgba());
		if (!cropperInitialization) {
			throw exception();
		}
		cropperInitialized = true;
	}
}

void CircleView::drawWithImage(SDL_Rect camera) {
	try {
		if (!cropperInitialized) {
			initializeCropper();
		}

		Coordinate coordinate = this->entity->getCoordinate();
		imgCropper.render(coordinate.getX() - camera.x, coordinate.getY() - camera.y);
	}
	catch (const exception& e) {
		LOG(logERROR) << "No se pudo cropear la imagen dentro del circulo: " << e.what();
	}

}
