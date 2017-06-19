#include "RingView.h"

RingView::~RingView()
{
	if (this->spriteClips != nullptr) {
		delete this->spriteClips;
	}
	if (this->entity == nullptr) return;
	delete this->entity;
}

void RingView::draw(int camX, int camY)
{
	// Load image
	if (texture.getTexture() == nullptr && this->entity->getIsActive() && !texture.loadFromFile("img/rings-spritesheets.png")) {
		LOG(logWARNING) << "No se pudo cargar la imagen del anillo '" << "img/rings-spritesheets.png" << "'.";
		return;
	}

	if (!this->entity->getIsActive()) {
		if (texture.getTexture() == nullptr) return;
		texture.free();
	}

	if (entity->getId() >= 0) {
		// Calculate current sprite
		Uint32 sprite = (this->entity->getTime() / 120) % 4;

		SDL_Rect* currentClip = &spriteClips[sprite];

		int x = entity->getCoordinate().getX() - camX;
		int y = entity->getCoordinate().getY() - camY;
		int w = currentClip->w;
		int h = currentClip->h;

		// Scale
		SDL_Rect dest = { x, y, w, h };

		texture.render(x, y, currentClip, dest, 0, NULL, SDL_FLIP_NONE);
	}
}

void RingView::loadSpriteClips()
{
	spriteClips = new SDL_Rect[4];

	// 1
	spriteClips[0].x = 8;
	spriteClips[0].y = 45;
	spriteClips[0].w = 32;
	spriteClips[0].h = 34;

	// 3
	spriteClips[1].x = 80;// 83;
	spriteClips[1].y = 45;
	spriteClips[1].w = 32;// 26;
	spriteClips[1].h = 34;

	// 4
	spriteClips[2].x = 109;// 117;
	spriteClips[2].y = 45;
	spriteClips[2].w = 32;// 14;
	spriteClips[2].h = 34;

	// 2
	spriteClips[3].x = 44;// 47;
	spriteClips[3].y = 45;
	spriteClips[3].w = 32;// 26;
	spriteClips[3].h = 34;
}

