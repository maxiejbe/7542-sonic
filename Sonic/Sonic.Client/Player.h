#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.h"
#include "Logger.h"
#include "Texture.h"
#include "Vector2.h"
#include "InputManager.h"
#include "entities/Message.h"

using namespace std;

class Player
{
public:
	Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed);

	void update(float dt);
	void updateInput();
	void move(float timeStep);
	void render(int camX, int camY);

	void setNumber(int number);
	int getNumber();

	float getPosX();
	void setPosX(float x);
	float getPosY();
	void setPosY(float y);

	void setPlayerStatus(PlayerStatus status);
	PlayerStatus getPlayerStatus();

	int getWidth();
	int getHeight();
private:
	int getFramesCount(PlayerStatus status);
	Texture texture;
	Vector2 position;
	Vector2 velocity;
	int width, height;
	int scenarioWidth, scenarioHeight;
	int scrollSpeed;
	float groundPos;
	bool isJumping;
	float targetVelX;
	int number;
	SDL_RendererFlip flip;
	PlayerStatus spriteState;
};

#endif // !PLAYER_H