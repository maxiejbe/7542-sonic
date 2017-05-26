#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameState.h"

class PauseState : public GameState
{
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static PauseState* Instance() {
		return &m_PauseState;
	}

protected:
	PauseState() {}

private:
	static PauseState m_PauseState;

	static const int OPCMENU = 3;

	TTF_Font* font;
	Texture texture;
	Uint32 time;
	float posX, posY;
	const char* labels[OPCMENU];
	SDL_Surface* menus[OPCMENU];
	bool selected[OPCMENU];
	SDL_Color color[OPCMENU];
	int option;
	bool enabled[OPCMENU];

	void initColorNameOptions();
	void showBackgroundImage();
	void updateAndRenderOptions();
	void renderSelectedOption();
	int getNextOption(int, int);
	void setEnabledOptions();
};

#endif // !PAUSE_STATE_H

