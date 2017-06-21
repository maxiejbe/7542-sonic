#include "PlayerView.h"
#include "SDLWindow.h"

const int ANIMATION_STATES = 5;
const int ANIMATION_FRAMES_SONIC = 8;
const int ANIMATION_FRAMES_TAILS = 9;
const int ANIMATION_FRAMES_KNUCKLES = 8;
const int ANIMATION_FRAMES_SHADOW = 8;
const int SHIELD_WIDTH = 96;
const int SHIELD_HEIGHT = 92;
const int INVINCIBILITY_WIDTH = 96;
const int INVINCIBILITY_HEIGHT = 96;

PlayerView::PlayerView(Player* player)
{
	this->player = player;
	loadSpriteClips();
}

PlayerView::~PlayerView()
{
	if (this->spriteClips != nullptr) {
		for (int count = 0; count < ANIMATION_STATES; count++) {
			delete[] this->spriteClips[count];
		}
		delete[] this->spriteClips;
	}

	if (this->shieldClips != nullptr) {
		delete this->shieldClips;
	}

	if (this->player != nullptr) return;
	delete this->player;
}

void PlayerView::render(int camX, int camY)
{
	checkTextures();
	renderPlayer(camX, camY);
	renderShield(camX, camY);
	renderInvincibility(camX, camY);
}

bool PlayerView::checkTextures()
{
	// Check texture
	if (this->texture.getTexture() == nullptr) {
		if (!this->texture.loadFromFile(PlayerUtils::getPlayerSpritesheetPath(this->player))) {
			LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << PlayerUtils::getPlayerSpritesheetPath(this->player) << "'.";
			return false;
		}
		texture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!this->player->getIsConnected() && !this->isGreyed) {
		// Se desconecto, lo griso
		string filePath = PlayerUtils::getDisconnectedPlayerSpritesheetPath(this->player);
		if (!this->texture.loadFromFile(filePath)) {
			LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << filePath << "'.";
			return false;
		}
		texture.setBlendMode(SDL_BLENDMODE_BLEND);
		this->isGreyed = true;
	}
	else if (this->player->getIsConnected() && this->isGreyed) {
		// Volvio a conectarse, lo coloreo
		if (!this->texture.loadFromFile(PlayerUtils::getPlayerSpritesheetPath(this->player))) {
			LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << PlayerUtils::getPlayerSpritesheetPath(this->player) << "'.";
			return false;
		}
		texture.setBlendMode(SDL_BLENDMODE_BLEND);
		this->isGreyed = false;
	}

	return true;
}

void PlayerView::renderShield(int camX, int camY)
{
	if (player->getHasShield()) {
		if (this->textureShield.getTexture() == nullptr && !this->textureShield.loadFromFile("img/shield.png")) {
			LOG(logWARNING) << "No se pudo cargar la imagen del shield '" << "img/shield.png" << "'.";
		}
		else {
			textureShield.render((int)(player->getPosition().x - camX) - SHIELD_WIDTH / 4, (int)(player->getPosition().y - camY) - SHIELD_HEIGHT / 8, SHIELD_WIDTH, SHIELD_HEIGHT);
		}
	}
	else if (this->textureShield.getTexture() != nullptr) {
		this->textureShield.free();
	}
}

void PlayerView::renderInvincibility(int camX, int camY)
{
	if (player->getIsInvincible()) {
		if (this->textureInvincible.getTexture() == nullptr && !this->textureInvincible.loadFromFile("img/shields-spritesheet.png")) {
			LOG(logWARNING) << "No se pudo cargar la imagen del shield '" << "img/shields-spritesheet.png" << "'.";
		}
		else {
			Uint32 sprite = (this->player->getTime() / 120) % 9;

			SDL_Rect* currentClip = &shieldClips[sprite];

			int x = player->getPosition().x - camX - INVINCIBILITY_WIDTH / 4;
			int y = player->getPosition().y - camY - INVINCIBILITY_HEIGHT / 8;
			int w = INVINCIBILITY_WIDTH;
			int h = INVINCIBILITY_HEIGHT;

			// Scale
			SDL_Rect dest = { x, y, w, h };

			textureInvincible.render(x, y, currentClip, dest, 0, NULL, SDL_FLIP_NONE);
			//textureInvincible.render((int)(player->getPosition().x - camX) - INVINCIBILITY_WIDTH / 4, (int)(player->getPosition().y - camY) - INVINCIBILITY_HEIGHT / 8, SHIELD_WIDTH, INVINCIBILITY_HEIGHT);
		}
	}
	else if (this->textureInvincible.getTexture() != nullptr) {
		this->textureInvincible.free();
	}
}

