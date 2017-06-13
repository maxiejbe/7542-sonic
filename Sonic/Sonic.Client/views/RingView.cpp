#include "RingView.h"

void RingView::draw(int camX, int camY)
{
	// Load image
	if (texture.getTexture() == nullptr && !texture.loadFromFile("img/ring.png")) {
		LOG(logWARNING) << "No se pudo cargar la imagen del anillo '" << "img/ring.png" << "'.";
		return;
	}

	int x = entity->getCoordinate().getX() - camX;
	int y = entity->getCoordinate().getY() - camY;
	int w = entity->getDimensions().getWidth() * 1.5;
	int h = entity->getDimensions().getHeight() * 1.5;

	texture.render(x, y, w, h);
}

