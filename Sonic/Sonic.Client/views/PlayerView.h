#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Logger.h"
#include "Texture.h"
#include "Vector2.h"
#include "InputManager.h"
#include "entities/Message.h"
#include "entities/Player.h"

using namespace std;

class PlayerView
{
public:
	PlayerView(Player* player);

	void render(int camX, int camY);
private:
	int getFramesCount(PlayerStatus status);

	Texture texture;
	Player* player;
};

#endif // !PLAYERVIEW_H