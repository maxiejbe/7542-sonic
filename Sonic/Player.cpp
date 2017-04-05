#include "Player.h"
#include "SDLWindow.h"

Player::Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed)
{
	if (!texture.loadFromFile(filePath)) {
		LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << filePath << "'.";
	}

	this->posX = x;
	this->posY = y;
	this->velX = velX;
	this->velY = velY;
	this->width = texture.getWidth();
	this->height = texture.getHeight();
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
	this->scrollSpeed = scrollSpeed;
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY -= scrollSpeed; break;
		case SDLK_DOWN: velY += scrollSpeed; break;
		case SDLK_LEFT: velX -= scrollSpeed; break;
		case SDLK_RIGHT: velX += scrollSpeed; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY += scrollSpeed; break;
		case SDLK_DOWN: velY -= scrollSpeed; break;
		case SDLK_LEFT: velX += scrollSpeed; break;
		case SDLK_RIGHT: velX -= scrollSpeed; break;
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

int Player::getWidth()
{
	return this->texture.getWidth();
}

int Player::getHeight()
{
	return this->texture.getHeight();
}
