#include "Player.h"
#include "SDLWindow.h"

const float gravity = 0.38f;
const int ANIMATION_STATES = 4;
const int ANIMATION_FRAMES = 8;
SDL_Rect spriteClips[ANIMATION_STATES][ANIMATION_FRAMES];


Player::Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed)
{
	if (!texture.loadFromFile(filePath)) {
		LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << filePath << "'.";
	}
	else {
		// PlayerStatus::idle
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

	this->number = -1;
	this->position = Vector2(x, y);
	this->velocity = Vector2(velX, velY);
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
	this->scrollSpeed = scrollSpeed;
	this->groundPos = y;
	this->isJumping = false;
	this->flip = SDL_FLIP_NONE;
	this->spriteState = PlayerStatus::idle;
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
		this->flip = SDL_FLIP_HORIZONTAL;
		this->targetVelX = -scrollSpeed;
		if (!this->isJumping) {
			this->spriteState = PlayerStatus::walking;
			if (input->isKeyPressed(KEY_SPACE)) {
				this->targetVelX *= turbo;
				this->spriteState = PlayerStatus::running;
			}
		}
	}

	if (input->isKeyPressed(KEY_RIGHT)) {
		this->flip = SDL_FLIP_NONE;
		this->targetVelX = scrollSpeed;
		if (!this->isJumping) {
			this->spriteState = PlayerStatus::walking;
			if (input->isKeyPressed(KEY_SPACE)) {
				this->targetVelX *= turbo;
				this->spriteState = PlayerStatus::running;
			}
		}
	}

	if (input->isKeyPressed(KEY_UP)) {
		// TODO: extraer a PlayerStatus::jumping()
		if (!this->isJumping) {
			this->spriteState = PlayerStatus::jumping;
			this->isJumping = true;
			velocity.y -= 10;
		}
	}

	// En caso que se suelten a la vez la flecha y el space.
	if (input->isKeyUp(KEY_LEFT) || input->isKeyUp(KEY_RIGHT)) {
		if (input->isKeyPressed(KEY_SPACE) || input->isKeyUp(KEY_SPACE)) {
			this->spriteState = PlayerStatus::walking;
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
		if (this->velocity.x == 0 && this->spriteState == PlayerStatus::walking) {
			this->spriteState = PlayerStatus::idle;
		}
		this->velocity.x = 0;
	}

	this->position.x += this->velocity.x;

	// Que no se salga de los limites
	if (position.x < 0)
		position.x = 0;
	else if (position.x > scenarioWidth - width)
		position.x = (float)(scenarioWidth - width);

	// PlayerStatus::jumping
	if (this->isJumping) {
		velocity.y += gravity;

		if ((position.y + velocity.y) >= this->groundPos) {
			velocity.y = 0;
			this->isJumping = false;
			this->spriteState = PlayerStatus::idle;
		}

		position.y += velocity.y * 1.6;
	}
}

void Player::render(int camX, int camY)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % getFramesCount(this->spriteState);

	SDL_Rect* currentClip = &spriteClips[this->spriteState][sprite];

	// Scale
	SDL_Rect dest = { (int)(position.x - camX), (int)(position.y - camY), currentClip->w * 2, currentClip->h * 2 };
	//SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), currentClip, &dest);

	this->width = dest.w;
	this->height = dest.h;

	texture.render((int)(position.x - camX), (int)(position.y - camY), currentClip, dest, 0, NULL, this->flip);
}

void Player::setNumber(int number)
{
	this->number = number;
}

int Player::getNumber()
{
	return this->number;
}

float Player::getPosX()
{
	return this->position.x;
}

void Player::setPosX(float x)
{
	this->position.x = x;
}

float Player::getPosY()
{
	return this->position.y;
}

void Player::setPosY(float y)
{
	this->position.y = y;
}

void Player::setPlayerStatus(PlayerStatus status)
{
	this->spriteState = status;
}

PlayerStatus Player::getPlayerStatus()
{
	return this->spriteState;
}

int Player::getWidth()
{
	return this->texture.getWidth();
}

int Player::getHeight()
{
	return this->texture.getHeight();
}

int Player::getFramesCount(PlayerStatus status)
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