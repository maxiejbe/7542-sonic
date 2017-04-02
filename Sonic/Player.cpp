#include "Player.h"
#include "SDLWindow.h"

Player::Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH) {

	if (!texture.loadFromFile(filePath)) {
		LOG(logERROR, "Failed to load dot texture!");
	}

	this->posX = x;
	this->posY = y;
	this->velX = velX;
	this->velY = velY;
	this->width = texture.getWidth();
	this->height = texture.getHeight();
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
}

void Player::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY -= PLAYER_VEL; break;
		case SDLK_DOWN: velY += PLAYER_VEL; break;
		case SDLK_LEFT: velX -= PLAYER_VEL; break;
		case SDLK_RIGHT: velX += PLAYER_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY += PLAYER_VEL; break;
		case SDLK_DOWN: velY -= PLAYER_VEL; break;
		case SDLK_LEFT: velX += PLAYER_VEL; break;
		case SDLK_RIGHT: velX -= PLAYER_VEL; break;
		}
	}
}

void Player::move(float timeStep) {

	posX += velX * timeStep;

	if (posX < 0) {
		posX = 0;
	}
	else if (posX > scenarioWidth - width) {
		posX = scenarioWidth - width;
	}

	//Move the dot up or down
	posY += velY * timeStep;

	//If the dot went too far up or down
	if (posY < 0)
	{
		posY = 0;
	}
	else if (posY > scenarioHeight - height)
	{
		posY = scenarioHeight - height;
	}
}

void Player::render(int camX, int camY) {
	// Show the player relative to the camera
	texture.render((int)(posX - camX), (int)(posY - camY));
}

float Player::getPosX()
{
	return this->posX;
}

float Player::getPosY()
{
	return this->posY;
}

int Player::GetWidth()
{
	return this->texture.getWidth();
}

int Player::GetHeight()
{
	return this->texture.getHeight();
}
