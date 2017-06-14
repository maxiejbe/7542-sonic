#include "RingView.h"

void RingView::draw(int camX, int camY)
{
	// Load image
	if (texture.getTexture() == nullptr && this->entity->getIsActive() && !texture.loadFromFile("img/ring.png")) {
		LOG(logWARNING) << "No se pudo cargar la imagen del anillo '" << "img/ring.png" << "'.";
		return;
	}

	if (!this->entity->getIsActive()) {
		if (texture.getTexture() == nullptr) return;
		texture.free();
	}

	int x = entity->getCoordinate().getX() - camX;
	int y = entity->getCoordinate().getY() - camY;
	int w = entity->getDimensions().getWidth();
	int h = entity->getDimensions().getHeight();

	texture.render(x, y, w, h);
}

