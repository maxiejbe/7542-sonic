#include "Menu.h"
#include "Renderer.h"

Menu::Menu()
{
	initMenu();
}

Menu::~Menu()
{
}

void Menu::initMenu()
{
	TTF_Init();
	font = TTF_OpenFont("fonts/sega.ttf", 30);
	texture.loadFromFile("img/menu-background.jpg");

	labels[0] = "Connect";
	labels[1] = "Disconnect";
	labels[2] = "Exit";

	selected[0] = true;
	selected[1] = selected[2] = false;

	color[0] = { 255,255,255 };
	color[1] = { 255,0,0 };
}

void Menu::initColorNameOptions()
{
	option = 0;
	menus[option] = TTF_RenderText_Solid(font, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++)
	{
		if (i != option)
		{
			selected[i] = false;
			menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		}
	}
}

void Menu::showBackgroundImage()
{
	SDL_Rect dstrect;
	dstrect = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), NULL, &dstrect);
}

void Menu::updateAndRenderOptions()
{
	SDL_Rect Message_rect;
	for (int i = 0; i < OPCMENU; i += 1)
	{
		SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, menus[i]);
		Message_rect.x = SDLWindow::getInstance().getScreenWidth() / 2 - menus[i]->clip_rect.w / 2;
		Message_rect.y = (SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (2 * (menus[i]->clip_rect.h) * i);
		Message_rect.w = menus[i]->w;
		Message_rect.h = menus[i]->h;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &Message_rect);
	}

	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}

void Menu::freeSurfaceMenus()
{
	for (int i = 0; i < OPCMENU; i++)
	{
		SDL_FreeSurface(menus[i]);
	}
}

void Menu::changeSelectedOption()
{
	selected[option] = true;
	menus[option] = TTF_RenderText_Solid(font, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++)
	{
		if (i != option)
		{
			selected[i] = false;
			menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		}
	}
}

int Menu::showMenu()
{
	initColorNameOptions();
	showBackgroundImage();
	updateAndRenderOptions();

	SDL_Event event;
	bool isRunning = true;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				freeSurfaceMenus();
				return 1;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					option--;
					if (option < 0) { option = 0; }
					changeSelectedOption();
					updateAndRenderOptions();
					break;

				case SDLK_DOWN:
					option++;
					if (option == OPCMENU) { option = OPCMENU - 1; }
					changeSelectedOption();
					updateAndRenderOptions();
					break;

				case SDLK_RETURN:
					if (selected[0]) { return 0; } //TODO: Conectar
					if (selected[1]) { return 0; } //TODO: Desconectar
					if (selected[2])
					{
						freeSurfaceMenus();
						return 1;
					}

				case SDLK_ESCAPE:
					freeSurfaceMenus();
					return 0;
				}
			}
		}
	}
}