#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "InputManager.h"
#include "ConnectState.h"
#include "SelectTeamState.h"

enum MenuConnectionStatus { CONNECTED, DISCONNECTED };

class MenuState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static MenuState* Instance() {
		return &m_MenuState;
	}

protected:
	MenuState() {}

private:
	static MenuState m_MenuState;

	static const int OPCMENU = 2;

	TTF_Font* font;
	Texture texture;
	Texture textureConnect;
	Texture textureExit;
	Uint32 time;
	float posX, posY;
	const char* labels[OPCMENU];
	bool selected[OPCMENU];
	SDL_Color color[OPCMENU];
	int option;
	MenuConnectionStatus connectionStatus;
	GameMode gameMode;

	void initColorNameOptions();
	void showBackgroundImage();
	void updateAndRenderOptions();
	void renderSelectedOption();
	int getNextOption(int, int);
};

#endif // !MENU_STATE_H

