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

using namespace std;

class Player
{
public:
	Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed);

	void update(float dt);
	void updateInput();
	void move(float timeStep);
	void render(int camX, int camY);

	float getPosX();
	float getPosY();
	int getWidth();
	int getHeight();
private:
	Texture texture;
	Vector2 position;
	Vector2 velocity;
	int width, height;
	int scenarioWidth, scenarioHeight;
	int scrollSpeed;
	float groundPos;
	bool isJumping;
	float targetVelX;
};

#endif // !PLAYER_H