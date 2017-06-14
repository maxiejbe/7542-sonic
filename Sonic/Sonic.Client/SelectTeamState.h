#ifndef SELECT_TEAM_STATE_H
#define SELECT_TEAM_STATE_H

#include "GameState.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "InputManager.h"
#include "ConnectState.h"

class SelectTeamState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static SelectTeamState* Instance() {
		return &m_SelectTeamState;
	}

	int getTeam();

protected:
	SelectTeamState() {}

private:
	static SelectTeamState m_SelectTeamState;

	static const int OPCMENU = 2;
	static const int TEAMS_COUNT = 2;

	TTF_Font* fontTeam;
	Texture texture;
	Texture backgroundTexture;
	Uint32 time;
	const char* labels[OPCMENU];
	SDL_Surface* menus[OPCMENU];
	bool selected[OPCMENU];
	bool team[TEAMS_COUNT];
	SDL_Color color[OPCMENU];
	int option;
	int selectedTeam;

	void initColorNameOptions();
	void updateAndRenderOptions();
	void renderSelectedOption();
	int getNextOption(int, int);
	void showBackgroundImage();
};

#endif // !SELECT_TEAM_STATE_H
