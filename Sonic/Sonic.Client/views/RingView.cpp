#include "RingView.h"

void RingView::draw(SDL_Rect camera)
{
	// Load image
	if (texture.getTexture() == nullptr && !texture.loadFromFile("img/ring.png")) {
		LOG(logWARNING) << "No se pudo cargar la imagen del anillo '" << "img/ring.png" << "'.";
		return;
	}

	int x = entity->getCoordinate().getX() - camera.x;
	int y = entity->getCoordinate().getY() - camera.y;

	texture.render(x, y, &camera);
}

