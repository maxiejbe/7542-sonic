#include "Player.h"
#include "SDLWindow.h"

enum Animation
{
	IDLE,
	WALK,
	RUN,
	JUMP
};

const int ANIMATION_STATES = 4;
const int ANIMATION_FRAMES = 8;
SDL_Rect spriteClips[ANIMATION_STATES][ANIMATION_FRAMES];

int spriteState = IDLE;
int framesCount = 8;
SDL_RendererFlip flip = SDL_FLIP_NONE;
bool isRunning = false;

float gravity = 0.38f;
bool isJumping = false;

int runSpeed = 0;
float ground;


Player::Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed)
{
	if (!texture.loadFromFile(filePath)) {
		LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << filePath << "'.";
	}
	else
	{
		// IDLE
		spriteClips[IDLE][0].x = 5;
		spriteClips[IDLE][0].y = 12;
		spriteClips[IDLE][0].w = 25;
		spriteClips[IDLE][0].h = 39;

		// WALK
		spriteClips[WALK][0].x = 191;
		spriteClips[WALK][0].y = 109;
		spriteClips[WALK][0].w = 23;
		spriteClips[WALK][0].h = 39;

		spriteClips[WALK][1].x = 221;
		spriteClips[WALK][1].y = 109;
		spriteClips[WALK][1].w = 29;
		spriteClips[WALK][1].h = 40;

		spriteClips[WALK][2].x = 263;
		spriteClips[WALK][2].y = 109;
		spriteClips[WALK][2].w = 39;
		spriteClips[WALK][2].h = 40;

		spriteClips[WALK][3].x = 308;
		spriteClips[WALK][3].y = 109;
		spriteClips[WALK][3].w = 39;
		spriteClips[WALK][3].h = 39;

		spriteClips[WALK][4].x = 352;
		spriteClips[WALK][4].y = 109;
		spriteClips[WALK][4].w = 23;
		spriteClips[WALK][4].h = 39;

		spriteClips[WALK][5].x = 378;
		spriteClips[WALK][5].y = 109;
		spriteClips[WALK][5].w = 25;
		spriteClips[WALK][5].h = 40;

		spriteClips[WALK][6].x = 411;
		spriteClips[WALK][6].y = 109;
		spriteClips[WALK][6].w = 40;
		spriteClips[WALK][6].h = 38;

		spriteClips[WALK][7].x = 460;
		spriteClips[WALK][7].y = 109;
		spriteClips[WALK][7].w = 39;
		spriteClips[WALK][7].h = 39;

		// RUN
		spriteClips[RUN][0].x = 10;
		spriteClips[RUN][0].y = 155;
		spriteClips[RUN][0].w = 28;
		spriteClips[RUN][0].h = 36;

		spriteClips[RUN][1].x = 44;
		spriteClips[RUN][1].y = 154;
		spriteClips[RUN][1].w = 29;
		spriteClips[RUN][1].h = 36;

		spriteClips[RUN][2].x = 82;
		spriteClips[RUN][2].y = 154;
		spriteClips[RUN][2].w = 28;
		spriteClips[RUN][2].h = 36;

		spriteClips[RUN][3].x = 116;
		spriteClips[RUN][3].y = 154;
		spriteClips[RUN][3].w = 29;
		spriteClips[RUN][3].h = 36;

		// JUMP
		spriteClips[JUMP][0].x = 386;
		spriteClips[JUMP][0].y = 74;
		spriteClips[JUMP][0].w = 27;
		spriteClips[JUMP][0].h = 30;

		spriteClips[JUMP][1].x = 417;
		spriteClips[JUMP][1].y = 77;
		spriteClips[JUMP][1].w = 30;
		spriteClips[JUMP][1].h = 27;

		spriteClips[JUMP][2].x = 452;
		spriteClips[JUMP][2].y = 75;
		spriteClips[JUMP][2].w = 27;
		spriteClips[JUMP][2].h = 30;

		spriteClips[JUMP][3].x = 481;
		spriteClips[JUMP][3].y = 77;
		spriteClips[JUMP][3].w = 30;
		spriteClips[JUMP][3].h = 27;
	}
	this->position = Vector2(x, y);
	this->velocity = Vector2(velX, velY);
	//this->width = texture.getWidth();
	//this->height = texture.getHeight();
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
	this->scrollSpeed = scrollSpeed;
	runSpeed = scrollSpeed * 2;
	ground = y;
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.key.repeat == 0) {
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				if (!isJumping) {
					spriteState = JUMP;
					framesCount = 4;
					isJumping = true;
					velocity.y -= 10;
				}
				break;
			case SDLK_LEFT:
				velocity.x -= isRunning ? runSpeed : scrollSpeed;
				if (!isJumping) {
					spriteState = isRunning ? RUN : WALK;
					framesCount = isRunning ? 4 : 8;
				}
				flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT:
				velocity.x += isRunning ? runSpeed : scrollSpeed;
				if (!isJumping) {
					spriteState = isRunning ? RUN : WALK;
					framesCount = isRunning ? 4 : 8;
				}
				flip = SDL_FLIP_NONE;
				break;
			case SDLK_SPACE:
				isRunning = true;
				if (spriteState == WALK) {
					spriteState = RUN;
					framesCount = 4;
					if (velocity.x < 0)
						velocity.x -= scrollSpeed;
					else if (velocity.x > 0)
						velocity.x += scrollSpeed;
				}
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				if (velocity.x < 0) {
					velocity.x += isRunning ? runSpeed : scrollSpeed;
				}
				if (!isJumping) {
					spriteState = IDLE;
					framesCount = 1;
				}
				break;
			case SDLK_RIGHT:
				if (velocity.x > 0) {
					velocity.x -= isRunning ? runSpeed : scrollSpeed;
				}
				if (!isJumping) {
					spriteState = IDLE;
					framesCount = 1;
				}
				break;
			case SDLK_SPACE:
				isRunning = false;
				if (spriteState == RUN) {
					spriteState = WALK;
					framesCount = 8;
					if (velocity.x < 0)
						velocity.x += scrollSpeed;
					else if (velocity.x > 0)
						velocity.x -= scrollSpeed;
				}
				break;
			}
			break;
		}
	}
}

void Player::move(float timeStep)
{
	position.x += velocity.x * timeStep;

	if (position.x < 0)
		position.x = 0;
	else if (position.x > scenarioWidth - width)
		position.x = (float)(scenarioWidth - width);

	// Jump
	if (isJumping) {
		velocity.y += gravity;

		if ((position.y + velocity.y) >= ground) {
			velocity.y = 0;
			isJumping = false;
			spriteState = IDLE;
			framesCount = 1;
		}

		position.y += velocity.y * 1.6;
	}
}

void Player::render(int camX, int camY)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % framesCount;

	SDL_Rect* currentClip = &spriteClips[spriteState][sprite];

	// Scale
	SDL_Rect dest = { (int)(position.x - camX), (int)(position.y - camY), currentClip->w * 2, currentClip->h * 2 };
	//SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), currentClip, &dest);

	this->width = dest.w;
	this->height = dest.h;

	texture.render((int)(position.x - camX), (int)(position.y - camY), currentClip, dest, 0, NULL, flip);
}

float Player::getPosX()
{
	return this->position.x;
}

float Player::getPosY()
{
	return this->position.y;
}

int Player::getWidth()
{
	return this->texture.getWidth();
}

int Player::getHeight()
{
	return this->texture.getHeight();
}