void PlayerView::renderPlayer(int camX, int camY)
{
	// Calculate current sprite
	Uint32 sprite = (this->player->getTime() / getFramesDivision(this->player->getSpriteState())) % getFramesCount(this->player->getSpriteState()); //90

	SDL_Rect* currentClip = &spriteClips[player->getSpriteState()][sprite];

	// Scale
	SDL_Rect dest = { (int)(player->getPosition().x - camX), (int)(player->getPosition().y - camY), currentClip->w * 2, currentClip->h * 2 };

	// Calculate facing direction
	SDL_RendererFlip flip = (this->player->getFacingDirection() == FACING_RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	// Check recovering
	if (player->getIsRecovering()) {
		if (!this->isPlayingLoseRings) {
			if (this->player->getLives() == this->lastLives) {
				SoundManager::getInstance().playSound("sounds/lost_rings.wav");
			}
			this->isPlayingLoseRings = true;
		}
		if (this->player->getTime() % 200 < 100)
			texture.setAlpha(255);
		else
			texture.setAlpha(155);
	}
	else {
		texture.setAlpha(255);
		this->isPlayingLoseRings = false;
	}

	if (player->getSpriteState() == spinning) {
		if (!isPlayingSpin) {
			SoundManager::getInstance().playSound("sounds/spin.wav");
			isPlayingSpin = true;
		}
	}
	else {
		isPlayingSpin = false;
	}

	this->lastLives = this->player->getLives();

	texture.render((int)(player->getPosition().x - camX), (int)(player->getPosition().y - camY), currentClip, dest, 0, NULL, flip);
}

int PlayerView::getFramesCount(PlayerStatus status)
{
	switch (this->player->getPlayerType()) {
	case SONIC:
		switch (status) {
		case idle:
			return 1;
		case walking:
			return 8;
		case running:
			return 4;
		case jumping:
			return 4;
		case spinning:
			return 4;
		default:
			return 1;
		}
	case KNUCKLES:
		switch (status) {
		case idle:
			return 1;
		case walking:
			return 8;
		case running:
			return 4;
		case jumping:
			return 8;
		case spinning:
			return 4;
		default:
			return 1;
		}
	case TAILS:
		switch (status) {
		case idle:
			return 1;
		case walking:
			return 7;
		case running:
			return 3;
		case jumping:
			return 9;
		case spinning:
			return 4;
		default:
			return 1;
		}
	case SHADOW:
		switch (status) {
		case idle:
			return 1;
		case walking:
			return 8;
		case running:
			return 4;
		case jumping:
			return 4;
		case spinning:
			return 5;
		default:
			return 1;
		}
	default:
		return 0;
	}
}

int PlayerView::getFramesDivision(PlayerStatus status)
{
	switch (status) {
	case spinning:
		return 60;
	case jumping:
		return 70;
	default:
		return 85;
	}
}

void PlayerView::loadSpriteClips()
{
	switch (this->player->getPlayerType()) {
	case SONIC:
		spriteClips = new SDL_Rect *[ANIMATION_STATES];
		for (int count = 0; count < ANIMATION_STATES; count++) {
			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_SONIC];
		}

		// Idle
		spriteClips[PlayerStatus::idle][0].x = 5;
		spriteClips[PlayerStatus::idle][0].y = 12;
		spriteClips[PlayerStatus::idle][0].w = 25;
		spriteClips[PlayerStatus::idle][0].h = 39;

		// Walking
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

		// Running
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

		// Jumping
		spriteClips[PlayerStatus::jumping][0].x = 386;
		spriteClips[PlayerStatus::jumping][0].y = 72;
		spriteClips[PlayerStatus::jumping][0].w = 27;
		spriteClips[PlayerStatus::jumping][0].h = 30;

		spriteClips[PlayerStatus::jumping][1].x = 417;
		spriteClips[PlayerStatus::jumping][1].y = 75;
		spriteClips[PlayerStatus::jumping][1].w = 30;
		spriteClips[PlayerStatus::jumping][1].h = 27;

		spriteClips[PlayerStatus::jumping][2].x = 452;
		spriteClips[PlayerStatus::jumping][2].y = 72;
		spriteClips[PlayerStatus::jumping][2].w = 27;
		spriteClips[PlayerStatus::jumping][2].h = 30;

		spriteClips[PlayerStatus::jumping][3].x = 481;
		spriteClips[PlayerStatus::jumping][3].y = 75;
		spriteClips[PlayerStatus::jumping][3].w = 30;
		spriteClips[PlayerStatus::jumping][3].h = 27;

		// Spinning
		spriteClips[PlayerStatus::spinning][0].x = 351;
		spriteClips[PlayerStatus::spinning][0].y = 64;// 72;
		spriteClips[PlayerStatus::spinning][0].w = 30;
		spriteClips[PlayerStatus::spinning][0].h = 38;// 30;

		spriteClips[PlayerStatus::spinning][1].x = 386;
		spriteClips[PlayerStatus::spinning][1].y = 64;// 72;
		spriteClips[PlayerStatus::spinning][1].w = 27;
		spriteClips[PlayerStatus::spinning][1].h = 38;// 30;

		spriteClips[PlayerStatus::spinning][2].x = 417;
		spriteClips[PlayerStatus::spinning][2].y = 64;// 75;
		spriteClips[PlayerStatus::spinning][2].w = 30;
		spriteClips[PlayerStatus::spinning][2].h = 38;// 27;

		spriteClips[PlayerStatus::spinning][3].x = 452;
		spriteClips[PlayerStatus::spinning][3].y = 64;// 72;
		spriteClips[PlayerStatus::spinning][3].w = 27;
		spriteClips[PlayerStatus::spinning][3].h = 38;// 30;
		break;

	case TAILS:
		spriteClips = new SDL_Rect *[ANIMATION_STATES];
		for (int count = 0; count < ANIMATION_STATES; count++) {
			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_TAILS];
		}

		// idle
		spriteClips[PlayerStatus::idle][0].x = 23;
		spriteClips[PlayerStatus::idle][0].y = 14;
		spriteClips[PlayerStatus::idle][0].w = 36;
		spriteClips[PlayerStatus::idle][0].h = 31;

		// Walking
		spriteClips[PlayerStatus::walking][0].x = 23;
		spriteClips[PlayerStatus::walking][0].y = 169;
		spriteClips[PlayerStatus::walking][0].w = 40;
		spriteClips[PlayerStatus::walking][0].h = 32;

		spriteClips[PlayerStatus::walking][1].x = 72;
		spriteClips[PlayerStatus::walking][1].y = 168;
		spriteClips[PlayerStatus::walking][1].w = 42;
		spriteClips[PlayerStatus::walking][1].h = 32;

		spriteClips[PlayerStatus::walking][2].x = 123;
		spriteClips[PlayerStatus::walking][2].y = 166;
		spriteClips[PlayerStatus::walking][2].w = 36;
		spriteClips[PlayerStatus::walking][2].h = 32;

		spriteClips[PlayerStatus::walking][3].x = 171;
		spriteClips[PlayerStatus::walking][3].y = 166;
		spriteClips[PlayerStatus::walking][3].w = 42;
		spriteClips[PlayerStatus::walking][3].h = 32;

		spriteClips[PlayerStatus::walking][4].x = 220;
		spriteClips[PlayerStatus::walking][4].y = 166;
		spriteClips[PlayerStatus::walking][4].w = 40;
		spriteClips[PlayerStatus::walking][4].h = 32;

		spriteClips[PlayerStatus::walking][5].x = 268;
		spriteClips[PlayerStatus::walking][5].y = 166;
		spriteClips[PlayerStatus::walking][5].w = 41;
		spriteClips[PlayerStatus::walking][5].h = 32;

		spriteClips[PlayerStatus::walking][6].x = 320;
		spriteClips[PlayerStatus::walking][6].y = 165;
		spriteClips[PlayerStatus::walking][6].w = 43;
		spriteClips[PlayerStatus::walking][6].h = 32;

		// Running
		spriteClips[PlayerStatus::running][0].x = 378;
		spriteClips[PlayerStatus::running][0].y = 169;
		spriteClips[PlayerStatus::running][0].w = 37;
		spriteClips[PlayerStatus::running][0].h = 31;

		spriteClips[PlayerStatus::running][1].x = 422;
		spriteClips[PlayerStatus::running][1].y = 169;
		spriteClips[PlayerStatus::running][1].w = 36;
		spriteClips[PlayerStatus::running][1].h = 32;

		spriteClips[PlayerStatus::running][2].x = 470;
		spriteClips[PlayerStatus::running][2].y = 170;
		spriteClips[PlayerStatus::running][2].w = 36;
		spriteClips[PlayerStatus::running][2].h = 32;

		// Jumping
		spriteClips[PlayerStatus::jumping][0].x = 22;
		spriteClips[PlayerStatus::jumping][0].y = 102;
		spriteClips[PlayerStatus::jumping][0].w = 28;
		spriteClips[PlayerStatus::jumping][0].h = 48;

		spriteClips[PlayerStatus::jumping][1].x = 58;
		spriteClips[PlayerStatus::jumping][1].y = 102;
		spriteClips[PlayerStatus::jumping][1].w = 28;
		spriteClips[PlayerStatus::jumping][1].h = 48;

		spriteClips[PlayerStatus::jumping][2].x = 94;
		spriteClips[PlayerStatus::jumping][2].y = 100;
		spriteClips[PlayerStatus::jumping][2].w = 28;
		spriteClips[PlayerStatus::jumping][2].h = 48;

		spriteClips[PlayerStatus::jumping][3].x = 129;
		spriteClips[PlayerStatus::jumping][3].y = 101;
		spriteClips[PlayerStatus::jumping][3].w = 28;
		spriteClips[PlayerStatus::jumping][3].h = 48;

		spriteClips[PlayerStatus::jumping][4].x = 168;
		spriteClips[PlayerStatus::jumping][4].y = 106;
		spriteClips[PlayerStatus::jumping][4].w = 28;
		spriteClips[PlayerStatus::jumping][4].h = 48;

		spriteClips[PlayerStatus::jumping][5].x = 203;
		spriteClips[PlayerStatus::jumping][5].y = 105;
		spriteClips[PlayerStatus::jumping][5].w = 28;
		spriteClips[PlayerStatus::jumping][5].h = 50;

		spriteClips[PlayerStatus::jumping][6].x = 240;
		spriteClips[PlayerStatus::jumping][6].y = 106;
		spriteClips[PlayerStatus::jumping][6].w = 28;
		spriteClips[PlayerStatus::jumping][6].h = 48;

		spriteClips[PlayerStatus::jumping][7].x = 275;
		spriteClips[PlayerStatus::jumping][7].y = 108;
		spriteClips[PlayerStatus::jumping][7].w = 28;
		spriteClips[PlayerStatus::jumping][7].h = 48;

		spriteClips[PlayerStatus::jumping][8].x = 311;
		spriteClips[PlayerStatus::jumping][8].y = 108;
		spriteClips[PlayerStatus::jumping][8].w = 28;
		spriteClips[PlayerStatus::jumping][8].h = 48;

		// Spinning
		spriteClips[PlayerStatus::spinning][0].x = 376;
		spriteClips[PlayerStatus::spinning][0].y = 213;// 217;
		spriteClips[PlayerStatus::spinning][0].w = 51;
		spriteClips[PlayerStatus::spinning][0].h = 32;// 28;

		spriteClips[PlayerStatus::spinning][1].x = 437;
		spriteClips[PlayerStatus::spinning][1].y = 213;// 217;
		spriteClips[PlayerStatus::spinning][1].w = 49;
		spriteClips[PlayerStatus::spinning][1].h = 32;// 28;

		spriteClips[PlayerStatus::spinning][2].x = 497;
		spriteClips[PlayerStatus::spinning][2].y = 213;// 217;
		spriteClips[PlayerStatus::spinning][2].w = 47;
		spriteClips[PlayerStatus::spinning][2].h = 32;// 28;

		spriteClips[PlayerStatus::spinning][3].x = 552;
		spriteClips[PlayerStatus::spinning][3].y = 213;// 217;
		spriteClips[PlayerStatus::spinning][3].w = 48;
		spriteClips[PlayerStatus::spinning][3].h = 32;// 28;
		break;

	case KNUCKLES:
		spriteClips = new SDL_Rect *[ANIMATION_STATES];
		for (int count = 0; count < ANIMATION_STATES; count++) {
			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_KNUCKLES];
		}

		// Idle
		spriteClips[PlayerStatus::idle][0].x = 1;
		spriteClips[PlayerStatus::idle][0].y = 1;
		spriteClips[PlayerStatus::idle][0].w = 26;
		spriteClips[PlayerStatus::idle][0].h = 39;

		// Walking
		spriteClips[PlayerStatus::walking][0].x = 112;
		spriteClips[PlayerStatus::walking][0].y = 47;
		spriteClips[PlayerStatus::walking][0].w = 38;
		spriteClips[PlayerStatus::walking][0].h = 37;

		spriteClips[PlayerStatus::walking][1].x = 151;
		spriteClips[PlayerStatus::walking][1].y = 48;
		spriteClips[PlayerStatus::walking][1].w = 35;
		spriteClips[PlayerStatus::walking][1].h = 36;

		spriteClips[PlayerStatus::walking][2].x = 187;
		spriteClips[PlayerStatus::walking][2].y = 49;
		spriteClips[PlayerStatus::walking][2].w = 29;
		spriteClips[PlayerStatus::walking][2].h = 35;

		spriteClips[PlayerStatus::walking][3].x = 217;
		spriteClips[PlayerStatus::walking][3].y = 48;
		spriteClips[PlayerStatus::walking][3].w = 32;
		spriteClips[PlayerStatus::walking][3].h = 36;

		spriteClips[PlayerStatus::walking][4].x = 249;
		spriteClips[PlayerStatus::walking][4].y = 47;
		spriteClips[PlayerStatus::walking][4].w = 41;
		spriteClips[PlayerStatus::walking][4].h = 37;

		spriteClips[PlayerStatus::walking][5].x = 291;
		spriteClips[PlayerStatus::walking][5].y = 50;
		spriteClips[PlayerStatus::walking][5].w = 37;
		spriteClips[PlayerStatus::walking][5].h = 34;

		spriteClips[PlayerStatus::walking][6].x = 329;
		spriteClips[PlayerStatus::walking][6].y = 50;
		spriteClips[PlayerStatus::walking][6].w = 32;
		spriteClips[PlayerStatus::walking][6].h = 34;

		spriteClips[PlayerStatus::walking][7].x = 362;
		spriteClips[PlayerStatus::walking][7].y = 49;
		spriteClips[PlayerStatus::walking][7].w = 37;
		spriteClips[PlayerStatus::walking][7].h = 35;

		// Running
		spriteClips[PlayerStatus::running][0].x = 400;
		spriteClips[PlayerStatus::running][0].y = 49;
		spriteClips[PlayerStatus::running][0].w = 32;
		spriteClips[PlayerStatus::running][0].h = 35;

		spriteClips[PlayerStatus::running][1].x = 434;
		spriteClips[PlayerStatus::running][1].y = 49;
		spriteClips[PlayerStatus::running][1].w = 32;
		spriteClips[PlayerStatus::running][1].h = 35;

		spriteClips[PlayerStatus::running][2].x = 467;
		spriteClips[PlayerStatus::running][2].y = 49;
		spriteClips[PlayerStatus::running][2].w = 31;
		spriteClips[PlayerStatus::running][2].h = 35;

		spriteClips[PlayerStatus::running][3].x = 499;
		spriteClips[PlayerStatus::running][3].y = 49;
		spriteClips[PlayerStatus::running][3].w = 32;
		spriteClips[PlayerStatus::running][3].h = 35;

		// Jumping
		spriteClips[PlayerStatus::jumping][0].x = 32;
		spriteClips[PlayerStatus::jumping][0].y = 148;
		spriteClips[PlayerStatus::jumping][0].w = 30;
		spriteClips[PlayerStatus::jumping][0].h = 31;

		spriteClips[PlayerStatus::jumping][1].x = 63;
		spriteClips[PlayerStatus::jumping][1].y = 148;
		spriteClips[PlayerStatus::jumping][1].w = 31;
		spriteClips[PlayerStatus::jumping][1].h = 30;

		spriteClips[PlayerStatus::jumping][2].x = 95;
		spriteClips[PlayerStatus::jumping][2].y = 147;
		spriteClips[PlayerStatus::jumping][2].w = 30;
		spriteClips[PlayerStatus::jumping][2].h = 31;

		spriteClips[PlayerStatus::jumping][3].x = 126;
		spriteClips[PlayerStatus::jumping][3].y = 148;
		spriteClips[PlayerStatus::jumping][3].w = 31;
		spriteClips[PlayerStatus::jumping][3].h = 30;

		spriteClips[PlayerStatus::jumping][4].x = 32;
		spriteClips[PlayerStatus::jumping][4].y = 148;
		spriteClips[PlayerStatus::jumping][4].w = 30;
		spriteClips[PlayerStatus::jumping][4].h = 31;

		spriteClips[PlayerStatus::jumping][5].x = 63;
		spriteClips[PlayerStatus::jumping][5].y = 148;
		spriteClips[PlayerStatus::jumping][5].w = 31;
		spriteClips[PlayerStatus::jumping][5].h = 30;

		spriteClips[PlayerStatus::jumping][6].x = 95;
		spriteClips[PlayerStatus::jumping][6].y = 147;
		spriteClips[PlayerStatus::jumping][6].w = 30;
		spriteClips[PlayerStatus::jumping][6].h = 31;

		spriteClips[PlayerStatus::jumping][7].x = 126;
		spriteClips[PlayerStatus::jumping][7].y = 148;
		spriteClips[PlayerStatus::jumping][7].w = 31;
		spriteClips[PlayerStatus::jumping][7].h = 30;

		// Spinning
		spriteClips[PlayerStatus::spinning][0].x = 1;
		spriteClips[PlayerStatus::spinning][0].y = 140;// 148;
		spriteClips[PlayerStatus::spinning][0].w = 31;
		spriteClips[PlayerStatus::spinning][0].h = 38;// 30;

		spriteClips[PlayerStatus::spinning][1].x = 32;
		spriteClips[PlayerStatus::spinning][1].y = 140;// 148;
		spriteClips[PlayerStatus::spinning][1].w = 30;
		spriteClips[PlayerStatus::spinning][1].h = 38;// 31;

		spriteClips[PlayerStatus::spinning][2].x = 63;
		spriteClips[PlayerStatus::spinning][2].y = 140;// 148;
		spriteClips[PlayerStatus::spinning][2].w = 31;
		spriteClips[PlayerStatus::spinning][2].h = 38;// 30;

		spriteClips[PlayerStatus::spinning][3].x = 95;
		spriteClips[PlayerStatus::spinning][3].y = 140;// 147;
		spriteClips[PlayerStatus::spinning][3].w = 30;
		spriteClips[PlayerStatus::spinning][3].h = 38;// 31;

		spriteClips[PlayerStatus::spinning][4].x = 126;
		spriteClips[PlayerStatus::spinning][4].y = 140;// 148;
		spriteClips[PlayerStatus::spinning][4].w = 31;
		spriteClips[PlayerStatus::spinning][4].h = 38;// 30;
		break;

	case SHADOW:
		spriteClips = new SDL_Rect *[ANIMATION_STATES];
		for (int count = 0; count < ANIMATION_STATES; count++) {
			spriteClips[count] = new SDL_Rect[ANIMATION_FRAMES_SHADOW];
		}

		// Idle
		spriteClips[PlayerStatus::idle][0].x = 9;
		spriteClips[PlayerStatus::idle][0].y = 9;
		spriteClips[PlayerStatus::idle][0].w = 29;
		spriteClips[PlayerStatus::idle][0].h = 40;

		// Walking
		spriteClips[PlayerStatus::walking][0].x = 10;
		spriteClips[PlayerStatus::walking][0].y = 104;
		spriteClips[PlayerStatus::walking][0].w = 26;
		spriteClips[PlayerStatus::walking][0].h = 38;

		spriteClips[PlayerStatus::walking][1].x = 41;
		spriteClips[PlayerStatus::walking][1].y = 102;
		spriteClips[PlayerStatus::walking][1].w = 26;
		spriteClips[PlayerStatus::walking][1].h = 40;

		spriteClips[PlayerStatus::walking][2].x = 73;
		spriteClips[PlayerStatus::walking][2].y = 102;
		spriteClips[PlayerStatus::walking][2].w = 40;
		spriteClips[PlayerStatus::walking][2].h = 40;

		spriteClips[PlayerStatus::walking][3].x = 119;
		spriteClips[PlayerStatus::walking][3].y = 103;
		spriteClips[PlayerStatus::walking][3].w = 39;
		spriteClips[PlayerStatus::walking][3].h = 38;

		spriteClips[PlayerStatus::walking][4].x = 161;
		spriteClips[PlayerStatus::walking][4].y = 104;
		spriteClips[PlayerStatus::walking][4].w = 25;
		spriteClips[PlayerStatus::walking][4].h = 38;

		spriteClips[PlayerStatus::walking][5].x = 194;
		spriteClips[PlayerStatus::walking][5].y = 103;
		spriteClips[PlayerStatus::walking][5].w = 29;
		spriteClips[PlayerStatus::walking][5].h = 40;

		spriteClips[PlayerStatus::walking][6].x = 228;
		spriteClips[PlayerStatus::walking][6].y = 103;
		spriteClips[PlayerStatus::walking][6].w = 37;
		spriteClips[PlayerStatus::walking][6].h = 40;

		spriteClips[PlayerStatus::walking][7].x = 267;
		spriteClips[PlayerStatus::walking][7].y = 104;
		spriteClips[PlayerStatus::walking][7].w = 40;
		spriteClips[PlayerStatus::walking][7].h = 38;

		// Running
		spriteClips[PlayerStatus::running][0].x = 316;
		spriteClips[PlayerStatus::running][0].y = 106;
		spriteClips[PlayerStatus::running][0].w = 32;
		spriteClips[PlayerStatus::running][0].h = 36;

		spriteClips[PlayerStatus::running][1].x = 350;
		spriteClips[PlayerStatus::running][1].y = 106;
		spriteClips[PlayerStatus::running][1].w = 31;
		spriteClips[PlayerStatus::running][1].h = 36;

		spriteClips[PlayerStatus::running][2].x = 384;
		spriteClips[PlayerStatus::running][2].y = 106;
		spriteClips[PlayerStatus::running][2].w = 32;
		spriteClips[PlayerStatus::running][2].h = 36;

		spriteClips[PlayerStatus::running][3].x = 420;
		spriteClips[PlayerStatus::running][3].y = 106;
		spriteClips[PlayerStatus::running][3].w = 32;
		spriteClips[PlayerStatus::running][3].h = 36;

		// Jumping
		spriteClips[PlayerStatus::jumping][0].x = 623;
		spriteClips[PlayerStatus::jumping][0].y = 248;
		spriteClips[PlayerStatus::jumping][0].w = 30;
		spriteClips[PlayerStatus::jumping][0].h = 30;

		spriteClips[PlayerStatus::jumping][1].x = 658;
		spriteClips[PlayerStatus::jumping][1].y = 248;
		spriteClips[PlayerStatus::jumping][1].w = 30;
		spriteClips[PlayerStatus::jumping][1].h = 30;

		spriteClips[PlayerStatus::jumping][2].x = 693;
		spriteClips[PlayerStatus::jumping][2].y = 248;
		spriteClips[PlayerStatus::jumping][2].w = 30;
		spriteClips[PlayerStatus::jumping][2].h = 30;

		spriteClips[PlayerStatus::jumping][3].x = 728;
		spriteClips[PlayerStatus::jumping][3].y = 248;
		spriteClips[PlayerStatus::jumping][3].w = 30;
		spriteClips[PlayerStatus::jumping][3].h = 30;

		// Spinning

		spriteClips[PlayerStatus::idle][0].x = 9;
		spriteClips[PlayerStatus::idle][0].y = 9;
		spriteClips[PlayerStatus::idle][0].w = 29;
		spriteClips[PlayerStatus::idle][0].h = 40;


		spriteClips[PlayerStatus::spinning][0].x = 588;
		spriteClips[PlayerStatus::spinning][0].y = 238;// 248;
		spriteClips[PlayerStatus::spinning][0].w = 30;
		spriteClips[PlayerStatus::spinning][0].h = 40;// 30;

		spriteClips[PlayerStatus::spinning][1].x = 623;
		spriteClips[PlayerStatus::spinning][1].y = 238;// 248;
		spriteClips[PlayerStatus::spinning][1].w = 30;
		spriteClips[PlayerStatus::spinning][1].h = 40;// 30;

		spriteClips[PlayerStatus::spinning][2].x = 658;
		spriteClips[PlayerStatus::spinning][2].y = 238;// 248;
		spriteClips[PlayerStatus::spinning][2].w = 30;
		spriteClips[PlayerStatus::spinning][2].h = 40;// 30;

		spriteClips[PlayerStatus::spinning][3].x = 693;
		spriteClips[PlayerStatus::spinning][3].y = 238;// 248;
		spriteClips[PlayerStatus::spinning][3].w = 30;
		spriteClips[PlayerStatus::spinning][3].h = 40;// 30;

		spriteClips[PlayerStatus::spinning][4].x = 728;
		spriteClips[PlayerStatus::spinning][4].y = 238;// 248;
		spriteClips[PlayerStatus::spinning][4].w = 30;
		spriteClips[PlayerStatus::spinning][4].h = 40;// 30;
		break;
	}

	shieldClips = new SDL_Rect[9];

	// 1
	shieldClips[0].x = 7;
	shieldClips[0].y = 455;
	shieldClips[0].w = 48;
	shieldClips[0].h = 48;

	// 2
	shieldClips[1].x = 58;
	shieldClips[1].y = 455;
	shieldClips[1].w = 48;
	shieldClips[1].h = 48;

	// 3
	shieldClips[2].x = 109;
	shieldClips[2].y = 455;
	shieldClips[2].w = 48;
	shieldClips[2].h = 48;

	// 4
	shieldClips[3].x = 160;
	shieldClips[3].y = 455;
	shieldClips[3].w = 48;
	shieldClips[3].h = 48;

	// 5
	shieldClips[4].x = 211;
	shieldClips[4].y = 455;
	shieldClips[4].w = 48;
	shieldClips[4].h = 48;

	// 2
	shieldClips[5].x = 262;
	shieldClips[5].y = 455;
	shieldClips[5].w = 48;
	shieldClips[5].h = 48;

	// 3
	shieldClips[6].x = 313;
	shieldClips[6].y = 455;
	shieldClips[6].w = 48;
	shieldClips[6].h = 48;

	// 4
	shieldClips[7].x = 364;
	shieldClips[7].y = 455;
	shieldClips[7].w = 48;
	shieldClips[7].h = 48;

	// 5
	shieldClips[8].x = 415;
	shieldClips[8].y = 455;
	shieldClips[8].w = 48;
	shieldClips[8].h = 48;
}

Player * PlayerView::getPlayer()
{
	return this->player;
}
