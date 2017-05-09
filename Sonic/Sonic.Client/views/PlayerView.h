#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Logger.h"
#include "Texture.h"
#include "Vector2.h"
#include "InputManager.h"
#include "protocol/Message.h"
#include "entities/Player.h"

using namespace std;

class PlayerView
{
public:
	PlayerView(Player* player);
	~PlayerView();
	void render(int camX, int camY);
	Player* getPlayer();

private:
	int getFramesCount(PlayerStatus status);
	void loadSpriteClips();

	Texture texture;
	Player* player;
	SDL_Rect** spriteClips;
	bool isGreyed;
};

#endif // !PLAYERVIEW_H