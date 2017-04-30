#include "Player.h"
#include "SDLWindow.h"

enum Animation
{
	IDLE,
	WALK,
	RUN,
	JUMP
};

//Walking animation
const int WALKING_ANIMATION_FRAMES = 8;
SDL_Rect gSpriteClips[4][WALKING_ANIMATION_FRAMES];

int sprite_index = IDLE;  // Current animation
int frameDiv = 8;
SDL_RendererFlip flip = SDL_FLIP_NONE;
bool run = false;


Player::Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed)
{
	if (!texture.loadFromFile(filePath)) {
		LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << filePath << "'.";
	}
	else
	{
		// IDLE
		gSpriteClips[IDLE][0].x = 5;
		gSpriteClips[IDLE][0].y = 12;
		gSpriteClips[IDLE][0].w = 25;
		gSpriteClips[IDLE][0].h = 39;

		// WALK
		gSpriteClips[WALK][0].x = 191;
		gSpriteClips[WALK][0].y = 109;
		gSpriteClips[WALK][0].w = 23;
		gSpriteClips[WALK][0].h = 39;

		gSpriteClips[WALK][1].x = 221;
		gSpriteClips[WALK][1].y = 109;
		gSpriteClips[WALK][1].w = 29;
		gSpriteClips[WALK][1].h = 40;

		gSpriteClips[WALK][2].x = 263;
		gSpriteClips[WALK][2].y = 109;
		gSpriteClips[WALK][2].w = 39;
		gSpriteClips[WALK][2].h = 40;

		gSpriteClips[WALK][3].x = 308;
		gSpriteClips[WALK][3].y = 109;
		gSpriteClips[WALK][3].w = 39;
		gSpriteClips[WALK][3].h = 39;

		gSpriteClips[WALK][4].x = 352;
		gSpriteClips[WALK][4].y = 109;
		gSpriteClips[WALK][4].w = 23;
		gSpriteClips[WALK][4].h = 39;

		gSpriteClips[WALK][5].x = 378;
		gSpriteClips[WALK][5].y = 109;
		gSpriteClips[WALK][5].w = 25;
		gSpriteClips[WALK][5].h = 40;

		gSpriteClips[WALK][6].x = 411;
		gSpriteClips[WALK][6].y = 109;
		gSpriteClips[WALK][6].w = 40;
		gSpriteClips[WALK][6].h = 38;

		gSpriteClips[WALK][7].x = 460;
		gSpriteClips[WALK][7].y = 109;
		gSpriteClips[WALK][7].w = 39;
		gSpriteClips[WALK][7].h = 39;

		// RUN
		gSpriteClips[RUN][0].x = 10;
		gSpriteClips[RUN][0].y = 155;
		gSpriteClips[RUN][0].w = 28;
		gSpriteClips[RUN][0].h = 36;

		gSpriteClips[RUN][1].x = 44;
		gSpriteClips[RUN][1].y = 154;
		gSpriteClips[RUN][1].w = 29;
		gSpriteClips[RUN][1].h = 36;

		gSpriteClips[RUN][2].x = 82;
		gSpriteClips[RUN][2].y = 154;
		gSpriteClips[RUN][2].w = 28;
		gSpriteClips[RUN][2].h = 36;

		gSpriteClips[RUN][3].x = 116;
		gSpriteClips[RUN][3].y = 154;
		gSpriteClips[RUN][3].w = 29;
		gSpriteClips[RUN][3].h = 36;

		// JUMP
		gSpriteClips[JUMP][0].x = 386;
		gSpriteClips[JUMP][0].y = 74;
		gSpriteClips[JUMP][0].w = 27;
		gSpriteClips[JUMP][0].h = 30;

		gSpriteClips[JUMP][1].x = 417;
		gSpriteClips[JUMP][1].y = 77;
		gSpriteClips[JUMP][1].w = 30;
		gSpriteClips[JUMP][1].h = 27;

		gSpriteClips[JUMP][2].x = 452;
		gSpriteClips[JUMP][2].y = 75;
		gSpriteClips[JUMP][2].w = 27;
		gSpriteClips[JUMP][2].h = 30;

		gSpriteClips[JUMP][3].x = 481;
		gSpriteClips[JUMP][3].y = 77;
		gSpriteClips[JUMP][3].w = 30;
		gSpriteClips[JUMP][3].h = 27;
	}

	this->posX = x;
	this->posY = y;
	this->velX = velX;
	this->velY = velY;
	//this->width = 29;//texture.getWidth();
	//this->height = 36;// texture.getHeight();
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
	this->scrollSpeed = scrollSpeed;
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.key.repeat == 0) {
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				velY -= scrollSpeed;
				sprite_index = JUMP;
				frameDiv = 4;
				break;
				//case SDLK_DOWN:
				//	velY += scrollSpeed;
				//	sprite_index = RUN;
				//	frameDiv = 4;
				//	break;
			case SDLK_LEFT:
				velX -= scrollSpeed;
				sprite_index = run ? RUN : WALK;
				frameDiv = run ? 4 : 8;
				flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT:
				velX += scrollSpeed;
				sprite_index = run ? RUN : WALK;
				frameDiv = run ? 4 : 8;
				flip = SDL_FLIP_NONE;
				break;
			case SDLK_SPACE:
				run = true;
				if (sprite_index == WALK) {
					sprite_index = RUN;
					frameDiv = 4;
				}
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				velY += scrollSpeed;
				sprite_index = IDLE;
				frameDiv = 1;
				break;
				//case SDLK_DOWN:
				//	velY -= scrollSpeed;
				//	sprite_index = IDLE;
				//	frameDiv = 1;
				//	break;
			case SDLK_LEFT:
				velX += scrollSpeed;
				sprite_index = IDLE;
				frameDiv = 1;
				break;
			case SDLK_RIGHT:
				velX -= scrollSpeed;
				sprite_index = IDLE;
				frameDiv = 1;
				break;
			case SDLK_SPACE:
				run = false;
				if (sprite_index == RUN) {
					sprite_index = WALK;
					frameDiv = 8;
				}
				break;
			}
			break;
		}
	}
}

void Player::move(float timeStep)
{
	posX += velX * timeStep;

	if (posX < 0)
		posX = 0;
	else if (posX > scenarioWidth - width)
		posX = (float)(scenarioWidth - width);

	posY += velY * timeStep;

	if (posY < 0)
		posY = 0;
	else if (posY > scenarioHeight - height)
		posY = (float)(scenarioHeight - height);
}

void Player::render(int camX, int camY)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % frameDiv;

	SDL_Rect* currentClip = &gSpriteClips[sprite_index][sprite];

	// Scale
	SDL_Rect dest = { (int)(posX - camX), (int)(posY - camY), currentClip->w * 2, currentClip->h * 2 };
	//SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), currentClip, &dest);

	this->width = dest.w;
	this->height = dest.h;

	texture.render((int)(posX - camX), (int)(posY - camY), currentClip, dest, 0, NULL, flip);
}

float Player::getPosX()
{
	return this->posX;
}

float Player::getPosY()
{
	return this->posY;
}

int Player::getWidth()
{
	return this->texture.getWidth();
}

int Player::getHeight()
{
	return this->texture.getHeight();
}
