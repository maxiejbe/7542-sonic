#include "CircleImageCropper.h"

CircleImageCropper::CircleImageCropper()
{
	radio = 0;
	targetTexture = NULL;
}

CircleImageCropper::~CircleImageCropper()
{
	free();
}

void CircleImageCropper::free() {
	if (targetTexture != NULL) {
		SDL_DestroyTexture(targetTexture);
		targetTexture = NULL;
	}
}

bool CircleImageCropper::crop(int radio, string imgPath, Uint32 backgroundColor)
{
	StreamingTexture imageTexture;
	if (!imageTexture.loadFromFile(imgPath)) {
		LOG(logERROR) << "No se pudo cargar la textura dentro del circulo.";
		return false;
	}
	else {
		if (!initializeTargetTexture(radio)) {
			LOG(logERROR) << "No se pudo inicializar la textura de la imagen del circulo.";
			imageTexture.free();
			return false;
		}
		else {
			int width = radio * 2;
			int heigth = radio * 2;
			imageTexture.lockTexture();
			Uint32* imgPixels = (Uint32*)imageTexture.getPixels();
			int imageWidth = imageTexture.getPitch() / 4;
			int imageHeight = imageTexture.getHeight();
			int pixelCount = imageTexture.getPitch() * imageTexture.getHeight();
			int imgCircleCenterX = imageWidth / 2;
			int imgCircleCenterY = imageTexture.getHeight() / 2;

			int circleCenterX = radio;
			int circleCenterY = radio;

			int imgXPos = 0;
			int imgYPos = 0;
			int currentPosition = 0;
			Uint8 imgR, imgG, imgB, imgA;
			Uint8 r, g, b, a;
			int currentY = 0;

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < heigth; y++) {
					if (isInCircle(circleCenterX, circleCenterY, x, y)) {
						imgXPos = (imgCircleCenterY - radio) + y;
						imgYPos = (imgCircleCenterX - radio) + x;
						currentPosition = (imgXPos * imageWidth) + imgYPos;
						if (imgXPos >= 0 && imgYPos >= 0 && imgYPos <= imageWidth && imgXPos <= imageHeight && currentPosition > 0 && currentPosition < pixelCount) {
							SDL_GetRGBA(imgPixels[currentPosition], SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, &imgR, &imgG, &imgB, &imgA);
							if (imgR == 0 && imgG == 0 && imgB == 0 && imgA == 255) {
								SDL_GetRGBA(backgroundColor, SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, &r, &g, &b, &a);
								drawPoint(x, y, r, g, b, a);
							}
							else {
								drawPoint(x, y, imgR, imgG, imgB, imgA);
							}
						}
						else {
							SDL_GetRGBA(backgroundColor, SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, &r, &g, &b, &a);
							drawPoint(x, y, r, g, b, a);
						}
					}
				}
			}

			imageTexture.unlockTexture();
			imageTexture.free();

			SDL_SetRenderTarget(Renderer::getInstance().gRenderer, NULL);
			return true;
		}
	}
}

bool CircleImageCropper::initializeTargetTexture(int radio) {
	free();

	targetTexture = SDL_CreateTexture(Renderer::getInstance().gRenderer, SDL_GetWindowPixelFormat(SDLWindow::getInstance().gWindow), SDL_TEXTUREACCESS_TARGET, radio * 2, radio * 2);
	if (targetTexture != NULL) {
		this->radio = radio;
		SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Renderer::getInstance().gRenderer, targetTexture);
		// Set texture transparent
		SDL_SetRenderDrawColor(Renderer::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0);
		SDL_RenderClear(Renderer::getInstance().gRenderer);
		return true;
	}

	return false;
}

bool CircleImageCropper::isInCircle(int cx, int cy, int x, int y) {
	return (pow((x - cx), 2) + pow((y - cy), 2) <= pow(radio, 2));
}

void CircleImageCropper::drawPoint(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(Renderer::getInstance().gRenderer, r, g, b, a);
	SDL_RenderDrawPoint(Renderer::getInstance().gRenderer, x, y);
}

void CircleImageCropper::render(int x, int y) {
	if (targetTexture != NULL) {
		SDL_Rect position = { x, y, radio * 2 , radio * 2 };
		SDL_RenderCopy(Renderer::getInstance().gRenderer, targetTexture, NULL, &position);
	}
}