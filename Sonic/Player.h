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
	static const int PLAYER_VEL = 600; // TODO: tomar del json

	Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH);

	void handleEvent(SDL_Event& e);
	void move(float timeStep);
	void render(int camX, int camY);

	float getPosX();
	float getPosY();
	int GetWidth();
	int GetHeight();
private:
	Texture texture;
	float posX, posY;
	float velX, velY;
	int width, height;
	int scenarioWidth, scenarioHeight;
};

#endif // !PLAYER_H