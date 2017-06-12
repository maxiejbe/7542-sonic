#include "BonusView.h"

void BonusView::draw(SDL_Rect camera) {

	// TODO: mtebele - seguir
	//// Check texture
	//if (this->texture.getTexture() == nullptr && !this->texture.loadFromFile("img/monitors-spritesheet.png")) {
	//	LOG(logWARNING) << "No se pudo cargar la imagen del bonus 'img/monitors-spritesheet.png'.";
	//	return;
	//}

	//// Calculate current sprite
	//Uint32 sprite = (this->player->getTime() / 2) % 2;

	//SDL_Rect* currentClip = &spriteClips[player->getSpriteState()][sprite];

	//// Scale
	//SDL_Rect dest = { (int)(player->getPosition().x - camera.x), (int)(player->getPosition().y - camera.y), currentClip->w * 2, currentClip->h * 2 };

	//// Calculate facing direction
	//SDL_RendererFlip flip = (this->player->getFacingDirection() == FACING_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	//texture.render((int)(player->getPosition().x - camera.x), (int)(player->getPosition().y - camera.y), currentClip, dest, 0, NULL, flip);

	RectangleView::draw(camera);
}
//
//// TODO: mtebele - seguir
//void BonusView::loadSpriteClips()
//{
//	switch (this->player->getPlayerType()) {
//	case RING:
//		spriteClips = new SDL_Rect *[ANIMATION_STATES];
//		for (int count = 0; count < ANIMATION_STATES; count++) {
//			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_SONIC];
//		}
//
//		// Idle
//		spriteClips[PlayerStatus::idle][0].x = 5;
//		spriteClips[PlayerStatus::idle][0].y = 12;
//		spriteClips[PlayerStatus::idle][0].w = 25;
//		spriteClips[PlayerStatus::idle][0].h = 39;
//
//		break;
//
//	case INVINCIBILITY:
//		spriteClips = new SDL_Rect *[ANIMATION_STATES];
//		for (int count = 0; count < ANIMATION_STATES; count++) {
//			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_TAILS];
//		}
//
//		// idle
//		spriteClips[PlayerStatus::idle][0].x = 23;
//		spriteClips[PlayerStatus::idle][0].y = 14;
//		spriteClips[PlayerStatus::idle][0].w = 36;
//		spriteClips[PlayerStatus::idle][0].h = 31;
//		break;
//
//	case SHIELD:
//		spriteClips = new SDL_Rect *[ANIMATION_STATES];
//		for (int count = 0; count < ANIMATION_STATES; count++) {
//			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_KNUCKLES];
//		}
//
//		// Idle
//		spriteClips[PlayerStatus::idle][0].x = 1;
//		spriteClips[PlayerStatus::idle][0].y = 1;
//		spriteClips[PlayerStatus::idle][0].w = 26;
//		spriteClips[PlayerStatus::idle][0].h = 39;
//		break;
//	}
//}