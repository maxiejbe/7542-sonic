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
int framesCount = 1;
SDL_RendererFlip flip = SDL_FLIP_NONE;

float gravity = 0.38f;


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
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
	this->scrollSpeed = scrollSpeed;
	this->groundPos = y;
	this->isJumping = false;
}

void Player::update(float dt)
{
	this->targetVelX = 0;

	updateInput();
	move(dt);
}

void Player::updateInput()
{
	InputManager* input = InputManager::getInstance();

	float turbo = 2;

	if (input->isKeyPressed(KEY_LEFT)) {
		flip = SDL_FLIP_HORIZONTAL;
		this->targetVelX = -scrollSpeed;
		if (!this->isJumping) {
			spriteState = WALK;
			framesCount = 8;
			if (input->isKeyPressed(KEY_SPACE)) {
				this->targetVelX *= turbo;
				spriteState = RUN;
				framesCount = 4;
			}
		}
	}

	if (input->isKeyPressed(KEY_RIGHT)) {
		flip = SDL_FLIP_NONE;
		this->targetVelX = scrollSpeed;
		if (!this->isJumping) {
			spriteState = WALK;
			framesCount = 8;
			if (input->isKeyPressed(KEY_SPACE)) {
				this->targetVelX *= turbo;
				spriteState = RUN;
				framesCount = 4;
			}
		}
	}

	if (input->isKeyPressed(KEY_UP)) {
		// TODO: extraer a jump()
		if (!this->isJumping) {
			spriteState = JUMP;
			framesCount = 4;
			this->isJumping = true;
			velocity.y -= 10;
		}
	}

	// En caso que se suelten a la vez la flecha y el space.
	if (input->isKeyUp(KEY_LEFT) || input->isKeyUp(KEY_RIGHT)) {
		if (input->isKeyPressed(KEY_SPACE) || input->isKeyUp(KEY_SPACE)) {
			spriteState = WALK;
			framesCount = 8;
		}
	}
}

void Player::move(float dt)
{
	// Weighted averaging acceleration method
	float a = 0.08;
	this->velocity.x = (a * this->targetVelX * dt) + ((1 - a) * this->velocity.x);

	// TODO: extraer a isStopping()
	if (fabs(this->velocity.x) < 0.4) {
		if (this->velocity.x == 0 && spriteState == WALK) {
			spriteState = IDLE;
			framesCount = 1;
		}
		this->velocity.x = 0;
	}

	this->position.x += this->velocity.x;

	// Que no se salga de los limites
	if (position.x < 0)
		position.x = 0;
	else if (position.x > scenarioWidth - width)
		position.x = (float)(scenarioWidth - width);

	// Jump
	if (this->isJumping) {
		velocity.y += gravity;

		if ((position.y + velocity.y) >= this->groundPos) {
			velocity.y = 0;
			this->isJumping = false;
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
