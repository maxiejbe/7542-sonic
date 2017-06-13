#include "EnemyView.h"

const int ANIMATION_MAX_FRAMES_FISH = 2;
const int ANIMATION_MAX_FRAMES_FLY = 1;
const int ANIMATION_MAX_FRAMES_CRAB = 4;

EnemyView::EnemyView(Enemy * enemy)
{
	//this->enemy = enemy;
	loadSpriteClips();
}

EnemyView::~EnemyView()
{
}

void EnemyView::draw(SDL_Rect camera)
{
	// Load image
	if (texture.getTexture() == nullptr && !texture.loadFromFile("img/enemies-spritesheet.png")) {
		LOG(logWARNING) << "No se pudo cargar la imagen del bonus '" << "img/enemies-spritesheet.png" << "'.";
		return;
	}

	// Calculate current sprite
	//Uint32 sprite = (this->entity->getTime() / getFramesDivision(this->player->getSpriteState())) % getFramesCount(this->player->getSpriteState()); //90
	Uint32 sprite = 0;// (this->entity->getTime() / 85) % getFramesCount();

	SDL_Rect* currentClip = &spriteClips[sprite];

	// Scale
	SDL_Rect dest = { (int)(this->entity->getCoordinate().getX() - camera.x),
		(int)(this->entity->getCoordinate().getY() - camera.y),
		currentClip->w * 2,
		currentClip->h * 2 };

	// Calculate facing direction
	SDL_RendererFlip flip = /*(this->entity->getFacingDirection() == FACING_RIGHT) ?*/ SDL_FLIP_NONE;// : SDL_FLIP_HORIZONTAL;

	int x = this->entity->getCoordinate().getX() - camera.x;
	int y = this->entity->getCoordinate().getY() - camera.y;

	texture.render(x, y, currentClip, dest, 0, NULL, flip);
}

int EnemyView::getFramesCount()
{
	string type = this->entity->getType();

	if (type == EntityResolver::toTypeString(EntityType::enemigo_pez))
		return ANIMATION_MAX_FRAMES_FISH;
	else if (type == EntityResolver::toTypeString(EntityType::enemigo_mosca))
		return ANIMATION_MAX_FRAMES_FLY;
	else if (type == EntityResolver::toTypeString(EntityType::enemigo_cangrejo))
		return ANIMATION_MAX_FRAMES_CRAB;

	return 0;
}

void EnemyView::loadSpriteClips()
{
	string type = this->entity->getType();

	if (type == EntityResolver::toTypeString(EntityType::enemigo_pez)) {
		spriteClips = new SDL_Rect[ANIMATION_MAX_FRAMES_FISH];

		spriteClips[0].x = 0;
		spriteClips[0].y = 0;
		spriteClips[0].w = 30;
		spriteClips[0].h = 32;

		spriteClips[1].x = 33;
		spriteClips[1].y = 0;
		spriteClips[1].w = 29;
		spriteClips[1].h = 31;
	}
	else if (type == EntityResolver::toTypeString(EntityType::enemigo_mosca)) {
		spriteClips = new SDL_Rect[ANIMATION_MAX_FRAMES_FLY];

		spriteClips[0].x = 129;
		spriteClips[0].y = 0;
		spriteClips[0].w = 45;
		spriteClips[0].h = 19;
	}
	else if (type == EntityResolver::toTypeString(EntityType::enemigo_cangrejo)) {
		spriteClips = new SDL_Rect[ANIMATION_MAX_FRAMES_CRAB];

		spriteClips[0].x = 237;
		spriteClips[0].y = 0;
		spriteClips[0].w = 42;
		spriteClips[0].h = 31;

		spriteClips[1].x = 284;
		spriteClips[1].y = 0;
		spriteClips[1].w = 44;
		spriteClips[1].h = 31;

		spriteClips[2].x = 236;
		spriteClips[2].y = 32;
		spriteClips[2].w = 44;
		spriteClips[2].h = 38;

		spriteClips[3].x = 285;
		spriteClips[3].y = 32;
		spriteClips[3].w = 42;
		spriteClips[3].h = 35;
	}
}