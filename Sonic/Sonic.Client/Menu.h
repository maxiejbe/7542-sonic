#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"

class Menu
{
public:
	Menu();
	~Menu();

	int ShowMenu();

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

	void InitMenu();
	void InitColorNameOptions();
	void ShowBackgroundImage();
	void UpdateAndRenderOptions();
	void FreeSurfaceMenus();
	void ChangeSelectedOption();
};

#endif // !MENU_H