#include "PlayerView.h"
#include "SDLWindow.h"

const int ANIMATION_STATES = 4;
const int ANIMATION_FRAMES = 8;
SDL_Rect spriteClips[ANIMATION_STATES][ANIMATION_FRAMES];


PlayerView::PlayerView(Player* player)
{
	this->player = player;

	spriteClips[PlayerStatus::idle][0].x = 5;
	spriteClips[PlayerStatus::idle][0].y = 12;
	spriteClips[PlayerStatus::idle][0].w = 25;
	spriteClips[PlayerStatus::idle][0].h = 39;

	// PlayerStatus::walking
	spriteClips[PlayerStatus::walking][0].x = 191;
	spriteClips[PlayerStatus::walking][0].y = 109;
	spriteClips[PlayerStatus::walking][0].w = 23;
	spriteClips[PlayerStatus::walking][0].h = 39;

	spriteClips[PlayerStatus::walking][1].x = 221;
	spriteClips[PlayerStatus::walking][1].y = 109;
	spriteClips[PlayerStatus::walking][1].w = 29;
	spriteClips[PlayerStatus::walking][1].h = 40;

	spriteClips[PlayerStatus::walking][2].x = 263;
	spriteClips[PlayerStatus::walking][2].y = 109;
	spriteClips[PlayerStatus::walking][2].w = 39;
	spriteClips[PlayerStatus::walking][2].h = 40;

	spriteClips[PlayerStatus::walking][3].x = 308;
	spriteClips[PlayerStatus::walking][3].y = 109;
	spriteClips[PlayerStatus::walking][3].w = 39;
	spriteClips[PlayerStatus::walking][3].h = 39;

	spriteClips[PlayerStatus::walking][4].x = 352;
	spriteClips[PlayerStatus::walking][4].y = 109;
	spriteClips[PlayerStatus::walking][4].w = 23;
	spriteClips[PlayerStatus::walking][4].h = 39;

	spriteClips[PlayerStatus::walking][5].x = 378;
	spriteClips[PlayerStatus::walking][5].y = 109;
	spriteClips[PlayerStatus::walking][5].w = 25;
	spriteClips[PlayerStatus::walking][5].h = 40;

	spriteClips[PlayerStatus::walking][6].x = 411;
	spriteClips[PlayerStatus::walking][6].y = 109;
	spriteClips[PlayerStatus::walking][6].w = 40;
	spriteClips[PlayerStatus::walking][6].h = 38;

	spriteClips[PlayerStatus::walking][7].x = 460;
	spriteClips[PlayerStatus::walking][7].y = 109;
	spriteClips[PlayerStatus::walking][7].w = 39;
	spriteClips[PlayerStatus::walking][7].h = 39;

	// PlayerStatus::running
	spriteClips[PlayerStatus::running][0].x = 10;
	spriteClips[PlayerStatus::running][0].y = 155;
	spriteClips[PlayerStatus::running][0].w = 28;
	spriteClips[PlayerStatus::running][0].h = 36;

	spriteClips[PlayerStatus::running][1].x = 44;
	spriteClips[PlayerStatus::running][1].y = 154;
	spriteClips[PlayerStatus::running][1].w = 29;
	spriteClips[PlayerStatus::running][1].h = 36;

	spriteClips[PlayerStatus::running][2].x = 82;
	spriteClips[PlayerStatus::running][2].y = 154;
	spriteClips[PlayerStatus::running][2].w = 28;
	spriteClips[PlayerStatus::running][2].h = 36;

	spriteClips[PlayerStatus::running][3].x = 116;
	spriteClips[PlayerStatus::running][3].y = 154;
	spriteClips[PlayerStatus::running][3].w = 29;
	spriteClips[PlayerStatus::running][3].h = 36;

	// PlayerStatus::jumping
	spriteClips[PlayerStatus::jumping][0].x = 386;
	spriteClips[PlayerStatus::jumping][0].y = 74;
	spriteClips[PlayerStatus::jumping][0].w = 27;
	spriteClips[PlayerStatus::jumping][0].h = 30;

	spriteClips[PlayerStatus::jumping][1].x = 417;
	spriteClips[PlayerStatus::jumping][1].y = 77;
	spriteClips[PlayerStatus::jumping][1].w = 30;
	spriteClips[PlayerStatus::jumping][1].h = 27;

	spriteClips[PlayerStatus::jumping][2].x = 452;
	spriteClips[PlayerStatus::jumping][2].y = 75;
	spriteClips[PlayerStatus::jumping][2].w = 27;
	spriteClips[PlayerStatus::jumping][2].h = 30;

	spriteClips[PlayerStatus::jumping][3].x = 481;
	spriteClips[PlayerStatus::jumping][3].y = 77;
	spriteClips[PlayerStatus::jumping][3].w = 30;
	spriteClips[PlayerStatus::jumping][3].h = 27;
}

void PlayerView::render(int camX, int camY)
{
	// Check texture
	if (this->texture.getTexture() == nullptr && !this->texture.loadFromFile(this->player->getFilePath())) {
		LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << this->player->getFilePath() << "'.";
		return;
	}

	// Calculate current sprite
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % getFramesCount(this->player->getSpriteState());

	SDL_Rect* currentClip = &spriteClips[player->getSpriteState()][sprite];

	// Scale
	SDL_Rect dest = { (int)(player->getPosition().x - camX), (int)(player->getPosition().y - camY), currentClip->w * 2, currentClip->h * 2 };
	//SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), currentClip, &dest);

	// Set dimensions
	this->player->setWidth(dest.w);
	this->player->setHeight(dest.h);

	// Calculate facing direction
	SDL_RendererFlip flip = (this->player->getFacingDirection() == FACING_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	texture.render((int)(player->getPosition().x - camX), (int)(player->getPosition().y - camY), currentClip, dest, 0, NULL, flip);
}

int PlayerView::getFramesCount(PlayerStatus status)
{
	switch (status) {
	case idle:
		return 1;
	case walking:
		return 8;
	case running:
		return 4;
	case jumping:
		return 4;
	default:
		return 1;
	}
}