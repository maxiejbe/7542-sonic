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
#include "../utils/PlayerUtils.h"

using namespace std;

//TODO: Apply polimorphism with player type (SONIC, TAILS...)
class PlayerView
{
public:
	PlayerView(Player* player);
	~PlayerView();
	void render(int camX, int camY);
	Player* getPlayer();

private:
	int getFramesCount(PlayerStatus status);
	int getFramesDivision(PlayerStatus status);
	void loadSpriteClips();
	bool checkTextures();

	void renderShield(int camX, int camY);

	void renderInvincibility(int camX, int camY);

	void renderPlayer(int camX, int camY);

	Texture texture;
	Texture textureShield;
	Texture textureInvincible;
	Player* player;
	SDL_Rect** spriteClips;
	bool isGreyed;
};

#endif // !PLAYERVIEW_H