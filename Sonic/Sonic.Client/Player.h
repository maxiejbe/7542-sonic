#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.h"
#include "Logger.h"
#include "Texture.h"

using namespace std;

class Player
{
public:
	Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed);

	void handleEvent(SDL_Event& e);
	void move(float timeStep);
	void render(int camX, int camY);
	void render(int camX, int camY, int frame);

	float getPosX();
	float getPosY();
	int getWidth();
	int getHeight();
private:
	Texture texture;
	float posX, posY;
	float velX, velY;
	int width, height;
	int scenarioWidth, scenarioHeight;
	int scrollSpeed;
};

#endif // !PLAYER_H