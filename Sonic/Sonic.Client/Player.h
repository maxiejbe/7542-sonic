#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.h"
#include "Logger.h"
#include "Texture.h"
#include "Vector2.h"

using namespace std;

class Player
{
public:
	Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed);

	void handleEvent(SDL_Event& e);
	void move(float timeStep);
	void render(int camX, int camY);

	float getPosX();
	float getPosY();
	int getWidth();
	int getHeight();
private:
	Texture texture;
	Vector2 position;
	//float posX, posY;
	Vector2 velocity;
	//float velX, velY;
	int width, height;
	int scenarioWidth, scenarioHeight;
	int scrollSpeed;
};

#endif // !PLAYER_H