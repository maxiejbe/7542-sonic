#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Renderer.h"
#include "InputManager.h"

enum MenuConnectionStatus { CONNECTED, DISCONNECTED };

class Menu
{
public:
	
	Menu();
	~Menu();

	int showMenu();
	void setConnectionStatus(MenuConnectionStatus);
private:
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
	MenuConnectionStatus connectionStatus;
	bool enabled[OPCMENU];

	void initMenu();
	void initColorNameOptions();
	void showBackgroundImage();
	void updateAndRenderOptions();
	void freeSurfaceMenus();
	void changeSelectedOption();
	int getNextOption(int, int);
	void setEnabledOptions();
};

#endif // !MENU_H